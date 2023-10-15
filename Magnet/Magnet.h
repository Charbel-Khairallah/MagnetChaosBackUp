#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Angle.h"
#include "Dimension.h"
#include "MovingObject.h"
#include "Bar.h"
#include "UserInput.h"
#include "Circle.h"

class Magnet : public MovingObject {
private:
	static const double ACCELERATION_LIMIT;
	static const double VELOCITY_LIMIT;
	static const double ACCELERATION_RATE;
	static const int HIDING_LIMIT;

	long * Score;
	double PaddingRight;

	int StunnDuration;
	double Amplifier;
	double DamageReduction;

	bool Alive;

	std::vector<int> UpgradePoints;
	int AvailableUpgrades;

	sf::CircleShape MagnetShape;
	sf::RectangleShape DirectionShape;

	sf::Texture MagnetTexture;
	sf::Texture DirectionTexture;

	Angle CurrentRotation;

	sf::Color PositiveColor;
	sf::Color NegativeColor;

	Dimension Velocity;
	Dimension Acceleration;

	sf::Clock * StunnedTimer;
	sf::Clock * HidingTimer;

	Bar * HealthBar;
	Bar * ShiftBar;

	UserInput Move;
	UserInput PositiveShift;
	UserInput NegativeShift;
	UserInput Upgrade;

	void Bounce();

public:
	Magnet();
	Magnet(double PaddingRight, Bar * HealthBar, Bar * ShiftBar, UserInput Move, UserInput PositiveShift, UserInput NegativeShift, long &Score);
	~Magnet();

	void Refresh();
	void Draw();

	int GetAvailableUpgrades();
	bool IsDead();
	
	void UpgradeArmour();
	void UpgradeRegenerationSpeed();
	void UpgradePower();
	void UpgradeShiftSpeed();
	void UpgradeStunnDuration();
	void TakeDamage(double Damage, bool Stunn = true);
	void StartHidingTimer();
	void ResetHidingTimer();

	double GetX();
	double GetY();
	double GetFieldStrength();
	double GetAbsoluteFieldStrength();
	double GetMaxFieldStrengthWithoutAmplifier();
	double GetRadius();
	Circle GetBoundaries();
};