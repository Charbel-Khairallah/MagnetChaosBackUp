#pragma once
#include "Triangle.h"
#include "RotatedRectangle.h"
#include "Methods.h"

#include "Frame.h"

//------------------------------------ Constructors ------------------------------------//

RotatedRectangle::RotatedRectangle(Point FirstCorner, Point SecondCorner, Point ThirdCorner, Point FourthCorner) {
	this->FirstCorner = FirstCorner;
	this->SecondCorner = SecondCorner;
	this->ThirdCorner = ThirdCorner;
	this->FourthCorner = FourthCorner;

	this->Rearrange();
}

RotatedRectangle::RotatedRectangle(Point Center, Dimension Size, Angle Rotation) {
	double AngleInRadian = Angle::ToRadian(Rotation.GetActualValue());
	double X, Y;

	Point FirstCornerBeforeTransformation(Size.GetWidth() / 2.0, Size.GetHeight() / 2.0);
	Point SecondCornerBeforeTransformation(Size.GetWidth() / 2.0, - Size.GetHeight() / 2.0);
	Point ThirdCornerBeforeTransformation(- Size.GetWidth() / 2.0, - Size.GetHeight() / 2.0);
	Point FourthCornerBeforeTransformation(- Size.GetWidth() / 2.0, Size.GetHeight() / 2.0);

	X = FirstCornerBeforeTransformation.GetX() * cos(AngleInRadian) - FirstCornerBeforeTransformation.GetY() * sin(AngleInRadian);
	Y = FirstCornerBeforeTransformation.GetX() * sin(AngleInRadian) + FirstCornerBeforeTransformation.GetY() * cos(AngleInRadian);
	this->FirstCorner = Point(Center.GetX() + X, Center.GetY() + Y);

	X = SecondCornerBeforeTransformation.GetX() * cos(AngleInRadian) - SecondCornerBeforeTransformation.GetY() * sin(AngleInRadian);
	Y = SecondCornerBeforeTransformation.GetX() * sin(AngleInRadian) + SecondCornerBeforeTransformation.GetY() * cos(AngleInRadian);
	this->SecondCorner = Point(Center.GetX() + X, Center.GetY() + Y);

	X = ThirdCornerBeforeTransformation.GetX() * cos(AngleInRadian) - ThirdCornerBeforeTransformation.GetY() * sin(AngleInRadian);
	Y = ThirdCornerBeforeTransformation.GetX() * sin(AngleInRadian) + ThirdCornerBeforeTransformation.GetY() * cos(AngleInRadian);
	this->ThirdCorner = Point(Center.GetX() + X, Center.GetY() + Y);

	X = FourthCornerBeforeTransformation.GetX() * cos(AngleInRadian) - FourthCornerBeforeTransformation.GetY() * sin(AngleInRadian);
	Y = FourthCornerBeforeTransformation.GetX() * sin(AngleInRadian) + FourthCornerBeforeTransformation.GetY() * cos(AngleInRadian);
	this->FourthCorner = Point(Center.GetX() + X, Center.GetY() + Y);

}

//------------------------------------- Rearrange -------------------------------------//

void RotatedRectangle::Rearrange() {
	// Make Sure  That The Points Are In Order
	Dimension FirstLength(MT::AbsoluteValue(this->FirstCorner.GetX() - this->SecondCorner.GetX()), MT::AbsoluteValue(this->FirstCorner.GetY() - this->SecondCorner.GetY()));
	Dimension SecondLength(MT::AbsoluteValue(this->FirstCorner.GetX() - this->FourthCorner.GetX()), MT::AbsoluteValue(this->FirstCorner.GetY() - this->FourthCorner.GetY()));
	Dimension ThirdLength(MT::AbsoluteValue(this->FirstCorner.GetX() - this->ThirdCorner.GetX()), MT::AbsoluteValue(this->FirstCorner.GetY() - this->ThirdCorner.GetY()));

	if (ThirdLength.GetLength() < SecondLength.GetLength() || ThirdLength.GetLength() < FirstLength.GetLength()) {
		Point Temp = this->ThirdCorner;
		if (SecondLength.GetLength() > FirstLength.GetLength()) {
			this->ThirdCorner = this->FourthCorner;
			this->FourthCorner = Temp;
		}
		else {
			this->ThirdCorner = this->SecondCorner;
			this->SecondCorner = Temp;
		}
	}
}

//------------------------------------- Get Area -------------------------------------//

double RotatedRectangle::GetArea() {
	Dimension FirstSide(MT::AbsoluteValue(this->FirstCorner.GetX() - this->SecondCorner.GetX()), MT::AbsoluteValue(this->FirstCorner.GetY() - this->SecondCorner.GetY()));
	Dimension SecondSide(MT::AbsoluteValue(this->FirstCorner.GetX() - this->FourthCorner.GetX()), MT::AbsoluteValue(this->FirstCorner.GetY() - this->FourthCorner.GetY()));

	return FirstSide.GetLength() * SecondSide.GetLength();
}

//---------------------------------- Contains Point ----------------------------------//

bool RotatedRectangle::ContainsPoint(Point P) {
	Triangle FirstSection(this->FirstCorner, this->SecondCorner, P);
	Triangle SecondSection(this->SecondCorner, this->ThirdCorner, P);
	Triangle ThirdSection(this->ThirdCorner, this->FourthCorner, P);
	Triangle FourthSection(this->FourthCorner, this->FirstCorner, P);

	double AreaDifference = (FirstSection.GetArea() + SecondSection.GetArea() + ThirdSection.GetArea() + FourthSection.GetArea()) - this->GetArea();

	return MT::AbsoluteValue(AreaDifference) < 0.0000001;
}

//------------------------------------ Get Corner ------------------------------------//

Point RotatedRectangle::GetCorner(int Index) {
	switch (Index)
	{
		case 0: {
			return this->FirstCorner;
		}
		case 1: {
			return this->SecondCorner;
		}
		case 2: {
			return this->ThirdCorner;
		}
		case 3: {
			return this->FourthCorner;
		}
	}
	return Point(0, 0);
}