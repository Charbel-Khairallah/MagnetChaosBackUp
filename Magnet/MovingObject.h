#pragma once

class MovingObject {
private:
	long long ID;

protected:
	double AccelerationValue;
	double VelocityValue;

	double AccelerationLimit;
	double VelocityLimit;
	double AccelerationRate;
	
	void Accelerate();
	void Decelerate();
	
	void ClampAcceleration();
	void ClampVelocity();

public:
	MovingObject(double VelocityLimit = 0, double AcceleraitonLimit = 0, double AccelerationRate = 0);
	long long GetID();
};
