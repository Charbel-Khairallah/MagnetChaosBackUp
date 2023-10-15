#pragma once
#include <SFML/Graphics.hpp>

#include "Config.h"
#include "Point.h"
#include "Frame.h"

class Text {
private:
	std::vector<std::string> Lines;
	double TextSize;
	double TimeGap;
	Point Position;

	int CurrentColumn;
	int CurrentRow;
	bool HasNext;

	sf::Color TextColor;
	sf::Clock CharacterGapTimer;

	std::vector<sf::Text> VisibleLines;
	void CalculateNextCharacter();

public:
	Text(std::vector<std::string> Lines, double TextSize, Point Position);
	Text();
	~Text();

	void Draw();
	void Refresh();
	void Reset();
};