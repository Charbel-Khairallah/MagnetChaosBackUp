#pragma once
#include <SFML/Graphics.hpp>

#include "Point.h"
#include "Config.h"
#include "Frame.h"
#include "Methods.h"
#include "Circle.h"

class MagneticField {
private:
	static int MaxRadius;
	
	double CurrentIntensity;
	bool FadingOut;

	Point Center;
	Dimension BlockSize;

	sf::CircleShape Field;

	void ClampIntensity();

public:
	MagneticField(Point Center = Point(0, 0), Dimension BlockSize = Dimension(0, 0));
	~MagneticField();

	void Refresh(double Intensity);
	void Draw();
	void FadeOut();

	double GetIntensity();
	Circle GetBoundaries();

};