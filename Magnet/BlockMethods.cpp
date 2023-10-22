#pragma once
#include "Block.h"
#include "Frame.h"

int Block::CooldownDuration = 10'000; // 10 Seconds
int Block::FieldActivationDistance = 200;
sf::Clock Block::Timer;

//---------------------------------------- Init --------------------------------------//

void Block::Init() {
	this->MergeBlock = NULL;
	this->Field = NULL;
	this->MergePoint = Point(-1, -1);
	this->FieldIntensityFactor = 0;

	this->AlternativeBlockCreated = false;

	sf::Color FillColor = TRANSPARENT;
	if (this->Type == Iron) {
		this->BlockTexture = IRON;
	}
	else {
		this->BlockTexture = COPPER;
	}

	this->Size = Dimension(50, 50);

	this->IronBlock = sf::RectangleShape(sf::Vector2f(this->Size.GetWidth(), this->Size.GetHeight()));
	this->IronBlock.setOrigin(this->IronBlock.getOrigin().x + this->Size.GetWidth() / 2.0, this->IronBlock.getOrigin().y + this->Size.GetHeight() / 2.0);
	this->IronBlock.setTexture(&this->BlockTexture);
	this->IronBlock.setFillColor(FillColor);
}

//------------------------------------ Constructor -----------------------------------//

Block::Block(BlockType Type){
	Block::Timer.restart();

	this->State = Default;
	this->Type = Type;
	this->Player = NULL;
	this->FieldPower = 0;

	this->Init();

	this->GenerateRandomState();
}

Block::Block(BlockType Type, Point Position, Angle Rotation, Magnet * Player) {
	this->State = FadingIn;
	this->Type = Type;
	this->Position = Position;
	this->Rotation = Rotation;
	this->Velocity = Dimension(0, 0);
	this->VelocityLimit = 0;
	this->VelocityValue = 0;
	this->VelocityX = 0;
	this->VelocityY = 0;
	this->Acceleration = Dimension(0, 0);
	this->AccelerationLimit = 0;
	this->AccelerationRate = 0;
	this->AccelerationRate = 0;
	this->Player = Player;
	this->FieldPower = 400;
	if (this->Player != NULL)this->FieldPower *= this->Player->GetPower();

	this->Init();

	this->IronBlock.setRotation(this->Rotation.GetActualValue());
	this->IronBlock.setPosition(Position.GetX(), Position.GetY());

	this->Field = NULL;
	if (this->Type == Copper) {
		this->Field = new MagneticField(this->GetPosition(), this->GetSize());
	}
}

Block::Block(){
	
}

//------------------------------------- Destructor -----------------------------------//

Block::~Block() {
	if (this->Field != NULL)delete this->Field;
	this->Field = NULL;
}

//------------------------------- Generate Random State ------------------------------//

void Block::GenerateRandomState() {
	double X, Y;
	MT::GenerateRandomState(this->Size, X, Y, this->Rotation);

	this->VelocityLimit = MT::GenerateRandomInteger(300, 500) / 100.0;
	this->VelocityValue = MT::GenerateRandomInteger(100, 300) / 500.0;
	this->AccelerationLimit = MT::GenerateRandomInteger(50, 150) / 100.0;
	this->AccelerationRate = 0;
	this->AccelerationValue = 0;

	this->IronBlock.setPosition(X, Y);
	this->IronBlock.setRotation(this->Rotation.GetActualValue());

	this->VelocityX = this->VelocityValue * cos(Angle::ToRadian(this->Rotation.GetActualValue()));
	this->VelocityY = this->VelocityValue * sin(Angle::ToRadian(this->Rotation.GetActualValue()));
}

//-------------------------------------- Refresh -------------------------------------//

void Block::Refresh() {
	if (this->State == Default) {
		this->IronBlock.setFillColor(MT::Shift(this->IronBlock.getFillColor(), COLOR, SLOW));
		if (this->Type == Iron) {
			this->AccelerationValue += this->AccelerationRate;
			if (this->AccelerationValue < 0)this->AccelerationValue = 0;

			this->VelocityX += this->Acceleration.GetWidth();
			this->VelocityY += this->Acceleration.GetHeight();

			this->Velocity = Dimension(VelocityX, VelocityY);
			this->VelocityValue = this->Velocity.GetLength();
		}
		else {
			double Distance = Dimension(this->GetPosition().GetX() - this->Player->GetX(), this->GetPosition().GetY() - this->Player->GetY()).GetLength();
			double Factor = Distance / (double)Block::FieldActivationDistance;
			if (Factor <= 1) {
				Factor = (1 - Factor) * (this->Player->GetAbsoluteFieldStrength() / (double)this->Player->GetMaxFieldStrengthWithoutAmplifier());
				this->FieldPower -= sqrt(Factor);
				if (this->Field != NULL)this->Field->Refresh(Factor);
				this->IronBlock.setFillColor(MT::Mix(FIELD_COLOR, COLOR, Factor));
				this->FieldIntensityFactor = Factor;
			} 
			else {
				this->FieldIntensityFactor = 0;
			}
			if (this->FieldPower <= 0) {
				this->State = CopperDestruction;
				this->Field->FadeOut();
			}
		}
	}
	else if (this->State == Merging) {
		if (this->MergePoint.GetX() < 0 && this->MergePoint.GetY() < 0) {
			this->MergePoint = MT::Shift(this->GetPosition(), this->MergeBlock->GetPosition(), 1); // MID
			this->MergeBlock->SetMergePoint(this->MergePoint);
		}
		Angle AngleBetweenBlocks(this->GetPosition(), this->MergePoint);
		if (Dimension(this->GetPosition().GetX() - this->MergePoint.GetX(), this->GetPosition().GetY() - this->MergePoint.GetY()).GetLength() <= this->VelocityLimit) {
			this->VelocityX = 0;
			this->VelocityY = 0;
			this->Rotation.ShiftToAngle(0, 0.12);
			if (this->Rotation.GetActualValue() <= 0.5 || this->Rotation.GetActualValue() >= 359.5)this->Rotation = Angle(0);
		}
		else {
			this->Rotation.ShiftToAngle(AngleBetweenBlocks, 0.06);
			this->VelocityX = this->VelocityValue * cos(Angle::ToRadian(this->Rotation.GetActualValue())) * 0.98;
			this->VelocityY = this->VelocityValue * sin(Angle::ToRadian(this->Rotation.GetActualValue())) * 0.98;
		}

		this->Velocity = Dimension(this->VelocityX, this->VelocityY);
		this->VelocityValue = this->Velocity.GetLength();
		
		if (this->VelocityValue <= 0.1) {
			this->SetState(FadingOut);
		}
	}
	else if (this->State == FadingOut) {
		if(this->MergeBlock == NULL || this->MergeBlock->GetState() == FadingOut)
			this->IronBlock.setFillColor(MT::Shift(this->IronBlock.getFillColor(), TRANSPARENT, SLOW));

		if (this->IronBlock.getFillColor() == TRANSPARENT) {
			this->State = Disabled;
		}
	}
	else if (this->State == FadingIn) {
		this->IronBlock.setFillColor(MT::Shift(this->IronBlock.getFillColor(), COLOR, SLOW));

		if (this->IronBlock.getFillColor() == COLOR) {
			this->State = Default;
		}
	}
	else if (this->State == CopperDestruction) {
		this->IronBlock.setFillColor(MT::Shift(this->IronBlock.getFillColor(), TRANSPARENT, SLOW));
		this->Field->Refresh(this->Field->GetIntensity());

		if (this->IronBlock.getFillColor() == TRANSPARENT) {
			this->State = Disabled;
		}
	}

	Point NewPosition = Point(this->IronBlock.getPosition().x + this->Velocity.GetWidth(), this->IronBlock.getPosition().y + this->Velocity.GetHeight());
	if(this->MergeBlock != NULL)NewPosition = MT::Shift(NewPosition, this->MergeBlock->GetPosition(), 20);

	this->IronBlock.setPosition(sf::Vector2f(NewPosition.GetX(), NewPosition.GetY()));

	Angle AngleToShiftTo = Angle(Point(this->IronBlock.getGlobalBounds().left, this->IronBlock.getGlobalBounds().top), Point(this->IronBlock.getGlobalBounds().left, this->IronBlock.getGlobalBounds().top) + Dimension(this->VelocityX, this->VelocityY));
	this->Rotation.ShiftToAngle(AngleToShiftTo, 0.01);
	this->IronBlock.setRotation(this->Rotation.GetActualValue());
}

//---------------------------------------- Draw --------------------------------------//

void Block::Draw() {
	GameWindow->draw(this->IronBlock);
	if (this->Field != NULL)this->Field->Draw();
}

//---------------------------------- Intersects With ---------------------------------//

bool Block::IntersectsWith(Block * Other) {
	bool Result;
	RotatedRectangle ThisBoundaries = this->GetBoundaries();
	RotatedRectangle OtherBoundaries = Other->GetBoundaries();
	Result = ThisBoundaries.ContainsPoint(OtherBoundaries.GetCorner(0))
		||
		ThisBoundaries.ContainsPoint(OtherBoundaries.GetCorner(1))
		||
		ThisBoundaries.ContainsPoint(OtherBoundaries.GetCorner(2))
		||
		ThisBoundaries.ContainsPoint(OtherBoundaries.GetCorner(3))
		;
	Dimension ThisBlockVelocity(this->GetVelocityX(), this->GetVelocityY());
	Dimension OtherBlockVelocity(Other->GetVelocityX(), Other->GetVelocityY());

	if (Result && ((ThisBlockVelocity - OtherBlockVelocity).GetLength() >= this->VelocityLimit)) {
		Result = false;
		this->MergeWith(Other);
	}

	if (Result)Frame::BlockCollisionSound.play();
	return Result;
}

//-------------------------------------- Bounce --------------------------------------//

void Block::BounceOff(Block * Other) {
	Dimension OldVelocity(this->VelocityX, this->VelocityY);

	this->VelocityX = Other->GetVelocityX();
	this->VelocityY = Other->GetVelocityY();

	Other->SetVelocityX(OldVelocity.GetWidth());
	Other->SetVelocityY(OldVelocity.GetHeight());
}

//---------------------------------- Move Away From ----------------------------------//

void Block::MoveAwayFrom(Block * Other) {
	double Factor = 0.5;
	double VelocityShift = this->VelocityLimit * Factor;

	Angle BlocksAngle(this->GetPosition(), Other->GetPosition());
	double VelocityShiftX = VelocityShift * cos(Angle::ToRadian(BlocksAngle.GetActualValue()));
	double VelocityShiftY = VelocityShift * sin(Angle::ToRadian(BlocksAngle.GetActualValue()));

	this->SetVelocityX(this->GetVelocityX() + VelocityShiftX);
	this->SetVelocityY(this->GetVelocityY() + VelocityShiftY);

	Other->SetVelocityX(Other->GetVelocityX() - VelocityShiftX);
	Other->SetVelocityY(Other->GetVelocityY() - VelocityShiftY);

}

//----------------------------- Get Field Intensity Factor ----------------------------//

double Block::GetFieldIntensityFactor() {
	return this->FieldIntensityFactor;
}

//------------------------------------ Get Rotation -----------------------------------//

Angle Block::GetRotation() {
	return this->Rotation;
}

//------------------------------------- Get Position ----------------------------------//

Point Block::GetPosition() {
	return Point(this->IronBlock.getGlobalBounds().left, this->IronBlock.getGlobalBounds().top) + Dimension(this->IronBlock.getGlobalBounds().width / 2.0, this->IronBlock.getGlobalBounds().height / 2.0);
}

//-------------------------------------- Get Center -----------------------------------//

Point Block::GetCenter() {
	return Point(this->IronBlock.getPosition().x, this->IronBlock.getPosition().y);
}

//-------------------------------------- Get Size -------------------------------------//

Dimension Block::GetSize() {
	return this->Size;
}

//-------------------------------------- Get Type -------------------------------------//

BlockType Block::GetType() {
	return this->Type;
}

//------------------------------------ In Cooldown ------------------------------------//

bool Block::InCooldown() {
	return Block::Timer.getElapsedTime().asMilliseconds() <= Block::CooldownDuration;
}

//------------------------------------ Is Visible ------------------------------------//

bool Block::IsOutOfBounds() {
	return
		(
			(this->IronBlock.getGlobalBounds().left >= (GameWindow->getSize().x + 2 * this->IronBlock.getGlobalBounds().width))
			||
			(this->IronBlock.getGlobalBounds().left <= (-2 * this->IronBlock.getGlobalBounds().width))
			||
			(this->IronBlock.getGlobalBounds().top >= (GameWindow->getSize().y + 2 * this->IronBlock.getGlobalBounds().height))
			||
			(this->IronBlock.getGlobalBounds().top <= (-2 * this->IronBlock.getGlobalBounds().height))
		);
}


//------------------------------- Interact With Magnet -------------------------------//

void Block::InteractWithMagnet(Point MagnetPosition, double FieldStrength) { 
	if (this->State == Default) {
		if (this->Type == Iron) {
			Dimension Distance(MT::AbsoluteValue(MagnetPosition.GetX() - this->IronBlock.getGlobalBounds().left), MT::AbsoluteValue(MagnetPosition.GetY() - this->IronBlock.getGlobalBounds().top));
			if (Distance.GetLength() < 400 && Distance.GetLength() > 0 && FieldStrength != 0) {
				Angle Direction(Point(this->IronBlock.getGlobalBounds().left, this->IronBlock.getGlobalBounds().top), MagnetPosition);
				if (FieldStrength < 0) {
					FieldStrength = -FieldStrength;
					Direction = Angle(Direction.GetActualValue() + 180);
				}

				FieldStrength = FieldStrength / sqrt(Distance.GetLength());

				this->AccelerationRate = 0.0005 * FieldStrength;
				double AccelerationX = this->AccelerationValue * cos(Angle::ToRadian(Direction.GetActualValue()));
				double AccelerationY = this->AccelerationValue * sin(Angle::ToRadian(Direction.GetActualValue()));

				this->Acceleration = Dimension(AccelerationX, AccelerationY);

				this->Rotation.ShiftToAngle(Direction, pow(FieldStrength, 1.5));
			}
			else {
				this->AccelerationRate = 0;
				this->AccelerationValue = 0;
				this->Acceleration = Dimension(0, 0);
			}
		}
		else {
			
		}
	}
}

//------------------------------- Clear Collision Block -------------------------------//

void Block::ResetCollisionBlock() {
	this->LastCollisionBlocks = this->CurrentCollisionBlocks;
	this->CurrentCollisionBlocks.clear();
}

//----------------------------------- Get Velocity X -----------------------------------//

double Block::GetVelocityX() {
	return this->VelocityX;
}

//----------------------------------- Get Velocity Y -----------------------------------//

double Block::GetVelocityY() {
	return this->VelocityY;
}

//----------------------------------- Set Velocity X -----------------------------------//

void Block::SetVelocityX(double NewVelocityValue) {
	this->VelocityX = NewVelocityValue;
}

//----------------------------------- Set Velocity Y -----------------------------------//

void Block::SetVelocityY(double NewVelocityValue) {
	this->VelocityY = NewVelocityValue;
}

//------------------------------- Last Collision Was Null -------------------------------//

bool Block::InCollisionWith(Block * Other) {
	return (this->LastCollisionBlocks.find(Other->GetID()) != this->LastCollisionBlocks.end());
}

//------------------------------- Void Set Collision Block -------------------------------//

void Block::AddCollisionBlock(Block * Other) {
	this->CurrentCollisionBlocks.insert(Other->GetID());
}

//------------------------------------- In Collosion -------------------------------------//

bool Block::InCollision() {
	return this->CurrentCollisionBlocks.size() > 0;
}

//--------------------------------------- Get State --------------------------------------//

BlockState Block::GetState() {
	return this->State;
}

//--------------------------------------- Merge With -------------------------------------//

void Block::MergeWith(Block * Other) {
	this->SetMergeBlock(Other);
	Other->SetMergeBlock(this);
}

//---------------------------------------- Set State -------------------------------------//

void Block::SetState(BlockState NewState) {
	this->State = NewState;
}

//------------------------------------- Set Merge Block ----------------------------------//

void Block::SetMergeBlock(Block * Other) {
	this->MergeBlock = Other;
	this->SetState(Merging);
	if (Other != NULL)Other->SetState(Merging);
}

//------------------------------------- Get Merge Block ----------------------------------//

Block * Block::GetMergeBlock() {
	return this->MergeBlock;
}

//------------------------------------- Set Merge Point ----------------------------------//

void Block::SetMergePoint(Point MergePoint) {
	this->MergePoint = MergePoint;
}

//----------------------------------- Create Copper Block --------------------------------//

void Block::CreateAlternativeBlock() {
	this->AlternativeBlockCreated = true;
}

//------------------------------------- Is Copper Block ----------------------------------//

bool Block::IsAlternativeBlockCreated() {
	return this->AlternativeBlockCreated;
}

//-------------------------------------- Get Boundaries ----------------------------------//

RotatedRectangle Block::GetBoundaries() {
	return RotatedRectangle(this->GetPosition(), this->GetSize(), this->GetRotation());
}

//----------------------------------- Get Field Boundaries -------------------------------//

Circle Block::GetFieldBoundaries() {
	if (this->Field == NULL){
		return Circle(Point(0, 0), 0);
	}
	return this->Field->GetBoundaries();
}
