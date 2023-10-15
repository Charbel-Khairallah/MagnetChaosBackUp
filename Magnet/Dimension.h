#pragma once
#include <SFML/Graphics.hpp>
//#include "Point.h"

class Dimension {
private:
	double Width;
	double Height;

public:
	Dimension();
	Dimension(double Width, double Height);
	//Dimension(Point First, Point Second);

	double GetWidth();
	double GetHeight();
	double GetLength();
	sf::Vector2f Vector2F();

	Dimension operator +(Dimension Other);
	Dimension operator -(Dimension Other);
	Dimension & operator +=(Dimension Other);
	Dimension & operator -=(Dimension Other);
	bool operator > (Dimension Other);
	bool operator < (Dimension Other);
};