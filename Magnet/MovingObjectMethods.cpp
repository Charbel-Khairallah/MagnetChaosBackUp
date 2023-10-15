#pragma once
#include <iostream>

#include "MovingObject.h"
#include "Methods.h"

//------------------------------------ Constructor -----------------------------------//

MovingObject::MovingObject(double VelocityLimit, double AcceleraitonLimit, double AccelerationRate) {
	this->ID = MT::GenerateUniqueID();
	this->AccelerationValue = 0;
	this->VelocityValue = 0;

	this->AccelerationLimit = AcceleraitonLimit;
	this->VelocityLimit = VelocityLimit;
	this->AccelerationRate = AccelerationRate;
}

//------------------------------------- Accelerate -----------------------------------//

void MovingObject::Accelerate() {
	this->AccelerationValue += this->AccelerationRate;
	this->ClampAcceleration();

	this->VelocityValue += AccelerationValue;
	this->ClampVelocity();
}

//------------------------------------- Decelerate -----------------------------------//

void MovingObject::Decelerate() {
	this->AccelerationValue -= this->AccelerationValue * 0.015;
	if (MT::AbsoluteValue(this->AccelerationValue) < this->AccelerationRate)this->AccelerationValue = 0;
	this->VelocityValue -= this->VelocityValue * 0.015;
	if (MT::AbsoluteValue(this->VelocityValue) < this->AccelerationRate)this->VelocityValue = 0;
}

//--------------------------------- Clamp Acceleration -------------------------------//

void MovingObject::ClampAcceleration() {
	if (this->AccelerationValue > this->AccelerationLimit)this->AccelerationValue = this->AccelerationLimit;
	if (this->AccelerationValue < -this->AccelerationLimit)this->AccelerationValue = -this->AccelerationLimit;
}

//----------------------------------- Clamp Velocity ---------------------------------//

void MovingObject::ClampVelocity() {
	if (this->VelocityValue > this->VelocityLimit)this->VelocityValue = this->VelocityLimit;
	if (this->VelocityValue < -this->VelocityLimit)this->VelocityValue = -this->VelocityLimit;
}

//-------------------------------------- Get ID --------------------------------------//

long long MovingObject::GetID() {
	return this->ID;
}