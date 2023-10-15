#pragma once
#include "Point.h"

class Angle {
private:
	double Value;

public:
	Angle();
	Angle(double Value);
	Angle(Point First, Point Second);

	static double ToDegree(double Value);
	static double ToRadian(double Value);
	static double Clamp(double Value);

	double GetActualValue();

	void ShiftToAngle(Angle Other);
	void ShiftToAngle(Angle Other, double Factor);
};