#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"

class BackIcon {
private:
	bool MouseInside;

	sf::CircleShape OutterCircle;
	sf::CircleShape InnerCircle;
	sf::RectangleShape RectangleGap;
	sf::RectangleShape TopBackArrow;
	sf::RectangleShape BottomBackArrow;

	double RotationSpeed;

public:
	BackIcon();
	~BackIcon();

	void FadeIn();
	void FadeOut();
	void Refresh();
	void Draw();

	bool MouseOver();
};