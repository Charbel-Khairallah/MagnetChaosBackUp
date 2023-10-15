#pragma once
#include <SFML/Graphics.hpp>

#include "Point.h"
#include "Dimension.h"
#include "Config.h"
#include "Frame.h"
#include "Rectangle.h"
#include "Methods.h"

class Button {
private:
	sf::CircleShape TopLeftInnerCircle;
	sf::CircleShape TopRightInnerCircle;
	sf::CircleShape BottomLeftInnerCircle;
	sf::CircleShape BottomRightInnerCircle;

	sf::CircleShape TopLeftOuterCircle;
	sf::CircleShape TopRightOuterCircle;
	sf::CircleShape BottomLeftOuterCircle;
	sf::CircleShape BottomRightOuterCircle;

	sf::RectangleShape MainVerticalRectangle;
	sf::RectangleShape MainHorizontalRectangle;

	sf::RectangleShape TopEdgeRectangle;
	sf::RectangleShape BottomEdgeRectangle;
	sf::RectangleShape LeftEdgeRectangle;
	sf::RectangleShape RightEdgeRectangle;

	sf::Text ButtonText;

	sf::Color MainColor;
	sf::Color HoverColor;
	sf::Color PressedColor;
	sf::Color DisabledColor;

	sf::Color MainFill;
	sf::Color HoverFill;
	sf::Color PressedFill;
	sf::Color DisabledFill;

	sf::Color BorderColor;
	sf::Color BorderHoverColor;
	sf::Color BorderPressedColor;
	sf::Color DisabledBorderColor;

	Point Position;
	Dimension Size;
	double Thickness;
	double BorderRadius;
	bool Disabled;
public:
	Button(Point Position, Dimension Size, std::string ButtonText, double Thickness, double BorderRadius);
	Button();
	~Button();

	void Refresh();
	void Draw();
	void Enable();
	void Disable();

	bool MouseOver();
	bool IsEnabled();
};