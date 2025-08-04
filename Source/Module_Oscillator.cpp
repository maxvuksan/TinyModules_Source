#include "Module_Oscillator.h"
#include "Globals.h"
#include "DSPUtility.h"

Module_Oscillator::Module_Oscillator() : Module::Module(3, "oscillator") {

    KnobConfiguration freqConfig;
    freqConfig.defaultValue = 261.63;
    freqConfig.increment = 0.01;
    freqConfig.min = 20;
    freqConfig.max = 16000;
    freqConfig.skewAroundDefault = true;

    auto& freqKnob = Component_CreateKnob("freq", 2, 0, &freqConfig);

    KnobConfiguration fmConfig;
    freqConfig.defaultValue = 0;
    freqConfig.increment = 0.001;
    freqConfig.min = -1;
    freqConfig.max = 1;

    auto& fmDepthKnob = Component_CreateKnob("fm", 0, 3, &fmConfig);


    Component_CreateInputSocket("fm", 0, 4);
    Component_CreateInputSocket("v/oct", 0, 0);

    Component_CreateOutputSocket("sin", 2, 1);
    Component_CreateOutputSocket("squ", 2, 2);
    Component_CreateOutputSocket("saw", 2, 3);
    Component_CreateOutputSocket("tri", 2, 4);
}

void Module_Oscillator::Reset() {
    // set each channel to 0
    for (int i = 0; i < 16; i++) {
        phase[i] = 0;
    }
}

void Module_Oscillator::Prepare(double sampleRate, int blockSize) {
    Module::Prepare(sampleRate, blockSize, 2, 4);
}

void Module_Oscillator::Process() {

    const int numSamples = GetOutputBuffer(0).getNumSamples();

    float* sineOut      = GetOutputWritePtr(0);
    float* squareOut    = GetOutputWritePtr(1);
    float* sawOut       = GetOutputWritePtr(2);
    float* triangleOut  = GetOutputWritePtr(3);

    // TODO: num of active voices need to be assigned to the input socket from out socket 
    /*
        when we have multiple cables, we take the maximum number of channels, and sum the contents of each channel
    */
    int numActiveVoices = Component_GetSocket("v/oct")->GetNumActiveVoices();

    DBG(numActiveVoices);

    float knobFreq = Component_GetKnobValue("freq"); // Hz
    float knobVolts = DSP::FrequencyToVoltage(knobFreq);

    for (int voice = 0; voice < numActiveVoices; voice++) {

        float vOct = 0;
        if (Component_GetSocket("v/oct")->HasConnection()) {

            const float* vOctBuffer = GetInputReadPtr(1, voice); // V/OCT input
            vOct = vOctBuffer[0];
        }

        float totalVolts = knobVolts + vOct;

        for (int i = 0; i < numSamples; ++i)
        {
            float fm = GetInputReadPtr(0)[i];

            float freq = DSP::VoltageToFrequency(totalVolts) + (fm * Component_GetKnobValue("FM") * 15.0f);

            phaseIncrement = DSP::GetPhaseIncrement(freq, sampleRate);

            // Generate samples
            float sineSample        = DSP::SampleWaveform(DSP::WaveType::Sine, phase[voice]);
            float squareSample      = DSP::SampleWaveform(DSP::WaveType::Square, phase[voice]);
            float sawSample         = DSP::SampleWaveform(DSP::WaveType::Saw, phase[voice]);
            float triangleSample    = DSP::SampleWaveform(DSP::WaveType::Triangle, phase[voice]);

            // Write to output buffer 
            sineOut[i]      += sineSample;
            squareOut[i]    += squareSample;
            sawOut[i]       += sawSample;
            triangleOut[i]  += triangleSample;

            DSP::IncrementPhase(phase[voice], phaseIncrement);
        }
    }

    /* Optional normalisation:  prevent level jump as voices stack
   (comment out if you want true amplitude build-up) */ 
    if (numActiveVoices > 1)
    {
        const float g = 1.0f / numActiveVoices;
        //juce::FloatVectorOperations::multiply(sineOut, g, numSamples);
        //juce::FloatVectorOperations::multiply(squareOut, g, numSamples);
        //juce::FloatVectorOperations::multiply(sawOut, g, numSamples);
        //juce::FloatVectorOperations::multiply(triangleOut, g, numSamples);
    }
}


