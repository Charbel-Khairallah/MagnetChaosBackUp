#pragma once
#include <unordered_map>

#include "Frame.h"
#include "Angle.h"
#include "Magnet.h"
#include "UserInput.h"
#include "File.h"
#include "Bar.h"
#include "MenuItem.h"
#include "HealthItem.h"
#include "ShiftItem.h"
#include "UpgradeItem.h"
#include "Block.h"
#include "Bot.h"

class StartFrame : public Frame {
private:
	static int DifficultyTimerDuration;

	int ItemHeight;
	Magnet * Player;

	sf::RectangleShape BlockRectangle;
	sf::RectangleShape GameOverBackground;
	sf::Text GameOverText;
	sf::Text FinalScoreText;

	sf::RectangleShape MenuBackground;
	sf::Text ScoreLabel;

	sf::Clock DifficultyTimer;

	long ActualScore;
	double CurrentScore;

	std::vector<MenuItem*> MenuItems;
	std::vector<Block*> Blocks;
	std::vector<Bot*> Bots;

	UserInput Move;
	UserInput MoveSelectionUp;
	UserInput MoveSelectionDown;
	UserInput PositiveShift;
	UserInput NegativeShift;
	UserInput Upgrade;

	void MoveItemSelectionUp();
	void MoveItemSelectionDown();
	void EndGame();

public:
	StartFrame();
	~StartFrame();

	void DrawFrame();
	void DoAction(sf::Event& CurrentEvent);
	void DoEvents();
	void FadeIn();
	void FadeOut();
};