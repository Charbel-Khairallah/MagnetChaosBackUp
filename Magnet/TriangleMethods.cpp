#pragma once
#include "Triangle.h"
#include "Methods.h"

//------------------------------------ Constructor ------------------------------------//

Triangle::Triangle(Point FirstCorner, Point SecondCorner, Point ThirdCorner) {
	this->FirstCorner = FirstCorner;
	this->SecondCorner = SecondCorner;
	this->ThirdCorner = ThirdCorner;
}

//----------------------------------- ContainsPoint -----------------------------------//

bool Triangle::ContainsPoint(Point P) {
	Triangle FirstSection(this->FirstCorner, this->SecondCorner, P);
	Triangle SecondSection(this->FirstCorner, this->ThirdCorner, P);
	Triangle ThirdSection(this->ThirdCorner, this->SecondCorner, P);

	double AreaDifference = (FirstSection.GetArea() + SecondSection.GetArea() + ThirdSection.GetArea()) - this->GetArea();

	return MT::AbsoluteValue(AreaDifference) < 0.000001;
}

//------------------------------------- Get Area -------------------------------------//

double Triangle::GetArea() {
	double X1 = this->FirstCorner.GetX();
	double Y1 = this->FirstCorner.GetY();
	double X2 = this->SecondCorner.GetX();
	double Y2 = this->SecondCorner.GetY();
	double X3 = this->ThirdCorner.GetX();
	double Y3 = this->ThirdCorner.GetY();
	return 0.5 * MT::AbsoluteValue((X1 * (Y2 - Y3) + X2 * (Y3 - Y1) + X3 * (Y1 - Y2)));
}