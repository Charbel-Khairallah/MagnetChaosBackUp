#pragma once
#include <cmath>

#include "Circle.h"
#include "Config.h"

//------------------------------------ Constructor ------------------------------------//

Circle::Circle(Point Center, double Radius) {
	this->Center = Center;
	this->Radius = Radius;
}

//----------------------------------- ContainsPoint -----------------------------------//

bool Circle::ContainsPoint(Point P) {
	double DeltaX = P.GetX() - this->Center.GetX();
	double DeltaY = P.GetY() - this->Center.GetY();
	return (sqrt(DeltaX * DeltaX + DeltaY * DeltaY) <= this->Radius);
}

//------------------------------------- Get Area -------------------------------------//

double Circle::GetArea() {
	return PI * this->Radius * this->Radius;
}