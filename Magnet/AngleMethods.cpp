#include "Angle.h"
#include "Config.h"
#include "Methods.h"

//------------------------------------ Constructors ------------------------------------//

Angle::Angle() {
	this->Value = 0;
}

Angle::Angle(double Value) {
	this->Value = Angle::Clamp(Value);
}


Angle::Angle(Point First, Point Second) {
	if (First == Second)this->Value = 0;
	else {
		double Width = Second.GetX() - First.GetX();
		double Height = Second.GetY() - First.GetY();
		double Result = 90 - Angle::ToDegree(atan2(Width, Height));

		this->Value = Angle::Clamp(Result);
	}
}

//--------------------------------- Get Angle In Degrees ---------------------------------//

double Angle::ToDegree(double Value) {
	return Value * 180.0 / PI;
}

//--------------------------------- Get Angle In Radians ---------------------------------//

double Angle::ToRadian(double Value) {
	return Value * PI / 180.0;
}

//----------------------------------- Get Actual Value -----------------------------------//

double Angle::GetActualValue() {
	return this->Value;
}

//------------------------------------- Clamp A Value ------------------------------------//

double Angle::Clamp(double Value) {
	while (Value < 0)Value += 360;
	while (Value >= 360)Value -= 360;
	return Value;
}

//------------------------------------- Shift To Angle -----------------------------------//

void Angle::ShiftToAngle(Angle Other) {
	if (MT::AbsoluteValue(Angle::Clamp(this->Value) - Angle::Clamp(Other.GetActualValue())) <= 180) {
		this->Value = (29 * this->Value + Other.GetActualValue()) / 30.0;
	}
	else {
		if (Angle::Clamp(this->Value) > Angle::Clamp(Other.GetActualValue())) {
			this->Value -= 360;
			this->Value = (29 * this->Value + Other.GetActualValue()) / 30.0;
			this->Value = Angle::Clamp(this->Value);
		}
		else {
			double OtherAngleValue = Angle::Clamp(Other.GetActualValue()) - 360;
			this->Value = (29 * this->Value + OtherAngleValue) / 30.0;
			this->Value = Angle::Clamp(this->Value);
		}
	}
}


//------------------------------------- Shift To Angle -----------------------------------//

void Angle::ShiftToAngle(Angle Other, double Factor) {
	if (MT::AbsoluteValue(Angle::Clamp(this->Value) - Angle::Clamp(Other.GetActualValue())) <= 180) {
		this->Value = (this->Value + Other.GetActualValue() * Factor) / (double)(Factor + 1);
	}
	else {
		if (Angle::Clamp(this->Value) > Angle::Clamp(Other.GetActualValue())) {
			this->Value -= 360;
			this->Value = (this->Value + Other.GetActualValue() * Factor) / (double)(Factor + 1);
			this->Value = Angle::Clamp(this->Value);
		}
		else {
			double OtherAngleValue = Angle::Clamp(Other.GetActualValue()) - 360;
			this->Value = (this->Value + OtherAngleValue * Factor) / (double)(Factor + 1);
			this->Value = Angle::Clamp(this->Value);
		}
	}
}
