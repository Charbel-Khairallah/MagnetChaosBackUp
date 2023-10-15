#pragma once
#include "ControlItem.h"
#include "Config.h"
#include "Rectangle.h"
#include "Methods.h"
#include "Frame.h"

ControlItem * ControlItem::SelectedItem = NULL;

//------------------------------------ Constructor ------------------------------------//

ControlItem::ControlItem(Point & Origin, Dimension Size, int Index, std::string Title, Key * SelectedKey, int SelectedKeyIndex) {
	this->SelectedKey = SelectedKey;
	this->SelectedKeyIndex = SelectedKeyIndex;

	this->MousePressed = false;
	double X, Y, Width, Height;

	this->Origin = &Origin;
	this->Size = Size;
	this->Index = Index;

	double UnitWidth = Size.GetWidth() * 0.008;
	double UnitHeight = Size.GetHeight() * 0.04;
	double VerticalPadding = UnitHeight * 4;

	/* Separators */

	this->TopSeparator = sf::RectangleShape(sf::Vector2f(Size.GetWidth(), 0.4));
	this->TopSeparator.setFillColor(COLOR);

	this->BottomSeparator = sf::RectangleShape(sf::Vector2f(Size.GetWidth(), 0.4));
	this->BottomSeparator.setFillColor(COLOR);

	/* First Rectangle */

	this->FirstRectangle = sf::RectangleShape(sf::Vector2f(2 * UnitWidth, Size.GetHeight()));
	this->FirstRectangle.setFillColor(BACKGROUND);

	/* Top Outter Circle */

	this->TopOutterCircle = sf::CircleShape(UnitWidth);
	this->TopOutterCircle.setFillColor(BACKGROUND);

	/* Top Inner Circle */

	this->TopInnerCircle = sf::CircleShape(UnitWidth);
	this->TopInnerCircle.setFillColor(BACKGROUND);

	/* Second Rectangle */

	this->SecondRectangle = sf::RectangleShape(sf::Vector2f(UnitWidth, Size.GetHeight() - 2 * VerticalPadding));
	this->SecondRectangle.setFillColor(BACKGROUND);

	/* Third Rectangle */

	this->ThirdRectangle = sf::RectangleShape(sf::Vector2f(UnitWidth, Size.GetHeight() - 2 * VerticalPadding - 4 * UnitWidth));
	this->ThirdRectangle.setFillColor(BACKGROUND);

	/* Bottom Outter Circle */

	this->BottomOutterCircle = sf::CircleShape(UnitWidth);
	this->BottomOutterCircle.setFillColor(BACKGROUND);

	/* Bottom Inner Circle */

	this->BottomInnerCircle = sf::CircleShape(UnitWidth);
	this->BottomInnerCircle.setFillColor(BACKGROUND);

	/* Top Gradient */

	X = this->FirstRectangle.getGlobalBounds().left + this->FirstRectangle.getGlobalBounds().width;
	Y = this->FirstRectangle.getGlobalBounds().top;
	Width = Size.GetWidth() - this->FirstRectangle.getGlobalBounds().width;
	Height = UnitHeight;

	this->TopGradientVertex[0] = sf::Vertex(sf::Vector2f(X, Y), BACKGROUND);
	this->TopGradientVertex[1] = sf::Vertex(sf::Vector2f(X + Width, Y), TRANSPARENT);
	this->TopGradientVertex[2] = sf::Vertex(sf::Vector2f(X + Width, Y + Height), TRANSPARENT);
	this->TopGradientVertex[3] = sf::Vertex(sf::Vector2f(X, Y + Height), BACKGROUND);

	/* Bottom Gradient */

	X = this->FirstRectangle.getGlobalBounds().left + this->FirstRectangle.getGlobalBounds().width;
	Y = this->FirstRectangle.getGlobalBounds().top + this->FirstRectangle.getGlobalBounds().height - UnitHeight;
	Width = Size.GetWidth() - this->FirstRectangle.getGlobalBounds().width;
	Height = UnitHeight;

	this->BottomGradientVertex[0] = sf::Vertex(sf::Vector2f(X, Y), BACKGROUND);
	this->BottomGradientVertex[1] = sf::Vertex(sf::Vector2f(X + Width, Y), TRANSPARENT);
	this->BottomGradientVertex[2] = sf::Vertex(sf::Vector2f(X + Width, Y + Height), TRANSPARENT);
	this->BottomGradientVertex[3] = sf::Vertex(sf::Vector2f(X, Y + Height), BACKGROUND);

	/* Labels */

	this->SelectedKey->Select(this->SelectedKeyIndex);

	this->Title = sf::Text(Title, FONT, H3);
	this->Title.setFillColor(COLOR);
	this->Value = sf::Text(this->SelectedKey->GetValue(), FONT, H4);
	this->Value.setFillColor(COLOR);


	this->SetPositions();
}

//------------------------------------- Destructor ------------------------------------//

ControlItem::~ControlItem() {

}


//--------------------------------------- Select ---------------------------------------//

void ControlItem::Select(){
	ControlItem::SelectedItem = this;
	this->SelectedKey->Select(this->SelectedKeyIndex);
}


//--------------------------------------- Refresh --------------------------------------//

void ControlItem::Refresh(){
	Point TopLeftCorner(this->GetX(), this->GetY());
	Point BottomRightCorner(this->GetX() + this->GetWidth(), this->GetY() + this->GetHeight());
	Shape* KeyBoundaries = new Rectangle(TopLeftCorner, BottomRightCorner);

	Point MousePosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

	if (KeyBoundaries->ContainsPoint(MousePosition)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			this->MousePressed = true;
			this->Title.setFillColor(MT::Shift(this->Title.getFillColor(), PRESSED_COLOR, SLOW));
			this->Value.setFillColor(MT::Shift(this->Value.getFillColor(), PRESSED_COLOR, SLOW));

			this->FirstRectangle.setFillColor(MT::Shift(this->FirstRectangle.getFillColor(), PRESSED_COLOR, SLOW));
			this->SecondRectangle.setFillColor(MT::Shift(this->SecondRectangle.getFillColor(), PRESSED_COLOR, SLOW));
			this->ThirdRectangle.setFillColor(MT::Shift(this->ThirdRectangle.getFillColor(), PRESSED_COLOR, SLOW));

			this->TopInnerCircle.setFillColor(MT::Shift(this->TopInnerCircle.getFillColor(), PRESSED_COLOR, SLOW));
			this->BottomInnerCircle.setFillColor(MT::Shift(this->BottomInnerCircle.getFillColor(), PRESSED_COLOR, SLOW));

			this->BottomGradientVertex[0].color = MT::Shift(this->BottomGradientVertex[0].color, PRESSED_COLOR, SLOW);
			this->BottomGradientVertex[3].color = MT::Shift(this->BottomGradientVertex[3].color, PRESSED_COLOR, SLOW);
			this->TopGradientVertex[0].color = MT::Shift(this->TopGradientVertex[0].color, PRESSED_COLOR, SLOW);
			this->TopGradientVertex[3].color = MT::Shift(this->TopGradientVertex[3].color, PRESSED_COLOR, SLOW);
			
			this->TopSeparator.setFillColor(MT::Shift(this->TopSeparator.getFillColor(), TRANSPARENT, SLOW));
			this->BottomSeparator.setFillColor(MT::Shift(this->TopSeparator.getFillColor(), TRANSPARENT, SLOW));
		}
		else {
			if (this->MousePressed)this->Select();
			this->MousePressed = false;
			this->Title.setFillColor(MT::Shift(this->Title.getFillColor(), HOVER_COLOR, SLOW));
			this->Value.setFillColor(MT::Shift(this->Value.getFillColor(), HOVER_COLOR, SLOW));

			this->FirstRectangle.setFillColor(MT::Shift(this->FirstRectangle.getFillColor(), HOVER_COLOR, SLOW));
			this->SecondRectangle.setFillColor(MT::Shift(this->SecondRectangle.getFillColor(), HOVER_COLOR, SLOW));
			this->ThirdRectangle.setFillColor(MT::Shift(this->ThirdRectangle.getFillColor(), HOVER_COLOR, SLOW));

			this->TopInnerCircle.setFillColor(MT::Shift(this->TopInnerCircle.getFillColor(), HOVER_COLOR, SLOW));
			this->BottomInnerCircle.setFillColor(MT::Shift(this->BottomInnerCircle.getFillColor(), HOVER_COLOR, SLOW));

			this->BottomGradientVertex[0].color = MT::Shift(this->BottomGradientVertex[0].color, HOVER_COLOR, SLOW);
			this->BottomGradientVertex[3].color = MT::Shift(this->BottomGradientVertex[3].color, HOVER_COLOR, SLOW);
			this->TopGradientVertex[0].color = MT::Shift(this->TopGradientVertex[0].color, HOVER_COLOR, SLOW);
			this->TopGradientVertex[3].color = MT::Shift(this->TopGradientVertex[3].color, HOVER_COLOR, SLOW);

			this->TopSeparator.setFillColor(MT::Shift(this->TopSeparator.getFillColor(), TRANSPARENT, SLOW));
			this->BottomSeparator.setFillColor(MT::Shift(this->TopSeparator.getFillColor(), TRANSPARENT, SLOW));
		}
	}
	else {
		this->MousePressed = false;
		if (ControlItem::SelectedItem != NULL && ControlItem::SelectedItem->Index == this->Index) {
			this->Title.setFillColor(MT::Shift(this->Title.getFillColor(), PRESSED_COLOR, SLOW));
			this->Value.setFillColor(MT::Shift(this->Value.getFillColor(), PRESSED_COLOR, SLOW));

			this->FirstRectangle.setFillColor(MT::Shift(this->FirstRectangle.getFillColor(), PRESSED_COLOR, SLOW));
			this->SecondRectangle.setFillColor(MT::Shift(this->SecondRectangle.getFillColor(), PRESSED_COLOR, SLOW));
			this->ThirdRectangle.setFillColor(MT::Shift(this->ThirdRectangle.getFillColor(), PRESSED_COLOR, SLOW));

			this->TopInnerCircle.setFillColor(MT::Shift(this->TopInnerCircle.getFillColor(), PRESSED_COLOR, SLOW));
			this->BottomInnerCircle.setFillColor(MT::Shift(this->BottomInnerCircle.getFillColor(), PRESSED_COLOR, SLOW));

			this->BottomGradientVertex[0].color = MT::Shift(this->BottomGradientVertex[0].color, PRESSED_COLOR, SLOW);
			this->BottomGradientVertex[3].color = MT::Shift(this->BottomGradientVertex[3].color, PRESSED_COLOR, SLOW);
			this->TopGradientVertex[0].color = MT::Shift(this->TopGradientVertex[0].color, PRESSED_COLOR, SLOW);
			this->TopGradientVertex[3].color = MT::Shift(this->TopGradientVertex[3].color, PRESSED_COLOR, SLOW);

			this->TopSeparator.setFillColor(MT::Shift(this->TopSeparator.getFillColor(), TRANSPARENT, SLOW));
			this->BottomSeparator.setFillColor(MT::Shift(this->BottomSeparator.getFillColor(), TRANSPARENT, SLOW));
		}
		else {
			this->Title.setFillColor(MT::Shift(this->Title.getFillColor(), COLOR, SLOW));
			this->Value.setFillColor(MT::Shift(this->Value.getFillColor(), COLOR, SLOW));

			this->FirstRectangle.setFillColor(MT::Shift(this->FirstRectangle.getFillColor(), BACKGROUND, SLOW));
			this->SecondRectangle.setFillColor(MT::Shift(this->SecondRectangle.getFillColor(), BACKGROUND, SLOW));
			this->ThirdRectangle.setFillColor(MT::Shift(this->ThirdRectangle.getFillColor(), BACKGROUND, SLOW));

			this->TopInnerCircle.setFillColor(MT::Shift(this->TopInnerCircle.getFillColor(), BACKGROUND, SLOW));
			this->BottomInnerCircle.setFillColor(MT::Shift(this->BottomInnerCircle.getFillColor(), BACKGROUND, SLOW));

			this->BottomGradientVertex[0].color = MT::Shift(this->BottomGradientVertex[0].color, BACKGROUND, SLOW);
			this->BottomGradientVertex[3].color = MT::Shift(this->BottomGradientVertex[3].color, BACKGROUND, SLOW);
			this->TopGradientVertex[0].color = MT::Shift(this->TopGradientVertex[0].color, BACKGROUND, SLOW);
			this->TopGradientVertex[3].color = MT::Shift(this->TopGradientVertex[3].color, BACKGROUND, SLOW);

			this->TopSeparator.setFillColor(MT::Shift(this->TopSeparator.getFillColor(), COLOR, SLOW));
			this->BottomSeparator.setFillColor(MT::Shift(this->BottomSeparator.getFillColor(), COLOR, SLOW));
		}
	}
	delete KeyBoundaries;

	this->SetPositions();
	
}

//------------------------------------ Set Positions ------------------------------------//

void ControlItem::SetPositions() {
	double X, Y, Width, Height;
	double UnitWidth = this->Size.GetWidth() * 0.008;
	double UnitHeight = this->Size.GetHeight() * 0.04;
	double VerticalPadding = UnitHeight * 4;

	/* TopSeparator Rectangle */

	X = Origin->GetX();
	Y = Origin->GetY() + Index * Size.GetHeight();
	this->TopSeparator.setPosition(X, Y);
	this->BottomSeparator.setPosition(X, Y + Size.GetHeight());

	/* First Rectangle */

	X = Origin->GetX();
	Y = Origin->GetY() + Index * Size.GetHeight();
	this->FirstRectangle.setPosition(X, Y);

	/* Top Outter Circle */

	X = this->FirstRectangle.getGlobalBounds().left + this->FirstRectangle.getGlobalBounds().width;
	Y = this->FirstRectangle.getGlobalBounds().top + VerticalPadding - UnitWidth;
	this->TopOutterCircle.setPosition(X, Y);

	/* Top Inner Circle */

	X = this->FirstRectangle.getGlobalBounds().left + this->FirstRectangle.getGlobalBounds().width;
	Y = this->FirstRectangle.getGlobalBounds().top + VerticalPadding + UnitWidth;
	this->TopInnerCircle.setPosition(X, Y);

	/* Second Rectangle */

	X = this->FirstRectangle.getGlobalBounds().left + this->FirstRectangle.getGlobalBounds().width;
	Y = this->FirstRectangle.getGlobalBounds().top + VerticalPadding;
	this->SecondRectangle.setPosition(X, Y);

	/* Third Rectangle */

	X = this->SecondRectangle.getGlobalBounds().left + this->SecondRectangle.getGlobalBounds().width;
	Y = this->SecondRectangle.getGlobalBounds().top + 2 * UnitWidth;
	this->ThirdRectangle.setPosition(X, Y);

	/* Bottom Outter Circle */

	X = this->TopOutterCircle.getGlobalBounds().left;
	Y = Size.GetHeight() - VerticalPadding - UnitWidth;
	this->BottomOutterCircle.setPosition(X, Y);

	/* Bottom Inner Circle */

	X = this->TopInnerCircle.getGlobalBounds().left;
	Y = Origin->GetY() + Index * Size.GetHeight() + Size.GetHeight() - VerticalPadding - 3 * UnitWidth;
	this->BottomInnerCircle.setPosition(X, Y);

	/* Top Gradient */

	X = this->FirstRectangle.getGlobalBounds().left + this->FirstRectangle.getGlobalBounds().width;
	Y = this->FirstRectangle.getGlobalBounds().top;
	Width = Size.GetWidth() - this->FirstRectangle.getGlobalBounds().width;
	Height = UnitHeight;

	this->TopGradientVertex[0].position = sf::Vector2f(X, Y);
	this->TopGradientVertex[1].position = sf::Vector2f(X + Width, Y);
	this->TopGradientVertex[2].position = sf::Vector2f(X + Width, Y + Height);
	this->TopGradientVertex[3].position = sf::Vector2f(X, Y + Height);

	/* Bottom Gradient */

	X = this->FirstRectangle.getGlobalBounds().left + this->FirstRectangle.getGlobalBounds().width;
	Y = this->FirstRectangle.getGlobalBounds().top + this->FirstRectangle.getGlobalBounds().height - UnitHeight;
	Width = Size.GetWidth() - this->FirstRectangle.getGlobalBounds().width;
	Height = UnitHeight;

	this->BottomGradientVertex[0].position = sf::Vector2f(X, Y);
	this->BottomGradientVertex[1].position = sf::Vector2f(X + Width, Y);
	this->BottomGradientVertex[2].position = sf::Vector2f(X + Width, Y + Height);
	this->BottomGradientVertex[3].position = sf::Vector2f(X, Y + Height);

	/* Labels */

	X = 12 * UnitWidth;
	//Y = (Size.GetHeight() - this->Key.getGlobalBounds().height - this->Value.getGlobalBounds().height) / 3.0;
	Y = 20;
	this->Title.setPosition(X, Origin->GetY() + Index * Size.GetHeight() + Y);
	this->Value.setPosition(X, this->Title.getGlobalBounds().top + this->Title.getGlobalBounds().height + Y);
}

//---------------------------------------- GetX ----------------------------------------//

double ControlItem::GetX(){
	return this->Origin->GetX();
}

//---------------------------------------- GetY ----------------------------------------//

double ControlItem::GetY(){
	return this->Origin->GetY() + this->Index * this->Size.GetHeight();
}

//------------------------------------- Get Width --------------------------------------//

double ControlItem::GetWidth(){
	return this->Size.GetWidth();
}

//------------------------------------- Get Height -------------------------------------//

double ControlItem::GetHeight(){
	return this->Size.GetHeight();
}


//---------------------------------------- Draw ----------------------------------------//

void ControlItem::Draw(){

	GameWindow->draw(this->TopGradientVertex, 4, sf::Quads);
	GameWindow->draw(this->BottomGradientVertex, 4, sf::Quads);

	GameWindow->draw(this->FirstRectangle);
	GameWindow->draw(this->SecondRectangle);
	GameWindow->draw(this->ThirdRectangle);

	GameWindow->draw(this->TopOutterCircle);
	GameWindow->draw(this->TopInnerCircle);
	GameWindow->draw(this->BottomOutterCircle);
	GameWindow->draw(this->BottomInnerCircle);

	GameWindow->draw(this->Title);
	GameWindow->draw(this->Value);

	GameWindow->draw(this->TopSeparator);
	GameWindow->draw(this->BottomSeparator);
}

//-------------------------------------- Set value -------------------------------------//

void ControlItem::SetValue(std::string NewValue) {
	this->Value.setString(NewValue);
}

//-------------------------------------- Get value -------------------------------------//

std::string ControlItem::GetValue() {
	return this->Value.getString();
}