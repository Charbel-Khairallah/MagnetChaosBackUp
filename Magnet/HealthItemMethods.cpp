#pragma once
#include "HealthItem.h"

//------------------------------------- Constructor ------------------------------------//

HealthItem::HealthItem(Dimension BarSize, std::string LabelText, Point Origin, Dimension Size, sf::Color BackgroundColor) : MenuItem(LabelText, Origin, Size) {
	this->HealthBar = Bar(Origin + Dimension(Size.GetWidth() - BarSize.GetWidth() - 10, (Size.GetHeight() - BarSize.GetHeight()) / 2.0), BarSize, 0, 2, 0.005, 50, BackgroundColor);

}

//------------------------------------- Destructor ------------------------------------//

HealthItem::~HealthItem() {}

//--------------------------------------- Draw ---------------------------------------//

void HealthItem::Draw() {
	this->DrawBase();
	this->HealthBar.Draw();
}

//-------------------------------------- Refresh -------------------------------------//

void HealthItem::Refresh() {
	this->HealthBar.Refresh();
}

//------------------------------------- Increment ------------------------------------//

void HealthItem::Increment(double Value) {
	if (Value == 0)++this->HealthBar;
	else this->HealthBar += Value;
}

//------------------------------------- Decrement ------------------------------------//

void HealthItem::Decrement(double Value) {
	if (Value == 0)--this->HealthBar;
	else this->HealthBar -= Value;
}

//--------------------------------- Get Bar Reference --------------------------------//

Bar * HealthItem::GetBar() {
	return &this->HealthBar;
}
