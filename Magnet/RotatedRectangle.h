#pragma once
#include "Shape.h"
#include "Angle.h"

class RotatedRectangle : public Shape {
private:
public:
	Point FirstCorner;
	Point SecondCorner;
	Point ThirdCorner;
	Point FourthCorner;

	void Rearrange();

public:
	RotatedRectangle(Point FirstCorner, Point SecondCorner, Point ThirdCorner, Point FourthCorner);
	RotatedRectangle(Point Center, Dimension Size, Angle Rotation);
	double GetArea();
	bool ContainsPoint(Point P);

	Point GetCorner(int Index = 0);
};