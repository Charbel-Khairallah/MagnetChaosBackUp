#pragma once
#include "MenuItem.h"

MenuItem * MenuItem::SelectedItem = NULL;

//------------------------------------ Constructor ------------------------------------//

MenuItem::MenuItem(std::string LabelText, Point Origin, Dimension Size) {
	this->Origin = Origin;
	this->Size = Size;

	this->Index = 0;
	this->BorderThickness = 2;

	this->Label = sf::Text(LabelText, FONT, H3);
	this->Label.setFillColor(COLOR);
	this->Label.setPosition(Origin.GetX() + 20, Origin.GetY() + (Size.GetHeight() - this->Label.getGlobalBounds().height * 2) / 2.0);

	/* Top Border */

	this->TopBorder.setSize(sf::Vector2f(this->Size.GetWidth(), this->BorderThickness));
	this->TopBorder.setPosition(this->Origin.GetX(), this->Origin.GetY());
	this->TopBorder.setFillColor(TRANSPARENT);

	/* Bottom Border */

	this->BottomBorder.setSize(sf::Vector2f(this->Size.GetWidth(), this->BorderThickness));
	this->BottomBorder.setPosition(this->Origin.GetX(), this->Origin.GetY() + this->Size.GetHeight() - this->BottomBorder.getGlobalBounds().height);
	this->BottomBorder.setFillColor(TRANSPARENT);

	/* Left Border */

	this->LeftBorder.setSize(sf::Vector2f(this->BorderThickness, this->Size.GetHeight()));
	this->LeftBorder.setPosition(this->Origin.GetX(), this->Origin.GetY());
	this->LeftBorder.setFillColor(TRANSPARENT);

	/* Right Border */

	this->RightBorder.setSize(sf::Vector2f(this->BorderThickness, this->Size.GetHeight()));
	this->RightBorder.setPosition(this->Origin.GetX() + this->Size.GetWidth() - this->RightBorder.getGlobalBounds().width, this->Origin.GetY());
	this->RightBorder.setFillColor(TRANSPARENT);
}

//------------------------------------- Destructor ------------------------------------//

MenuItem::~MenuItem() {
	
}

//------------------------------------- Draw Base -------------------------------------//

void MenuItem::DrawBase() {
	GameWindow->draw(this->Label);
	GameWindow->draw(this->TopBorder);
	GameWindow->draw(this->BottomBorder);
	GameWindow->draw(this->LeftBorder);
	GameWindow->draw(this->RightBorder);
}