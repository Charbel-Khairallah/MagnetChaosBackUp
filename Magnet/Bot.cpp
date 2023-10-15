#pragma once
#include "Bot.h"
#include "RotatedRectangle.h"
#include "Dimension.h"
#include "Circle.h"

int Bot::CooldownDuration = 20'000; // 20 Seconds
int Bot::StunnDuration = 400;		//0.4 Seconds
int Bot::BlockDetectionDistance = 40;
double Bot::DamageAmplifier = 1;
double Bot::MaxSpeed = 2;
sf::Clock Bot::Timer;

//------------------------------------ Reset ------------------------------------//

void Bot::Reset() {
	Bot::CooldownDuration = 20'000;
	Bot::StunnDuration = 400;		//0.4 Seconds
	Bot::BlockDetectionDistance = 40;
	Bot::DamageAmplifier = 1;
	Bot::MaxSpeed = 2;
	Bot::Timer.restart();
}

//------------------------------------ Constructor ------------------------------------//

Bot::Bot(Magnet* Player, std::vector<Block* > & Blocks, long & Score) : MovingObject(Bot::MaxSpeed, 0.1, 0.001), Blocks(Blocks), Score(Score) {
	Bot::Timer.restart();

	this->Player = Player;
	this->Health = 100;
	this->CollisionTimer = NULL;
	this->Alive = true;
	this->AffectedByField = false;

	double X, Y;
	MT::GenerateRandomState(this->GetSize(), X, Y, this->Rotation);

	this->BotShape = sf::RectangleShape(sf::Vector2f(30, 30));
	this->BotShape.setTexture(&BOT);
	this->BotShape.setFillColor(ERROR_COLOR);
	this->BotShape.setPosition(X, Y);
	this->BotShape.setRotation(this->Rotation.GetActualValue());
	this->BotShape.setOrigin(this->BotShape.getOrigin().x + this->BotShape.getGlobalBounds().width / 2.0, this->BotShape.getOrigin().y + this->BotShape.getGlobalBounds().height / 2.0);

	this->BotHealthShape = sf::RectangleShape(this->BotShape.getSize());
	this->BotHealthShape.setTexture(&H100);
	this->BotHealthShape.setFillColor(WARNING_COLOR);
	this->BotHealthShape.setPosition(this->BotShape.getPosition());
	this->BotHealthShape.setRotation(this->BotShape.getRotation());
	this->BotHealthShape.setOrigin(this->BotShape.getOrigin());

	this->VelocityValue = 0;
	this->AccelerationValue = 0;
}

//------------------------------------- Destructor ------------------------------------//

Bot::~Bot() {
	
}

//-------------------------------------- Refresh --------------------------------------//

void Bot::Refresh() {
	Point BotPosition(this->BotShape.getGlobalBounds().left + this->BotShape.getSize().x / 2.0, this->BotShape.getGlobalBounds().top + this->BotShape.getSize().y / 2.0);
	Angle CurrentAngleToShiftTo = GetBestNextAngle();

	this->CheckFieldEffect();
	this->CheckCollisionWithPlayer();

	if (this->Health > 0) {
		if (this->CollisionTimer == NULL) {
			// No Collisions
			this->Rotation.ShiftToAngle(CurrentAngleToShiftTo, 0.03);
			this->CheckCollisionWithBlocks();

			if (this->AffectedByField) this->BotShape.setFillColor(MT::Shift(this->BotShape.getFillColor(), WARNING_COLOR, SLOW));
			else this->BotShape.setFillColor(MT::Shift(this->BotShape.getFillColor(), ERROR_COLOR, SLOW));
		}
		else {
			// In Collision

			if (this->CollisionTimer->getElapsedTime().asMilliseconds() >= Bot::StunnDuration) {
				delete this->CollisionTimer;
				this->CollisionTimer = NULL;
			}
			this->BotShape.setFillColor(MT::Shift(this->BotShape.getFillColor(), WARNING_COLOR, FAST));
		}
	}
	else {
		this->BotShape.setFillColor(MT::Shift(this->BotShape.getFillColor(), TRANSPARENT, FAST));
		this->BotHealthShape.setFillColor(MT::Shift(this->BotHealthShape.getFillColor(), TRANSPARENT, FAST));
		if (this->BotShape.getFillColor() == TRANSPARENT) {
			delete this->CollisionTimer;
			this->CollisionTimer = NULL;
			this->Alive = false;
		}
	}

	this->Accelerate();
	
	double VelocityX = this->VelocityValue * cos(Angle::ToRadian(this->Rotation.GetActualValue()));
	double VelocityY = this->VelocityValue * sin(Angle::ToRadian(this->Rotation.GetActualValue()));

	Point NewPosition(this->BotShape.getPosition().x + VelocityX, this->BotShape.getPosition().y + VelocityY);

	this->BotShape.setPosition(sf::Vector2f(NewPosition.GetX(), NewPosition.GetY()));
	this->BotShape.setRotation(this->Rotation.GetActualValue() + 90);

	this->BotHealthShape.setPosition(this->BotShape.getPosition());
	this->BotHealthShape.setRotation(this->BotShape.getRotation());
}

//--------------------------------------- Draw ---------------------------------------//

void Bot::Draw() {
	GameWindow->draw(this->BotShape);
	GameWindow->draw(this->BotHealthShape);
}

//---------------------------------- Is Out Of Bounds --------------------------------//

bool Bot::IsOutOfBounds() {
	return
		(
			(this->BotShape.getGlobalBounds().left >= (GameWindow->getSize().x + 2 * this->BotShape.getGlobalBounds().width))
			||
			(this->BotShape.getGlobalBounds().left <= (-2 * this->BotShape.getGlobalBounds().width))
			||
			(this->BotShape.getGlobalBounds().top >= (GameWindow->getSize().y + 2 * this->BotShape.getGlobalBounds().height))
			||
			(this->BotShape.getGlobalBounds().top <= (-2 * this->BotShape.getGlobalBounds().height))
		);
}


//------------------------------------- Get Size -------------------------------------//

Dimension Bot::GetSize() {
	return Dimension(this->BotShape.getGlobalBounds().width, this->BotShape.getGlobalBounds().height);
}

//------------------------------------ In Cooldown -----------------------------------//

bool Bot::InCooldown() {
	return Bot::Timer.getElapsedTime().asMilliseconds() <= Bot::CooldownDuration;
}

//----------------------------- Check Collision With Blocks ---------------------------//

void Bot::CheckCollisionWithBlocks() {
	Point BotCenter(this->BotShape.getPosition().x, this->BotShape.getPosition().y);
	Dimension BotSize(this->BotShape.getSize().x, this->BotShape.getSize().y);
	
	RotatedRectangle BotBoundaries(BotCenter, BotSize, this->Rotation);

	for (int i = 0; i < this->Blocks.size(); i++) {
		if (this->Blocks[i]->GetType() == Copper)continue;
		RotatedRectangle BlockBoundaries = this->Blocks[i]->GetBoundaries();
		Circle BlockFieldBoundaries = this->Blocks[i]->GetFieldBoundaries();

		if (
			BlockBoundaries.ContainsPoint(BotBoundaries.GetCorner(0))
			||
			BlockBoundaries.ContainsPoint(BotBoundaries.GetCorner(1))
			||
			BlockBoundaries.ContainsPoint(BotBoundaries.GetCorner(2))
			||
			BlockBoundaries.ContainsPoint(BotBoundaries.GetCorner(3))
		)
		{
			if (this->CollisionTimer != NULL)delete this->CollisionTimer;
			this->CollisionTimer = new sf::Clock();
			this->Rotation = Angle(this->Rotation.GetActualValue() + 180);
			this->TakeDamage(50);
			Frame::RobotDamageSound.play();

			goto Stop;
		}
	}

	Stop:;
}

//--------------------------------- Check Field Effect -------------------------------//

void Bot::CheckFieldEffect() {
	this->AffectedByField = false;

	Point BotCenter(this->BotShape.getPosition().x, this->BotShape.getPosition().y);
	Dimension BotSize(this->BotShape.getSize().x, this->BotShape.getSize().y);

	RotatedRectangle BotBoundaries(BotCenter, BotSize, this->Rotation);

	for (int i = 0; i < this->Blocks.size(); i++) {
		if (this->Blocks[i]->GetType() == Iron)continue;

		RotatedRectangle BlockBoundaries = this->Blocks[i]->GetBoundaries();
		Circle BlockFieldBoundaries = this->Blocks[i]->GetFieldBoundaries();

		if (
			BlockBoundaries.ContainsPoint(BotBoundaries.GetCorner(0))
			||
			BlockBoundaries.ContainsPoint(BotBoundaries.GetCorner(1))
			||
			BlockBoundaries.ContainsPoint(BotBoundaries.GetCorner(2))
			||
			BlockBoundaries.ContainsPoint(BotBoundaries.GetCorner(3))
			||
			BlockFieldBoundaries.ContainsPoint(BotBoundaries.GetCorner(0))
			||
			BlockFieldBoundaries.ContainsPoint(BotBoundaries.GetCorner(1))
			||
			BlockFieldBoundaries.ContainsPoint(BotBoundaries.GetCorner(2))
			||
			BlockFieldBoundaries.ContainsPoint(BotBoundaries.GetCorner(3))
			)
		{
			this->TakeDamage(0.5 * this->Blocks[i]->GetFieldIntensityFactor());
			this->AffectedByField = this->Blocks[i]->GetFieldIntensityFactor() > 0;
		}
	}
}

//---------------------------- Check Collision With Player --------------------------//

void Bot::CheckCollisionWithPlayer() {
	Point BotCenter(this->BotShape.getPosition().x, this->BotShape.getPosition().y);
	Dimension BotSize(this->BotShape.getSize().x, this->BotShape.getSize().y);

	RotatedRectangle BotBoundaries(BotCenter, BotSize, this->Rotation);

	Circle PlayerBoundaries = this->Player->GetBoundaries();

	if (
		PlayerBoundaries.ContainsPoint(BotBoundaries.GetCorner(0))
		||
		PlayerBoundaries.ContainsPoint(BotBoundaries.GetCorner(1))
		||
		PlayerBoundaries.ContainsPoint(BotBoundaries.GetCorner(2))
		||
		PlayerBoundaries.ContainsPoint(BotBoundaries.GetCorner(3))
		) 
	{
		this->TakeDamage(this->Health, true);
	}
}

//------------------------------- Refresh Health Texture -----------------------------//

void Bot::RefreshHealthTexture() {
	if (this->Health >= 87.5) {
		this->BotHealthShape.setTexture(&H100);
	}
	else if (this->Health >= 62.5) {
		this->BotHealthShape.setTexture(&H075);
	}
	else if (this->Health >= 37.5) {
		this->BotHealthShape.setTexture(&H050);
	}
	else if (this->Health >= 12.5) {
		this->BotHealthShape.setTexture(&H025);
	}
	else {
		this->BotHealthShape.setTexture(&H000);
	}
}

//-------------------------------------- Is Alive ------------------------------------//

bool Bot::IsAlive(){
	return this->Alive;
}

//------------------------------------ Take Damage -----------------------------------//

void Bot::TakeDamage(double Damage, bool CollisionWithPlayer) {
	this->Health -= Damage;

	if (CollisionWithPlayer) {
		this->Score -= Damage;
		this->Player->TakeDamage((Damage / 10.0) * Bot::DamageAmplifier);
	}
	else {
		if (Damage < 1)Damage *= 10;
		this->Score += Damage;
	}

	this->RefreshHealthTexture();
}

//------------------------------- Get Best Next Position ------------------------------//

Angle Bot::GetBestNextAngle() {
	Point BotPosition(this->BotShape.getGlobalBounds().left, this->BotShape.getGlobalBounds().top);
	Point PlayerPosition(this->Player->GetX(), this->Player->GetY());

	Angle AngleToPlayer(BotPosition, PlayerPosition);
	double DistanceLimit = 100;

	Block* ClosestBlock = NULL;
	for (int i = 0; i < this->Blocks.size(); i++) {
		if (this->Blocks[i]->GetType() == Iron) {
			if (ClosestBlock == NULL) {
				ClosestBlock = this->Blocks[i];
			}
			else {
				Dimension OldDistance(ClosestBlock->GetCenter().GetX() - BotPosition.GetX(), ClosestBlock->GetCenter().GetY() - BotPosition.GetY());
				Dimension NewDistance(this->Blocks[i]->GetCenter().GetX() - BotPosition.GetX(), this->Blocks[i]->GetCenter().GetY() - BotPosition.GetY());
				if (NewDistance.GetLength() < OldDistance.GetLength()) {
					ClosestBlock = this->Blocks[i];
				}
			}
		}
	}

	if (ClosestBlock == NULL)return AngleToPlayer;

	double Distance = 0;

	if (BotPosition.GetX() == PlayerPosition.GetX()) {
		Distance = MT::AbsoluteValue(BotPosition.GetX() - ClosestBlock->GetCenter().GetX());
	}
	else {
		// Y = aX + b
		double a = (BotPosition.GetY() - PlayerPosition.GetY()) / (double)(BotPosition.GetX() - PlayerPosition.GetX());
		double b = BotPosition.GetY() - a * BotPosition.GetX();

		Distance = MT::AbsoluteValue(a * ClosestBlock->GetCenter().GetX() - ClosestBlock->GetCenter().GetY() + b) / (double)sqrt(a * a + 1);
	}

	if (Distance <= DistanceLimit) {
		Point PlayerPosition(this->Player->GetX(), this->Player->GetY());
		Point BlockProjection = MT::GetProjection(ClosestBlock->GetCenter(), BotPosition, PlayerPosition);

		Dimension BotBlockDistance(BlockProjection.GetX() - BotPosition.GetX(), BlockProjection.GetY() - BotPosition.GetY());
		Dimension BotPlayerDistance(this->Player->GetX() - BotPosition.GetX(), this->Player->GetY() - BotPosition.GetY());
		Dimension PlayerBlockDistance(this->Player->GetX() - BlockProjection.GetX(), this->Player->GetY() - BlockProjection.GetY());

		Dimension RealBotBlockDistance(ClosestBlock->GetCenter().GetX() - BotPosition.GetX(), ClosestBlock->GetCenter().GetY() - BotPosition.GetY());

		if (MT::AbsoluteValue(BotBlockDistance.GetLength() + PlayerBlockDistance.GetLength() - BotPlayerDistance.GetLength()) < 0.01 && RealBotBlockDistance.GetLength() < Bot::BlockDetectionDistance) {
			// Block Is Between Bot And Player && Block Is Too Close To Bot
			// Move Away From The Block
			return Angle(ClosestBlock->GetCenter(), BotPosition);
		}
		else {
			return AngleToPlayer;
		}
	}
	else {
		return AngleToPlayer;
	}

}

//---------------------------------- Make Bot Wiser ---------------------------------//

void Bot::MakeBotWiser() {
	if (Bot::BlockDetectionDistance < 120)Bot::BlockDetectionDistance += 3;
	if (Bot::CooldownDuration > 2000)Bot::CooldownDuration -= 500;
	if (Bot::MaxSpeed < 3.5)Bot::MaxSpeed += 0.05;
	if (Bot::DamageAmplifier < 2)Bot::DamageAmplifier += 0.05;
}