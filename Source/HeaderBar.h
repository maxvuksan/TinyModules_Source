#pragma once
#include <JuceHeader.h>
#include "Globals.h"

class HeaderBar : public juce::Component {

    public:
        HeaderBar();
        ~HeaderBar() override;

        void paint(juce::Graphics& g) override;
        void resized() override;

    private:
        
        void ShowSaveDialog();
        void ShowLoadDialog();

        void ShowMenuCallback(); 
        
        
        // Example buttons or controls
        juce::TextButton menuButton{ "Menu" };  
        juce::Label titleLabel;

        std::unique_ptr<juce::FileChooser> fileChooser;

		SAFE_UI_COMPONENT(HeaderBar)

};