#pragma once
#include "Module.h"

class Module_Oscillator : public Module {

	public:

		Module_Oscillator();

		void Reset() override;
		void Prepare(double sampleRate, int blockSize) override;
		void Process();

	private:


		float phase[16];

		float phaseIncrement = 0;

};