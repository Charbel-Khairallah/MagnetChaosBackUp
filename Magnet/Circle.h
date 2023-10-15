#pragma once
#include "Shape.h"

class Circle : public Shape {
private:
	Point Center;
	double Radius;

public:
	Circle(Point Center, double Radius);
	double GetArea();
	bool ContainsPoint(Point P);
};