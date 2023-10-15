#pragma once
#include <SFML/Graphics.hpp>

#include "Dimension.h"
#include "Point.h"
#include "Corner.h"

class CurvilinearTriangle {
private: 
	Dimension Size;
	Corner Position;
	Point Origin;
	sf::Color FillColor;

	sf::VertexArray Shape;
	sf::RectangleShape HorizontalRectangle;
	sf::RectangleShape VerticalRectangle;

	double Thickness;

public:
	CurvilinearTriangle();
	CurvilinearTriangle(Point Origin, Dimension Size, double Thickness, Corner Position, sf::Color FillColor);
	void Draw();
};