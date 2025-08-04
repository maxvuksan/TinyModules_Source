#include "TextList.h"
#include "CustomLookAndFeel.h"

void TextList::SetItems(std::vector<juce::String> otherItems) {

    this->items.resize(otherItems.size());
    std::copy(otherItems.begin(), otherItems.end(), this->items.begin());

}

int TextList::getNumRows() {
    return items.size();
}

void TextList::paintListBoxItem(int rowNumber, juce::Graphics& g,
    int width, int height, bool rowIsSelected)
{
    if (rowIsSelected) {
        g.setColour(CustomLookAndFeel::GetTheme()->colour_blockFill);
    }
    else {
        if (rowNumber % 2 == 0) {
            g.setColour(CustomLookAndFeel::GetTheme()->colour_backgroundRackEven);
        }
        else {
            g.setColour(CustomLookAndFeel::GetTheme()->colour_backgroundRackOdd);
        }
    }

    g.fillRect(0, 0, width, height);
    
    g.setColour(CustomLookAndFeel::GetTheme()->colour_knobPointer);

    const int paddingX = 10;

    g.drawText(items[rowNumber],
        paddingX,                      // x
        0,                      // y
        width - 2 * paddingX,           // adjusted width
        height,          // adjusted height
        juce::Justification::centredLeft);
}