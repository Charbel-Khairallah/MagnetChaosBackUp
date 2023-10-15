#pragma once
#include "Dimension.h"
#include <iostream>

class Point {
private:
	double X;
	double Y;

public:
	Point();
	Point(double X, double Y);

	double GetX();
	double GetY();

	Point operator +(Dimension D);
	Point operator -(Dimension D);
	bool operator == (Point Other);
};