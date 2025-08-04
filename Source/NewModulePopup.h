
#pragma once
#include <JuceHeader.h>
#include "TextList.h"
#include "CustomLookAndFeel.h"

class NewModulePopup : public juce::Component {

	public:

		NewModulePopup() {

			textList.SetItems({
				"ADSR",
				"Filter",
				"Other",
				"Noise",
				"Chords",
				"Sequencer"
			});

			listBox.setColour(juce::ListBox::backgroundColourId,
				CustomLookAndFeel::GetTheme()->colour_backgroundRackEven);

			listBox.setModel(&textList);
			addAndMakeVisible(listBox);

		}

		void paint(juce::Graphics& g);
		void resized();

	private:

		TextList textList;
		juce::ListBox listBox;


};