#pragma once
#include "MenuItem.h"
#include "CurvilinearTriangle.h"
#include "Bar.h"

class ShiftItem : public MenuItem {
private:
	Bar ShiftBar;

	sf::RectangleShape BarMidRectangle;

public:
	ShiftItem(Dimension BarSize, std::string LabelText, Point Origin, Dimension Size, sf::Color BackgroundColor);
	~ShiftItem();

	void Draw();
	void Refresh();

	double GetRate();
	void SetRate(double NewRate);

	void Increment(double Value = 0);
	void Decrement(double Value = 0);

	Bar* GetBar();
};