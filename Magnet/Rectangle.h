#pragma once
#include "Shape.h"

class Rectangle : public Shape{
private:
public:
	Point TopLeftCorner;
	Point BottomRightCorner;

public:
	Rectangle(Point TopLeftCorner, Point BottomRightCorner);
	double GetArea();
	bool ContainsPoint(Point P);
};