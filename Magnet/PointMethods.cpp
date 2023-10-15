#pragma once
#include "Point.h"

//------------------------------------ Constructors -----------------------------------//

Point::Point() {
	this->X = this->Y = 0;
}

Point::Point(double X, double Y) {
	this->X = X;
	this->Y = Y;
}

//---------------------------------------- GetX ---------------------------------------//

double Point::GetX() {
	return this->X;
}

//---------------------------------------- GetY ---------------------------------------//

double Point::GetY() {
	return this->Y;
}


//------------------------------------- + Operator ------------------------------------//

Point Point::operator + (Dimension D) {
	return Point(this->X + D.GetWidth(), this->Y + D.GetHeight());
}

//------------------------------------- - Operator ------------------------------------//

Point Point::operator - (Dimension D) {
	return Point(this->X - D.GetWidth(), this->Y - D.GetHeight());
}

//------------------------------------- == Operator -----------------------------------//

bool Point::operator == (Point Other) {
	return this->X == Other.GetX() && this->Y == Other.GetY();
}