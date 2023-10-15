#pragma once
#include "Rectangle.h"
#include "Methods.h"

//------------------------------------ Constructor ------------------------------------//

Rectangle::Rectangle(Point TopLeftCorner, Point BottomRightCorner) {
	this->TopLeftCorner = TopLeftCorner;
	this->BottomRightCorner = BottomRightCorner;
}

//----------------------------------- ContainsPoint -----------------------------------//

bool Rectangle::ContainsPoint(Point P) {
	return P.GetX() >= this->TopLeftCorner.GetX() && P.GetX() <= this->BottomRightCorner.GetX()
		&& P.GetY() >= this->TopLeftCorner.GetY() && P.GetY() <= this->BottomRightCorner.GetY();
}

//------------------------------------- Get Area -------------------------------------//

double Rectangle::GetArea() {
	Dimension RectangleSize(MT::AbsoluteValue(this->TopLeftCorner.GetX() - this->BottomRightCorner.GetX()), MT::AbsoluteValue(this->TopLeftCorner.GetY() - this->BottomRightCorner.GetY()));
	return RectangleSize.GetWidth() * RectangleSize.GetHeight();
}