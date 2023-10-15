#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Point.h"
#include "Dimension.h"
#include "Key.h"

class ControlItem{
private:
	Point* Origin;
	Dimension Size;
	int Index;
	bool MousePressed;

	sf::Text Title;
	sf::Text Value;

	sf::Vertex TopGradientVertex[4];
	sf::Vertex BottomGradientVertex[4];

	sf::RectangleShape FirstRectangle;
	sf::RectangleShape SecondRectangle;
	sf::RectangleShape ThirdRectangle;

	sf::RectangleShape TopSeparator;
	sf::RectangleShape BottomSeparator;

	sf::CircleShape TopOutterCircle;
	sf::CircleShape TopInnerCircle;
	sf::CircleShape BottomOutterCircle;
	sf::CircleShape BottomInnerCircle;

public:
	static ControlItem* SelectedItem;
	Key * SelectedKey;
	int SelectedKeyIndex;

	ControlItem(Point & Origin, Dimension Size, int Index, std::string Title, Key * SelectedKey, int SelectedKeyIndex);
	~ControlItem();

	void Select();
	void Refresh();
	void SetPositions();
	void SetValue(std::string);

	double GetX();
	double GetY();
	double GetWidth();
	double GetHeight();

	std::string GetValue();

	void Draw();
};


/*
	Desired Shape On Focus:
	====================-----
	====================-----
	===========
	===========
	===========
	===========\
	===============\
	================|
	================|
	================|
	================|
	===============/
	===========/
	===========
	===========
	===========
	====================-----
	====================-----
*/