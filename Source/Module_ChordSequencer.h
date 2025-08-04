#pragma once
#include "Module.h"
#include "PianoSwitch.h"

class Module_ChordSequencer : public Module {

public:
	Module_ChordSequencer();

	juce::var SerializeCustom() override;
	void DeserializeCustom(const juce::var&) override;

	void Reset();
	void Prepare(double sampleRate, int blockSize);
	void Process();

	void Step();
	void StepReset();

private:

	bool previousClockHigh = false;
	bool previousStepResetHigh = false;

	int stepIndex = 0;

	std::unique_ptr<PianoSwitch> pianoSwitch[4];
};