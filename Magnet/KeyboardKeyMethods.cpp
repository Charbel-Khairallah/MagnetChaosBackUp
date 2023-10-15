#pragma once
#include "KeyboardKey.h"
#include "Rectangle.h"
#include "Methods.h"
#include "ControlItem.h"

Dimension KeyboardKey::Unit(sf::VideoMode::getDesktopMode().width * 0.6 / 15.0, sf::VideoMode::getDesktopMode().height * 0.08);
Point KeyboardKey::Origin(sf::VideoMode::getDesktopMode().width * 0.6 / 3.0, sf::VideoMode::getDesktopMode().height * 0.25);

//------------------------------------------- Contructor -------------------------------------------//

KeyboardKey::KeyboardKey(int Rotation, std::string Letter, double Multiplier, Dimension Shift, int KeyType, int KeyCode) : Key(KeyType, KeyCode) {
	this->Letter = Letter;
	this->KeyCode = KeyCode;
	this->KeyType = KeyType;

	/* Middle Rectangle */

	double RectangleWidth = KeyboardKey::Unit.GetWidth() * Multiplier - KeyboardKey::Unit.GetWidth() * 0.2;
	double RectangleHeight = KeyboardKey::Unit.GetHeight() - KeyboardKey::Unit.GetWidth() / 10.0;
	this->MiddleRectangle = sf::RectangleShape(sf::Vector2f(RectangleWidth, RectangleHeight));

	double RectangleX = Origin.GetX() + Shift.GetWidth() + KeyboardKey::Unit.GetWidth() / 10.0;
	double RectangleY = Origin.GetY() + Shift.GetHeight();
	this->MiddleRectangle.setPosition(RectangleX, RectangleY);
	this->MiddleRectangle.setFillColor(this->MainColor);

	/* Left Polygon */

	double X, Y;
	this->LeftPolygon = sf::ConvexShape(4);

	X = this->MiddleRectangle.getGlobalBounds().left;
	Y = this->MiddleRectangle.getGlobalBounds().top;
	this->LeftPolygon.setPoint(0, sf::Vector2f(X, Y));

	X = this->MiddleRectangle.getGlobalBounds().left;
	Y = this->MiddleRectangle.getGlobalBounds().top + this->MiddleRectangle.getGlobalBounds().height;
	this->LeftPolygon.setPoint(1, sf::Vector2f(X, Y));

	X = this->MiddleRectangle.getGlobalBounds().left - KeyboardKey::Unit.GetHeight() / 10.0;
	Y = this->MiddleRectangle.getGlobalBounds().top + this->MiddleRectangle.getGlobalBounds().height + KeyboardKey::Unit.GetHeight() / 10.0;
	this->LeftPolygon.setPoint(2, sf::Vector2f(X, Y));

	X = this->MiddleRectangle.getGlobalBounds().left - KeyboardKey::Unit.GetHeight() / 10.0;
	Y = this->MiddleRectangle.getGlobalBounds().top;
	this->LeftPolygon.setPoint(3, sf::Vector2f(X, Y));

	this->LeftPolygon.setFillColor(this->FirstEdgeColor);

	/* Bottom Polygon */

	this->BottomPolygon = sf::ConvexShape(4);

	X = this->MiddleRectangle.getGlobalBounds().left;
	Y = this->MiddleRectangle.getGlobalBounds().top + this->MiddleRectangle.getGlobalBounds().height;
	this->BottomPolygon.setPoint(0, sf::Vector2f(X, Y));

	X = this->MiddleRectangle.getGlobalBounds().left + this->MiddleRectangle.getGlobalBounds().width;
	Y = this->MiddleRectangle.getGlobalBounds().top + this->MiddleRectangle.getGlobalBounds().height;
	this->BottomPolygon.setPoint(1, sf::Vector2f(X, Y));

	X = this->MiddleRectangle.getGlobalBounds().left + this->MiddleRectangle.getGlobalBounds().width + KeyboardKey::Unit.GetWidth() / 10.0;
	Y = this->MiddleRectangle.getGlobalBounds().top + this->MiddleRectangle.getGlobalBounds().height + KeyboardKey::Unit.GetHeight() / 10.0;
	this->BottomPolygon.setPoint(2, sf::Vector2f(X, Y));

	X = this->MiddleRectangle.getGlobalBounds().left - KeyboardKey::Unit.GetWidth() / 10.0;
	Y = this->MiddleRectangle.getGlobalBounds().top + this->MiddleRectangle.getGlobalBounds().height + KeyboardKey::Unit.GetHeight() / 10.0;
	this->BottomPolygon.setPoint(3, sf::Vector2f(X, Y));

	this->BottomPolygon.setFillColor(this->SecondEdgeColor);

	/* Right Polygon */

	this->RightPolygon = sf::ConvexShape(4);

	X = this->MiddleRectangle.getGlobalBounds().left + this->MiddleRectangle.getGlobalBounds().width;
	Y = this->MiddleRectangle.getGlobalBounds().top;
	this->RightPolygon.setPoint(0, sf::Vector2f(X, Y));

	X = this->MiddleRectangle.getGlobalBounds().left + this->MiddleRectangle.getGlobalBounds().width;
	Y = this->MiddleRectangle.getGlobalBounds().top + this->MiddleRectangle.getGlobalBounds().height;
	this->RightPolygon.setPoint(1, sf::Vector2f(X, Y));

	X = this->MiddleRectangle.getGlobalBounds().left + this->MiddleRectangle.getGlobalBounds().width + KeyboardKey::Unit.GetHeight() / 10.0;
	Y = this->MiddleRectangle.getGlobalBounds().top + this->MiddleRectangle.getGlobalBounds().height + KeyboardKey::Unit.GetHeight() / 10.0;
	this->RightPolygon.setPoint(2, sf::Vector2f(X, Y));

	X = this->MiddleRectangle.getGlobalBounds().left + this->MiddleRectangle.getGlobalBounds().width + KeyboardKey::Unit.GetHeight() / 10.0;
	Y = this->MiddleRectangle.getGlobalBounds().top;
	this->RightPolygon.setPoint(3, sf::Vector2f(X, Y));

	this->RightPolygon.setFillColor(this->ThirdEdgeColor);

	/* Text Label */

	this->Label = sf::Text(this->Letter, FONT, H4);
	X = this->MiddleRectangle.getGlobalBounds().left + (this->MiddleRectangle.getGlobalBounds().width - this->Label.getGlobalBounds().width) / 2.0;
	Y = this->MiddleRectangle.getGlobalBounds().top + (this->MiddleRectangle.getGlobalBounds().height - this->Label.getGlobalBounds().height) / 2.0;
	if (this->KeyCode < -1) {
		// Disabled
		this->Label.setFillColor(DISABLED_COLOR);
	}
	else {
		this->Label.setFillColor(COLOR);
	}
	switch (Rotation) {
		case 0: {
			Y -= 10;
			break;
		}
		case 90: {
			Y -= 5;
			X += 14;
			break;
		}
		case 180: {
			Y += 10;
			X += 4;
			break;
		}
		case 270: {
			X -= 8;
			break;
		}
	}
	this->Label.setPosition(X, Y);
	this->Label.setRotation(Rotation);

	/* Selection Rectangle */

	double SelectionRectangleWidth = (KeyboardKey::Unit.GetWidth() * Multiplier - KeyboardKey::Unit.GetWidth() * 0.2) * 0.64;
	double SelectionRectangleHeight = (KeyboardKey::Unit.GetHeight() - KeyboardKey::Unit.GetWidth() / 10.0) * 0.1;

	this->SelectionRectangle = sf::RectangleShape(sf::Vector2f(SelectionRectangleWidth, SelectionRectangleHeight));
	
	X = this->MiddleRectangle.getGlobalBounds().left + (this->MiddleRectangle.getGlobalBounds().width - SelectionRectangleWidth) / 2.0;
	Y = this->MiddleRectangle.getGlobalBounds().top + this->MiddleRectangle.getGlobalBounds().height - SelectionRectangleHeight * 2;
	this->SelectionRectangle.setPosition(X, Y);

	this->SelectionRectangle.setFillColor(this->SecondaryColor);

	/* Left Selection Circle */

	this->LeftSelectionCircle = sf::CircleShape(this->SelectionRectangle.getGlobalBounds().height / 2.0);

	X = this->SelectionRectangle.getGlobalBounds().left - this->LeftSelectionCircle.getGlobalBounds().width / 2.0;
	Y = this->SelectionRectangle.getGlobalBounds().top;
	this->LeftSelectionCircle.setPosition(X, Y);

	this->LeftSelectionCircle.setFillColor(this->SecondaryColor);

	/* Right Selection Circle */

	this->RightSelectionCircle = sf::CircleShape(this->SelectionRectangle.getGlobalBounds().height / 2.0);

	X = this->SelectionRectangle.getGlobalBounds().left + this->SelectionRectangle.getGlobalBounds().width - this->LeftSelectionCircle.getGlobalBounds().width / 2.0;
	Y = this->SelectionRectangle.getGlobalBounds().top;
	this->RightSelectionCircle.setPosition(X, Y);

	this->RightSelectionCircle.setFillColor(this->SecondaryColor);

	/* Disabled Rectangle */

	this->DisabledRectangle = sf::RectangleShape(sf::Vector2f(this->GetWidth(), this->GetHeight()));
	this->DisabledRectangle.setPosition(Origin.GetX() + Shift.GetWidth(), Origin.GetY() + Shift.GetHeight());
	this->DisabledRectangle.setFillColor(DISABLED_FILL);

}

//------------------------------------------- Desctructor -------------------------------------------//

KeyboardKey::~KeyboardKey() {
	ControlItem::SelectedItem = NULL;
}

//---------------------------------------------- GetX ----------------------------------------------//

double KeyboardKey::GetX() {
	return this->MiddleRectangle.getGlobalBounds().left - KeyboardKey::Unit.GetWidth() / 10.0;
}

//---------------------------------------------- GetY ----------------------------------------------//

double KeyboardKey::GetY() {
	return this->MiddleRectangle.getGlobalBounds().top;
}

//-------------------------------------------- GetWidth --------------------------------------------//

double KeyboardKey::GetWidth() {
	return this->MiddleRectangle.getGlobalBounds().width + KeyboardKey::Unit.GetWidth() * 0.2;
}

//-------------------------------------------- GetHeight --------------------------------------------//

double KeyboardKey::GetHeight() {
	return this->MiddleRectangle.getGlobalBounds().height + KeyboardKey::Unit.GetWidth() / 10.0;
}


//----------------------------------------------- Select ---------------------------------------------//

void KeyboardKey::Select(int Index) {
	Frame::SelectionSound.play();
	if (Key::SelectedKey != NULL) {
		Key::SelectedKey->UnSelect();
	}
	Key::SelectedKey = this;
	this->Selected = true;
	if (ControlItem::SelectedItem != NULL) {
		ControlItem::SelectedItem->SelectedKey = this;
		ControlItem::SelectedItem->SelectedKeyIndex = -1;
		ControlItem::SelectedItem->SetValue(this->GetValue());
	}
}

//--------------------------------------------- UnSelect ---------------------------------------------//

void KeyboardKey::UnSelect() {
	this->Selected = false;
}

//--------------------------------------------- Refresh ---------------------------------------------//

void KeyboardKey::Refresh() {
	// If Not Disabled
	if (this->KeyCode >= -1) {
		Point TopLeftCorner(this->GetX(), this->GetY());
		Point BottomRightCorner(this->GetX() + this->GetWidth(), this->GetY() + this->GetHeight());
		Shape* KeyBoundaries = new Rectangle(TopLeftCorner, BottomRightCorner);

		Point MousePosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

		if (KeyBoundaries->ContainsPoint(MousePosition)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				this->Label.setFillColor(MT::Shift(this->Label.getFillColor(), PRESSED_COLOR, FAST));
				this->SelectionRectangle.setFillColor(MT::Shift(this->SelectionRectangle.getFillColor(), PRESSED_COLOR, SLOW));
				this->LeftSelectionCircle.setFillColor(MT::Shift(this->SelectionRectangle.getFillColor(), PRESSED_COLOR, SLOW));
				this->RightSelectionCircle.setFillColor(MT::Shift(this->SelectionRectangle.getFillColor(), PRESSED_COLOR, SLOW));
				this->MousePressed = true;
			}
			else {
				this->Label.setFillColor(MT::Shift(this->Label.getFillColor(), HOVER_COLOR, FAST));
				this->SelectionRectangle.setFillColor(MT::Shift(this->SelectionRectangle.getFillColor(), HOVER_COLOR, SLOW));
				this->LeftSelectionCircle.setFillColor(MT::Shift(this->SelectionRectangle.getFillColor(), HOVER_COLOR, SLOW));
				this->RightSelectionCircle.setFillColor(MT::Shift(this->SelectionRectangle.getFillColor(), HOVER_COLOR, SLOW));
				if (this->MousePressed) {
					this->Select();
				}
				this->MousePressed = false;
			}
		}
		else {
			this->MousePressed = false;
			if (this->Selected) {
				this->Label.setFillColor(MT::Shift(this->Label.getFillColor(), PRESSED_COLOR, FAST));
				this->SelectionRectangle.setFillColor(MT::Shift(this->SelectionRectangle.getFillColor(), PRESSED_COLOR, SLOW));
				this->LeftSelectionCircle.setFillColor(MT::Shift(this->SelectionRectangle.getFillColor(), PRESSED_COLOR, SLOW));
				this->RightSelectionCircle.setFillColor(MT::Shift(this->SelectionRectangle.getFillColor(), PRESSED_COLOR, SLOW));
			}
			else {
				this->Label.setFillColor(MT::Shift(this->Label.getFillColor(), COLOR, FAST));
				this->SelectionRectangle.setFillColor(MT::Shift(this->SelectionRectangle.getFillColor(), this->SecondaryColor, SLOW));
				this->LeftSelectionCircle.setFillColor(MT::Shift(this->SelectionRectangle.getFillColor(), this->SecondaryColor, SLOW));
				this->RightSelectionCircle.setFillColor(MT::Shift(this->SelectionRectangle.getFillColor(), this->SecondaryColor, SLOW));
			}
		}
		delete KeyBoundaries;
	}
}

//---------------------------------------------- Draw -----------------------------------------------//

void KeyboardKey::Draw() {
	GameWindow->draw(this->LeftPolygon);
	GameWindow->draw(this->BottomPolygon);
	GameWindow->draw(this->RightPolygon);

	GameWindow->draw(this->MiddleRectangle);
	GameWindow->draw(this->Label);

	GameWindow->draw(this->LeftSelectionCircle);
	GameWindow->draw(this->RightSelectionCircle);
	GameWindow->draw(this->SelectionRectangle);

	if (this->KeyCode < -1) {
		GameWindow->draw(this->DisabledRectangle);
	}
}

//-------------------------------------------- Get Value --------------------------------------------//

std::string KeyboardKey::GetValue() {
	if (this->Label.getRotation() == 90)return "Down";
	if (this->Label.getRotation() == 180)return "Left";
	if (this->Label.getRotation() == 270)return "Up";
	if (this->Label.getRotation() == 0 && this->Letter == ">")return "Rigth";
	return this->Letter;
}