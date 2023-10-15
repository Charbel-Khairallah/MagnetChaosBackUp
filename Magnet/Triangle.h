#pragma once
#include "Shape.h"

class Triangle : public Shape {
private:
	Point FirstCorner;
	Point SecondCorner;
	Point ThirdCorner;

public:
	Triangle(Point FirstCorner, Point SecondCorner, Point ThirdCorner);
	double GetArea();
	bool ContainsPoint(Point P);
};