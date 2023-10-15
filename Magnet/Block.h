#pragma once
#include <unordered_set>

#include "MovingObject.h"
#include "Angle.h"
#include "BlockType.h"
#include "Point.h"
#include "Dimension.h"
#include "Methods.h"
#include "Config.h"
#include "BlockState.h"
#include "Magnet.h"
#include "MagneticField.h"
#include "RotatedRectangle.h"
#include "Circle.h"

class Block : public MovingObject {
private:
	static int CooldownDuration;
	static int FieldActivationDistance;
	static sf::Clock Timer;

	Angle Rotation;
	BlockType Type;
	BlockState State;

	Point Position;
	Dimension Size;

	Dimension Velocity;
	Dimension Acceleration;

	sf::Texture BlockTexture;
	sf::RectangleShape IronBlock;

	Point MergePoint;
	Block * MergeBlock;
	Magnet * Player;
	MagneticField * Field;
	std::unordered_set<long long> LastCollisionBlocks;
	std::unordered_set<long long> CurrentCollisionBlocks;

	void GenerateRandomState();
	void Init();

	double VelocityX, VelocityY;
	bool AlternativeBlockCreated;
	double FieldPower;
	double FieldIntensityFactor;

public:
	Block();
	Block(BlockType Type);
	Block(BlockType Type, Point Position, Angle Rotation, Magnet * Player);
	~Block();

	void Refresh();
	void Draw();
	
	bool IntersectsWith(Block * Other);
	bool IsOutOfBounds();
	bool InCollisionWith(Block * Other);

	Angle GetRotation();
	Point GetPosition();
	Point GetCenter();
	Dimension GetSize();
	Block * GetMergeBlock();
	RotatedRectangle GetBoundaries();
	Circle GetFieldBoundaries();

	double GetVelocityX();
	double GetVelocityY();
	double GetFieldIntensityFactor();

	BlockState GetState();
	BlockType GetType();

	void InteractWithMagnet(Point MagnetPosition, double FieldStrength);
	void BounceOff(Block * Other);
	void MoveAwayFrom(Block * Other);
	void ResetCollisionBlock();
	void AddCollisionBlock(Block * Other);
	void MergeWith(Block * Other);

	bool InCollision();
	bool IsAlternativeBlockCreated();

	void SetVelocityX(double NewVelocityValue);
	void SetVelocityY(double NewVelocityValue);
	void SetState(BlockState NewState);
	void SetMergeBlock(Block * Other);
	void SetMergePoint(Point MergePoint);
	void CreateAlternativeBlock();

	static bool InCooldown();
};