#pragma once
#include "ShiftItem.h"

//------------------------------------- Constructor ------------------------------------//

ShiftItem::ShiftItem(Dimension BarSize, std::string LabelText, Point Origin, Dimension Size, sf::Color BackgroundColor) : MenuItem(LabelText, Origin, Size) {
	this->ShiftBar = Bar(Origin + Dimension(Size.GetWidth() - BarSize.GetWidth() - 10, (Size.GetHeight() - BarSize.GetHeight()) / 2.0), BarSize, 50, 2, 0.1, 50, BackgroundColor);

	double Thickness = 1;
	this->BarMidRectangle = sf::RectangleShape(sf::Vector2f(Thickness, BarSize.GetHeight()));
	this->BarMidRectangle.setFillColor(COLOR);
	this->BarMidRectangle.setPosition(this->ShiftBar.GetX() + (this->ShiftBar.GetWidth() - Thickness) / 2.0, this->ShiftBar.GetY());
}

//------------------------------------- Destructor ------------------------------------//

ShiftItem::~ShiftItem() {}

//--------------------------------------- Draw ---------------------------------------//

void ShiftItem::Draw() {
	this->DrawBase();
	this->ShiftBar.Draw();

	GameWindow->draw(this->BarMidRectangle);
}

//-------------------------------------- Refresh -------------------------------------//

void ShiftItem::Refresh() {
	this->ShiftBar.Refresh();
}


//--------------------------------- Get Bar Reference --------------------------------//

Bar * ShiftItem::GetBar() {
	return &this->ShiftBar;
}

//-------------------------------------- Get Rate ------------------------------------//

double ShiftItem::GetRate() {
	return this->ShiftBar.GetRate();
}

//-------------------------------------- Set Rate ------------------------------------//

void ShiftItem::SetRate(double NewRate) {
	if (NewRate >= 1)NewRate = 1;
	if (NewRate <= -1)NewRate = -1;
	return this->ShiftBar.SetRate(NewRate);
}

