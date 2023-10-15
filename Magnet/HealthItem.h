#pragma once
#include "MenuItem.h"
#include "CurvilinearTriangle.h"
#include "Bar.h"

class HealthItem : public MenuItem {
private:
	Bar HealthBar;

public:
	HealthItem(Dimension BarSize, std::string LabelText, Point Origin, Dimension Size, sf::Color BackgroundColor);
	~HealthItem();
	
	void Draw();
	void Refresh();

	void Increment(double Value = 0);
	void Decrement(double Value = 0);

	Bar * GetBar();
};