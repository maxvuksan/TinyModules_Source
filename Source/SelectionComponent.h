#pragma once
#include <JuceHeader.h>
#include "CustomLookAndFeel.h"

class SelectionComponent : public juce::Component
{

    public:

        SelectionComponent() {
            setInterceptsMouseClicks(false, false);
        }

        void paint(juce::Graphics& g) override
        {
            g.setColour(CustomLookAndFeel::GetTheme()->colour_selectionFill);
            g.fillRect(getLocalBounds().reduced(1));

            g.setColour(CustomLookAndFeel::GetTheme()->colour_selectionOutline);
            g.drawRect(getLocalBounds().reduced(1), 2);
        }

};
