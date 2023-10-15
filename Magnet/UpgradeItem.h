#pragma once
#include "MenuItem.h"
#include "Magnet.h"
#include "UserInput.h"


class UpgradeItem : public MenuItem {
private:
	int LevelValue;
	int MaxLevel;
	int Index;

	bool Pressed;

	Point Origin;
	Dimension Size;

	Magnet * Player;

	sf::Text Level;
	sf::CircleShape LevelBackground;

	sf::RectangleShape TopBorder;
	sf::RectangleShape BottomBorder;
	sf::RectangleShape LeftBorder;
	sf::RectangleShape RightBorder;

	UserInput UpgradeInput;

	void Upgrade();

public:
	UpgradeItem(UserInput Upgrade, int Index, Magnet * Player, std::string LabelText, Point Origin, Dimension Size);
	~UpgradeItem();

	void Draw();
	void Refresh();

	static int SelectedIndex;

};