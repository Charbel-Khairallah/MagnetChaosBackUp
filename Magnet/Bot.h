#pragma once
#include <SFML/Graphics.hpp>
#include "MovingObject.h"
#include "Magnet.h"
#include "Block.h"
#include "Config.h"
#include "Dimension.h"


class Bot : public MovingObject{
private:
	static int CooldownDuration;
	static int StunnDuration;
	static sf::Clock Timer;
	static int BlockDetectionDistance;
	static double DamageAmplifier;
	static double MaxSpeed;

	double Health;
	bool Stunned;
	bool Alive;
	bool AffectedByField;
	long & Score;

	sf::RectangleShape BotShape;
	sf::RectangleShape BotHealthShape;
	sf::Clock * CollisionTimer;

	Magnet * Player;
	std::vector < Block* > & Blocks;

	Angle Rotation;

	Angle GetBestNextAngle();

	void CheckCollisionWithBlocks();
	void CheckFieldEffect();
	void CheckCollisionWithPlayer();
	void RefreshHealthTexture();
	void TakeDamage(double Damage, bool CollisionWithPlayer = false);

public:
	Bot(Magnet* Player, std::vector<Block* >& Blocks, long & Score);
	~Bot();

	Dimension GetSize();
	bool IsOutOfBounds();
	bool IsAlive();

	void Refresh();
	void Draw();

	static bool InCooldown();
	static void MakeBotWiser();
	static void Reset();
};