
#include "SwitchGrid.h"
#include "Globals.h"
#include "CustomLookAndFeel.h"

SwitchGrid::SwitchGrid(int width, int height) {

	switches.resize(width);
	switchRecentlyInteracted.resize(width);
	for (int i = 0; i < width; i++) {
		switches[i].resize(height, false);
		switchRecentlyInteracted[i].resize(height);
	}

	outlineX = -1;
	outlineY = -1;

	highlightX = -1;
	highlightY = -1;
}

juce::var SwitchGrid::Serialize()
{
	juce::Array<juce::var> outerArray;

	for (const auto& column : switches)
	{
		juce::Array<juce::var> innerArray;
		for (bool state : column)
		{
			innerArray.add(state);  // saves as bool var
		}
		outerArray.add(innerArray);
	}

	return outerArray;
}

void SwitchGrid::Deserialize(const juce::var& data)
{
	if (!data.isArray()) return;

	auto* outerArray = data.getArray();
	int width = (int)outerArray->size();

	if (width != switches.size()) return; // safety check

	for (int x = 0; x < width; ++x)
	{
		auto inner = outerArray->getReference(x);
		if (!inner.isArray()) continue;

		auto* innerArray = inner.getArray();
		int height = (int)innerArray->size();

		if (height != switches[x].size()) continue;

		for (int y = 0; y < height; ++y)
		{
			switches[x][y] = (bool)innerArray->getReference(y);
		}
	}

	repaint();
}

void SwitchGrid::SetHighlighted(int x, int y) {
	highlightX = x;
	highlightY = y;
}

void SwitchGrid::SetOutlined(int x, int y) {
	outlineX = x;
	outlineY = y;
}

bool SwitchGrid::GetSwitchState(int x, int y) {
	return switches[x][y];
}
bool SwitchGrid::GetSwitchRecentlyInteractedState(int x, int y) {
	return switchRecentlyInteracted[x][y];
}
void SwitchGrid::SetSwitchRecentlyInteractedState(int x, int y, bool state) {
	switchRecentlyInteracted[x][y] = state;
}

void SwitchGrid::paint(juce::Graphics & g){

	const int totalWidth = switches.size() * (GLOBAL_COMPONENT_WIDTH / 2);
	const int totalHeight = switches[0].size() * (GLOBAL_COMPONENT_HEIGHT + GLOBAL_COMPONENT_PADDING_Y) - 4;

	juce::Rectangle<int> gridBounds(0, 0, totalWidth, totalHeight);

	g.setColour(CustomLookAndFeel::GetTheme()->colour_displayPanel);
	g.fillRect(gridBounds.toFloat().reduced(1.0f));

	for (int x = 0; x < switches.size(); x++) {
		for (int y = 0; y < switches[x].size(); y++) {

			auto pos = getLocalBounds().getTopLeft();

			pos.addXY(x * (GLOBAL_COMPONENT_WIDTH / 2), y * (GLOBAL_COMPONENT_HEIGHT + GLOBAL_COMPONENT_PADDING_Y));

			juce::Rectangle<float> squareBaseRect(
				pos.x + 3,
				pos.y + 4,
				(GLOBAL_COMPONENT_WIDTH / 2) - 6,
				GLOBAL_COMPONENT_HEIGHT - 8
			);

			// the switch is the current trigger
			if (outlineX == x && outlineY == y) {
				g.setColour(CustomLookAndFeel::GetTheme()->colour_switchOutline);
				g.drawRect(squareBaseRect.expanded(1.0f), 2.0f);
			}
			if (highlightX == x && highlightY == y) {
				
				if (switches[x][y]) {
					g.setColour(CustomLookAndFeel::GetTheme()->colour_switchOnHighlight);
				}
				else {
					g.setColour(CustomLookAndFeel::GetTheme()->colour_switchOffHighlight);
				}
			}
			else {
				if (switches[x][y]) {
					g.setColour(CustomLookAndFeel::GetTheme()->colour_switchOn);
				}
				else {
					g.setColour(CustomLookAndFeel::GetTheme()->colour_switchOff);
				}
			}

			g.fillRect(squareBaseRect.reduced(1.0f));
		}
	}
}

void SwitchGrid::mouseDown(const juce::MouseEvent& e) {

	int xIndex = e.position.x / (GLOBAL_COMPONENT_WIDTH / 2);
	int yIndex = e.position.y / GLOBAL_COMPONENT_HEIGHT;

	if (xIndex >= 0 && xIndex < switches.size() &&
		yIndex >= 0 && yIndex < switches[xIndex].size())
	{
		switchRecentlyInteracted[xIndex][yIndex] = true;

		if (e.mods.isLeftButtonDown())
		{
			switches[xIndex][yIndex] = !switches[xIndex][yIndex];
		}

		if (onClick) {
			onClick(xIndex, yIndex, this);
		}

		repaint();

	}

}


