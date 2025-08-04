#include "CustomLookAndFeel.h"

CustomTheme* CustomLookAndFeel::theme;

void CustomLookAndFeel::Init() {

	theme = new CustomTheme;
}

CustomTheme* CustomLookAndFeel::GetTheme() {

	jassert(theme != nullptr);
	return theme;
}

void CustomLookAndFeel::Destruct() {
	delete theme;
	theme = nullptr;
}

CustomLookAndFeel::CustomLookAndFeel()
{
	if (theme == nullptr) {
		CustomLookAndFeel::Init();
	}

    // Load the font from binary data
    theme->typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::RalewayMedium_ttf,
        BinaryData::RalewayMedium_ttfSize);

	theme->font = juce::Font(theme->typeface).withHeight(16.0f);
}

CustomLookAndFeel::~CustomLookAndFeel() {
	if (theme != nullptr) {
		CustomLookAndFeel::Destruct();
	}
}

juce::Typeface::Ptr CustomLookAndFeel::getTypefaceForFont(const juce::Font& font)
{
    // Return the custom font instead of the default one
    return theme->typeface;
}




void CustomLookAndFeel::drawButtonBackground(juce::Graphics& g,
    juce::Button& button,
    const juce::Colour& backgroundColour,
    bool shouldDrawButtonAsHighlighted,
    bool shouldDrawButtonAsDown)
{
    auto bounds = button.getLocalBounds().toFloat();
    auto cornerSize = GetTheme()->borderRadius;

    // Base color
    juce::Colour baseColour = GetTheme()->colour_blockFill;

    if (shouldDrawButtonAsDown)
        baseColour = GetTheme()->colour_blockFillDark;
    else if (shouldDrawButtonAsHighlighted)
        baseColour = GetTheme()->colour_selectionFill;

    // Fill only, no border
    g.setColour(baseColour);
    g.fillRoundedRectangle(bounds, cornerSize);
}

void CustomLookAndFeel::drawButtonText(juce::Graphics& g,
    juce::TextButton& button,
    bool shouldDrawButtonAsHighlighted,
    bool shouldDrawButtonAsDown)
{
    // Use the custom theme font
    auto font = GetTheme()->font;
    g.setFont(font);

    juce::Colour textColour = GetTheme()->colour_headerBarText;

    if (!button.isEnabled())
        textColour = textColour.withMultipliedAlpha(0.5f);

    g.setColour(textColour);
    g.drawFittedText(button.getButtonText(),
        button.getLocalBounds(),
        juce::Justification::centred,
        1);
}
