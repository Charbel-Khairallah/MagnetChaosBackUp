#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Config.h"
#include "Point.h"
#include "Dimension.h"
#include "Frame.h"

class MenuItem {
private:
	sf::RectangleShape TopBorder;
	sf::RectangleShape BottomBorder;
	sf::RectangleShape LeftBorder;
	sf::RectangleShape RightBorder;

	int Index;
	int BorderThickness;

	static MenuItem * SelectedItem;

protected:
	Point Origin;
	Dimension Size;
	sf::Text Label;

	void DrawBase();

public:
	MenuItem(std::string LabelText, Point Origin, Dimension Size);
	virtual ~MenuItem();

	virtual void Draw() = NULL;
	virtual void Refresh() = NULL;
};