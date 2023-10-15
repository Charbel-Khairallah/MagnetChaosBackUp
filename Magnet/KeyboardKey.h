#pragma once
#include <SFML/Graphics.hpp>
#include "Key.h"
#include "Dimension.h"
#include "Point.h"

class KeyboardKey : public Key {
private:

	sf::RectangleShape MiddleRectangle;
	sf::ConvexShape LeftPolygon;
	sf::ConvexShape RightPolygon;
	sf::ConvexShape BottomPolygon;

	sf::RectangleShape SelectionRectangle;
	sf::CircleShape LeftSelectionCircle;
	sf::CircleShape RightSelectionCircle;
	
	sf::RectangleShape DisabledRectangle;

	sf::Text Label;
	std::string Letter;

public:
	static Dimension Unit;
	static Point Origin;

	KeyboardKey(int Rotation, std::string Letter, double Multiplier, Dimension Shift, int KeyType, int KeyCode);
	~KeyboardKey();

	void Select(int Index = 0);
	void UnSelect();
	void Refresh();

	double GetX();
	double GetY();
	double GetWidth();
	double GetHeight();

	std::string GetValue();

	void Draw();
};