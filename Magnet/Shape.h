#pragma once
#include <iostream>
#include "Point.h"

class Shape {
private:

public:
	virtual bool ContainsPoint(Point P) = NULL;
	virtual double GetArea() = NULL;
	virtual ~Shape() {}
};