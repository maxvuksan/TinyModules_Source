#include "NewModulePopup.h"


void NewModulePopup::paint(juce::Graphics& g) {

	g.setColour(CustomLookAndFeel::GetTheme()->colour_headerBar);
	g.fillRect(getLocalBounds());
}

void NewModulePopup::resized() {

	listBox.setBounds(getLocalBounds().reduced(20).removeFromLeft(300));
}