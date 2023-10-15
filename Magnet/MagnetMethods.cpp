#pragma once
#include "Magnet.h"
#include "Methods.h"
#include "Frame.h"

const double Magnet::ACCELERATION_LIMIT = 1;
const double Magnet::VELOCITY_LIMIT = 2.5;
const double Magnet::ACCELERATION_RATE = 0.0012;
const int Magnet::HIDING_LIMIT = 1'000; // 1 Second

//------------------------------------ Constructor ------------------------------------//

Magnet::Magnet(double PaddingRight, Bar * HealthBar, Bar * ShiftBar, UserInput Move, UserInput PositiveShift, UserInput NegativeShift, long& Score) : MovingObject(Magnet::VELOCITY_LIMIT, Magnet::ACCELERATION_LIMIT, Magnet::ACCELERATION_RATE){	
	this->StunnDuration = 1000;
	this->Amplifier = 1;
	this->DamageReduction = 1;
	this->Alive = true;

	this->StunnedTimer = NULL;
	this->HidingTimer = NULL;

	this->Score = &Score;
	this->PaddingRight = PaddingRight;
	this->HealthBar = HealthBar;
	this->ShiftBar = ShiftBar;
	this->Move = Move;
	this->PositiveShift = PositiveShift;
	this->NegativeShift = NegativeShift;
	this->Upgrade = Upgrade;

	double size = 20;
	double position = 500;

	if (!this->MagnetTexture.loadFromFile("../GameData/Images/Magnet.png")) {
		std::cout << "Could Not Load Texture." << std::endl;
	}
	this->MagnetShape.setTexture(&this->MagnetTexture);
	this->MagnetShape.setRadius(size);
	this->MagnetShape.setOrigin(size, size);
	this->MagnetShape.setPosition(position, position);
	this->MagnetShape.setFillColor(sf::Color(80, 80, 80, 255));

	if (!this->DirectionTexture.loadFromFile("../GameData/Images/Direction.png")) {
		std::cout << "Could Not Load Texture." << std::endl;
	}
	this->DirectionShape.setTexture(&this->DirectionTexture);
	this->DirectionShape.setSize(sf::Vector2f(2 * size, 2 * size));
	this->DirectionShape.setOrigin(size, size);
	this->DirectionShape.setPosition(position, position);

	this->DirectionShape.setFillColor(sf::Color(255, 255, 255, 255));

	/* Upgrades */

	for (int i = 1; i <= 25; i++) {
		this->UpgradePoints.push_back(400 * pow(i, 1.2));
	}
	this->AvailableUpgrades = 0;
}

Magnet::Magnet() : MovingObject(0, 0, 0) {}

//------------------------------------ Destructor ------------------------------------//

Magnet::~Magnet() {
	if (this->StunnedTimer != NULL) {
		delete StunnedTimer;
	}
	if (this->HidingTimer != NULL){
		delete this->HidingTimer;
	}
}

//--------------------------------------  Bounce ------------------------------------//

void Magnet::Bounce() {
	bool Stunned = false;

	double LeftX = this->MagnetShape.getGlobalBounds().left;
	double RightX = this->MagnetShape.getGlobalBounds().left + this->MagnetShape.getGlobalBounds().width;
	double TopY = this->MagnetShape.getGlobalBounds().top;
	double BottomY = this->MagnetShape.getGlobalBounds().top + this->MagnetShape.getGlobalBounds().height;

	double LeftLimitX = 0;
	double RightLimitX = GameWindow->getSize().x;
	double TopLimitY = 0;
	double BottomLimitY = GameWindow->getSize().y;

	if (LeftX <= LeftLimitX || RightX >= (RightLimitX - this->PaddingRight)) {
		if (LeftX <= LeftLimitX) {
			this->Acceleration = Dimension(MT::AbsoluteValue(this->Acceleration.GetWidth()), this->Acceleration.GetHeight());
			this->Velocity = Dimension(MT::AbsoluteValue(this->Velocity.GetWidth()), this->Velocity.GetHeight());
		}
		else {
			this->Acceleration = Dimension(-MT::AbsoluteValue(this->Acceleration.GetWidth()), this->Acceleration.GetHeight());
			this->Velocity = Dimension(-MT::AbsoluteValue(this->Velocity.GetWidth()), this->Velocity.GetHeight());
		}
		Stunned = true;
		this->CurrentRotation = Angle(180 - this->CurrentRotation.GetActualValue());
	}

	if (TopY <= TopLimitY || BottomY >= BottomLimitY) {
		if (TopY <= TopLimitY) {
			this->Acceleration = Dimension(this->Acceleration.GetWidth(), MT::AbsoluteValue(this->Acceleration.GetHeight()));
			this->Velocity = Dimension(this->Velocity.GetWidth(), MT::AbsoluteValue(this->Velocity.GetHeight()));
		}
		else {
			this->Acceleration = Dimension(this->Acceleration.GetWidth(), -MT::AbsoluteValue(this->Acceleration.GetHeight()));
			this->Velocity = Dimension(this->Velocity.GetWidth(), -MT::AbsoluteValue(this->Velocity.GetHeight()));
		}
		Stunned = true;
		this->CurrentRotation = Angle(-this->CurrentRotation.GetActualValue());
	}

	if (Stunned) {
		Frame::StunnSound.play();
		if (this->StunnedTimer != NULL) {
			delete StunnedTimer;
		}
		StunnedTimer = new sf::Clock();
		(*this->HealthBar) -= 5;
		this->ShiftBar->Reset();
		(*this->Score) -= 2 * MT::RoundUp(MT::AbsoluteValue(this->VelocityValue));
		
		if (this->HealthBar->GetValue() <= 0)this->Alive = false;
	}
}

//-------------------------------------- Refresh -------------------------------------//

void Magnet::Refresh() {
	if (this->StunnedTimer != NULL) {
		this->MagnetShape.setFillColor(MT::Shift(this->MagnetShape.getFillColor(), WARNING_COLOR, SLOW));

		if (this->StunnedTimer->getElapsedTime().asMilliseconds() >= this->StunnDuration) {
			delete this->StunnedTimer;
			this->StunnedTimer = NULL;
		}
	}
	else {
		this->MagnetShape.setFillColor(MT::Shift(this->MagnetShape.getFillColor(), this->ShiftBar->GetBarColor(), SLOW));
		
		this->Move.CheckState();
		this->PositiveShift.CheckState();
		this->NegativeShift.CheckState();
		this->Upgrade.CheckState();

		/* Moving */
		if (this->Move.IsActive()) {
			this->Accelerate();
		}
		else {
			this->Decelerate();
		}

		/* Positive Shift */
		if (this->PositiveShift.IsActive()) {
			++(*this->ShiftBar);
		}

		/* Negative Shift */
		if (this->NegativeShift.IsActive()) {
			--(*this->ShiftBar);
		}
	
	}

	Angle NewAngle;
	if (this->StunnedTimer == NULL) {
		NewAngle = Angle(Point(this->MagnetShape.getPosition().x, this->MagnetShape.getPosition().y), Point(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
		this->CurrentRotation.ShiftToAngle(NewAngle);
	}

	this->DirectionShape.setRotation(Angle::Clamp(this->CurrentRotation.GetActualValue()) + 45);
	this->MagnetShape.setRotation(Angle::Clamp(this->CurrentRotation.GetActualValue()));

		
	double AccelerationX = this->AccelerationValue * cos(Angle::ToRadian(this->CurrentRotation.GetActualValue()));
	double AccelerationY = this->AccelerationValue * sin(Angle::ToRadian(this->CurrentRotation.GetActualValue()));

	this->Acceleration = Dimension(AccelerationX, AccelerationY);

	double VelocityX = this->VelocityValue * cos(Angle::ToRadian(this->CurrentRotation.GetActualValue()));
	double VelocityY = this->VelocityValue * sin(Angle::ToRadian(this->CurrentRotation.GetActualValue()));

	this->Velocity = Dimension(VelocityX, VelocityY);

	this->Bounce();

	this->MagnetShape.setPosition(sf::Vector2f(this->MagnetShape.getPosition().x + this->Velocity.GetWidth(), this->MagnetShape.getPosition().y + this->Velocity.GetHeight()));
	this->DirectionShape.setPosition(sf::Vector2f(this->DirectionShape.getPosition().x + this->Velocity.GetWidth(), this->DirectionShape.getPosition().y + this->Velocity.GetHeight()));

	if (this->HidingTimer != NULL && this->HidingTimer->getElapsedTime().asMilliseconds() >= Magnet::HIDING_LIMIT) {
		this->TakeDamage(this->HealthBar->GetRate() * 5, false);
	}
	else {
		++(*this->HealthBar);
	}

	if (this->UpgradePoints.size() > 0 && (*this->Score) >= this->UpgradePoints[0]) {
		this->AvailableUpgrades++;
		this->UpgradePoints.erase(this->UpgradePoints.begin());
	}
}

//---------------------------------------- Draw --------------------------------------//

void Magnet::Draw() {
	GameWindow->draw(this->DirectionShape);
	GameWindow->draw(this->MagnetShape);
}

//-------------------------------- Get Available Upgrade -----------------------------//

int Magnet::GetAvailableUpgrades() {
	return this->AvailableUpgrades;
}

//---------------------------------- Upgrade Max Health ------------------------------//

void Magnet::UpgradeArmour() {
	this->AvailableUpgrades--;
	this->DamageReduction *= 0.92;
}

//------------------------------ Upgrade Regeneration Speed --------------------------//

void Magnet::UpgradeRegenerationSpeed() {
	this->AvailableUpgrades--;
	this->HealthBar->SetRate(this->HealthBar->GetRate() * 1.5);
}

//---------------------------------- Upgrade Max Shift -------------------------------//

void Magnet::UpgradePower() {
	this->AvailableUpgrades--;
	this->Amplifier *= 1.19;
}

//--------------------------------- Upgrade Shift Speed ------------------------------//

void Magnet::UpgradeShiftSpeed() {
	this->AvailableUpgrades--;
	this->ShiftBar->SetRate(this->ShiftBar->GetRate() * 2);
}

//------------------------------- Upgrade Stunn Duration -----------------------------//

void Magnet::UpgradeStunnDuration() {
	this->AvailableUpgrades--;
	this->StunnDuration *= 0.8;
}

//-------------------------------------- Is Dead -------------------------------------//

bool Magnet::IsDead() {
	return !this->Alive;
}

//--------------------------------------- Get X --------------------------------------//

double Magnet::GetX() {
	return this->DirectionShape.getGlobalBounds().left;
}

//--------------------------------------- Get Y --------------------------------------//

double Magnet::GetY() {
	return this->DirectionShape.getGlobalBounds().top;
}

//--------------------------------- Get Field Strength -------------------------------//

double Magnet::GetFieldStrength() {
	return (50 - this->ShiftBar->GetValue()) / 100.0 * this->Amplifier;
}
//----------------------------- Get Absolute Field Strength --------------------------//

double Magnet::GetAbsoluteFieldStrength() {
	return MT::AbsoluteValue(this->GetFieldStrength());
}

//---------------------- Get Max Field Strength Without Amplifier --------------------//

double Magnet::GetMaxFieldStrengthWithoutAmplifier() {
	return (50 / 100.0);
}

//----------------------------------- Get Boundaries ---------------------------------//

Circle Magnet::GetBoundaries() {
	Point Center(this->MagnetShape.getPosition().x, this->MagnetShape.getPosition().y);
	double Radius = this->MagnetShape.getRadius();
	return Circle(Center, Radius);
}

//------------------------------------ Take Damage ----------------------------------//

void Magnet::TakeDamage(double Damage, bool Stunn) {
	(*this->HealthBar) -= Damage * this->DamageReduction;

	if (Stunn) {
		if (this->StunnedTimer != NULL) {
			delete StunnedTimer;
		}
		StunnedTimer = new sf::Clock();
		this->ShiftBar->Reset();
		Frame::StunnSound.play();
	}

	if (this->HealthBar->GetValue() <= 0)this->Alive = false;
}

//-------------------------------- Start Hiding Timer -------------------------------//

void Magnet::StartHidingTimer() {
	if(this->HidingTimer == NULL)this->HidingTimer = new sf::Clock();
}

//-------------------------------- Reset Hiding Timer -------------------------------//

void Magnet::ResetHidingTimer() {
	if (this->HidingTimer != NULL) {
		delete this->HidingTimer;
		this->HidingTimer = NULL;
	}
}

//------------------------------------ Get Radius -----------------------------------//

double Magnet::GetRadius() {
	return this->MagnetShape.getRadius();
}