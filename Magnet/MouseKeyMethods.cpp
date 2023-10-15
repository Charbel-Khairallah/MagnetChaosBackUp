#pragma once
#include "MouseKey.h"
#include "Methods.h"
#include "Rectangle.h"
#include "ControlItem.h"

//------------------------------------------- Contructor -------------------------------------------//

MouseKey::MouseKey(Point Origin, Dimension Size, int KeyType, int KeyCode) : Key(KeyType, KeyCode) {
	this->SelectedIndex = -1;
	sf::Uint8* Pixels = new sf::Uint8(4 * Size.GetWidth() * Size.GetHeight());
	
	/* Main Mouse Image */

	if (!this->MouseImage.loadFromFile("../GameData/Images/Mouse2.png")) {
		std::cout << "Error: Could Not Load Image." << std::endl;
	}

	for (int i = 0; i < this->MouseImage.getSize().x; i++) {
		for (int j = 0; j < this->MouseImage.getSize().y; j++) {
			if (this->MouseImage.getPixel(i, j) == sf::Color::Transparent) {
				// Leave it Transparent
			}
			else if (this->MouseImage.getPixel(i, j) == sf::Color(0, 255, 0, 255)) {
				this->MouseImage.setPixel(i, j, this->SecondaryColor);
			}
			else {
				this->MouseImage.setPixel(i, j, this->ThirdEdgeColor);
			}
		}
	}
	this->MouseTexture.loadFromImage(this->MouseImage);
	this->MouseTexture.setSmooth(true);

	this->Mouse.setPosition(Origin.GetX(), Origin.GetY());
	this->Mouse.setSize(Size.Vector2F());

	this->Mouse.setTexture(&this->MouseTexture);
	
	// CAUSING ERROR IDK WHY !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// RANDOMLY OCCURING
	this->ResizedMouseImage.create(Size.GetWidth(), Size.GetHeight(), Pixels);
	MT::ResizeImage(this->MouseImage, this->ResizedMouseImage);

	/* Mouse Reference In Order To Check Selection Area */

	if (!this->MouseSelectionImage.loadFromFile("../GameData/Images/MouseSelection.png")) {
		std::cout << "Error: Could Not Load Image." << std::endl;
	}

	this->ResizedMouseSelectionImage.create(Size.GetWidth(), Size.GetHeight(), Pixels);
	MT::ResizeImage(this->MouseSelectionImage, this->ResizedMouseSelectionImage);
	
	/* Selection Images */

	if (!this->LeftClickImage.loadFromFile("../GameData/Images/LeftButtonEdge.png")) {
		std::cout << "Error: Could Not Load Image." << std::endl;
	}
	this->ResizedLeftClickImage.create(Size.GetWidth(), Size.GetHeight(), Pixels);
	MT::ResizeImage(this->LeftClickImage, this->ResizedLeftClickImage);
	this->LeftClickCurve = MT::ImageToCurve(this->ResizedLeftClickImage, Origin);

	if (!this->RightClickImage.loadFromFile("../GameData/Images/RightButtonEdge.png")) {
		std::cout << "Error: Could Not Load Image." << std::endl;
	}
	this->ResizedRightClickImage.create(Size.GetWidth(), Size.GetHeight(), Pixels);
	MT::ResizeImage(this->RightClickImage, this->ResizedRightClickImage);
	this->RightClickCurve = MT::ImageToCurve(this->ResizedRightClickImage, Origin);

	if (!this->MiddleClickImage.loadFromFile("../GameData/Images/MiddleButtonEdge2.png")) {
		std::cout << "Error: Could Not Load Image." << std::endl;
	}
	this->ResizedMiddleClickImage.create(Size.GetWidth(), Size.GetHeight(), Pixels);
	MT::ResizeImage(this->MiddleClickImage, this->ResizedMiddleClickImage);
	this->MiddleClickCurve = MT::ImageToCurve(this->ResizedMiddleClickImage, Origin);


	delete[] Pixels;
}

//------------------------------------------- Desctructor -------------------------------------------//

MouseKey::~MouseKey() {
	ControlItem::SelectedItem = NULL;
}

//---------------------------------------------- GetX ----------------------------------------------//

double MouseKey::GetX() {
	return this->Mouse.getPosition().x;
}

//---------------------------------------------- GetY ----------------------------------------------//

double MouseKey::GetY() {
	return this->Mouse.getPosition().y;
}

//-------------------------------------------- GetWidth --------------------------------------------//

double MouseKey::GetWidth() {
	return this->Mouse.getSize().x;
}

//-------------------------------------------- GetHeight --------------------------------------------//

double MouseKey::GetHeight() {
	return this->Mouse.getSize().y;
}

//----------------------------------------------- Select ---------------------------------------------//

void MouseKey::Select(int Index) {
	Frame::SelectionSound.play();
	if (Key::SelectedKey != NULL) {
		Key::SelectedKey->UnSelect();
	}
	this->SelectedIndex = Index;
	this->Selected = true;

	Key::SelectedKey = this;

	if (ControlItem::SelectedItem != NULL) {
		ControlItem::SelectedItem->SelectedKey = this;
		ControlItem::SelectedItem->SelectedKeyIndex = Index;

		ControlItem::SelectedItem->SetValue(this->GetValue());
	}
}

//--------------------------------------------- UnSelect ---------------------------------------------//

void MouseKey::UnSelect() {
	this->Selected = false;
	this->SelectedIndex = -1;
}

//--------------------------------------------- Refresh ---------------------------------------------//

void MouseKey::Refresh() {
	Point TopLeftCorner(this->GetX(), this->GetY());
	Point BottomRightCorner(this->GetX() + this->GetWidth(), this->GetY() + this->GetHeight());
	Shape* KeyBoundaries = new Rectangle(TopLeftCorner, BottomRightCorner);

	Point MousePosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

	if (KeyBoundaries->ContainsPoint(MousePosition)) {
		int X = MousePosition.GetX() - TopLeftCorner.GetX();
		int Y = MousePosition.GetY() - TopLeftCorner.GetY();
		if (X < 0) X = 0;
		if (Y < 0) Y = 0;
		if (X >= this->ResizedMouseImage.getSize().x)X = this->ResizedMouseImage.getSize().x - 1;
		if (Y >= this->ResizedMouseImage.getSize().y)Y = this->ResizedMouseImage.getSize().y - 1;
		if (
			this->ResizedMouseSelectionImage.getPixel(X, Y) == sf::Color(0, 255, 0, 255)
			||
			this->ResizedMouseSelectionImage.getPixel(X, Y) == sf::Color(0, 0, 255, 255)
			||
			this->ResizedMouseSelectionImage.getPixel(X, Y) == sf::Color(255, 0, 0, 255)
			) {
			sf::Color TargetColor;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				TargetColor = PRESSED_COLOR;
				this->MousePressed = true;
			}
			else {
				if (this->MousePressed) {
					if (this->ResizedMouseSelectionImage.getPixel(X, Y) == sf::Color(0, 255, 0, 255))this->SelectedIndex = 1;
					else if (this->ResizedMouseSelectionImage.getPixel(X, Y) == sf::Color(0, 0, 255, 255))this->SelectedIndex = 2;
					else this->SelectedIndex = 0;
					this->Select(this->SelectedIndex);
				}
				this->MousePressed = false;
				TargetColor = HOVER_COLOR;
			}
			if (this->ResizedMouseSelectionImage.getPixel(X, Y) == sf::Color(0, 255, 0, 255)) {
				for (std::size_t i = 0; i < this->LeftClickCurve.getVertexCount(); i++) {
					this->RightClickCurve[i].color = MT::Shift(this->RightClickCurve[i].color, TargetColor, SLOW);
				}
				if (this->SelectedIndex == 0) {
					for (std::size_t i = 0; i < this->RightClickCurve.getVertexCount(); i++) {
						this->LeftClickCurve[i].color = MT::Shift(this->LeftClickCurve[i].color, PRESSED_COLOR, SLOW);
					}
				}
				else {
					for (std::size_t i = 0; i < this->LeftClickCurve.getVertexCount(); i++) {
						this->LeftClickCurve[i].color = MT::Shift(this->LeftClickCurve[i].color, TRANSPARENT, SLOW);
					}
				}
				if (this->SelectedIndex == 2) {
					for (std::size_t i = 0; i < this->MiddleClickCurve.getVertexCount(); i++) {
						this->MiddleClickCurve[i].color = MT::Shift(this->MiddleClickCurve[i].color, PRESSED_COLOR, SLOW);
					}
				}
				else {
					for (std::size_t i = 0; i < this->MiddleClickCurve.getVertexCount(); i++) {
						this->MiddleClickCurve[i].color = MT::Shift(this->MiddleClickCurve[i].color, TRANSPARENT, SLOW);
					}
				}
			}
			else if (this->ResizedMouseSelectionImage.getPixel(X, Y) == sf::Color(0, 0, 255, 255)) {
				for (std::size_t i = 0; i < this->MiddleClickCurve.getVertexCount(); i++) {
					this->MiddleClickCurve[i].color = MT::Shift(this->MiddleClickCurve[i].color, TargetColor, SLOW);
				}
				if (this->SelectedIndex == 1) {
					for (std::size_t i = 0; i < this->RightClickCurve.getVertexCount(); i++) {
						this->RightClickCurve[i].color = MT::Shift(this->RightClickCurve[i].color, PRESSED_COLOR, SLOW);
					}
				}
				else {
					for (std::size_t i = 0; i < this->RightClickCurve.getVertexCount(); i++) {
						this->RightClickCurve[i].color = MT::Shift(this->RightClickCurve[i].color, TRANSPARENT, SLOW);
					}
				}
				if (SelectedIndex == 0) {
					for (std::size_t i = 0; i < this->LeftClickCurve.getVertexCount(); i++) {
						this->LeftClickCurve[i].color = MT::Shift(this->LeftClickCurve[i].color, PRESSED_COLOR, SLOW);
					}
				}
				else {
					for (std::size_t i = 0; i < this->LeftClickCurve.getVertexCount(); i++) {
						this->LeftClickCurve[i].color = MT::Shift(this->LeftClickCurve[i].color, TRANSPARENT, SLOW);
					}
				}
			}
			else {
				for (std::size_t i = 0; i < this->LeftClickCurve.getVertexCount(); i++) {
					this->LeftClickCurve[i].color = MT::Shift(this->LeftClickCurve[i].color, TargetColor, SLOW);
				}
				if (SelectedIndex == 2) {
					for (std::size_t i = 0; i < this->MiddleClickCurve.getVertexCount(); i++) {
						this->MiddleClickCurve[i].color = MT::Shift(this->MiddleClickCurve[i].color, PRESSED_COLOR, SLOW);
					}
				}
				else {
					for (std::size_t i = 0; i < this->MiddleClickCurve.getVertexCount(); i++) {
						this->MiddleClickCurve[i].color = MT::Shift(this->MiddleClickCurve[i].color, TRANSPARENT, SLOW);
					}
				}
				if (SelectedIndex == 1) {
					for (std::size_t i = 0; i < this->LeftClickCurve.getVertexCount(); i++) {
						this->RightClickCurve[i].color = MT::Shift(this->RightClickCurve[i].color, PRESSED_COLOR, SLOW);
					}
				}
				else {
					for (std::size_t i = 0; i < this->LeftClickCurve.getVertexCount(); i++) {
						this->RightClickCurve[i].color = MT::Shift(this->RightClickCurve[i].color, TRANSPARENT, SLOW);
					}
				}
			}
		}
		else {
			this->MousePressed = false;
			sf::Color MiddleCurveColor = TRANSPARENT;
			sf::Color LeftCurveColor = TRANSPARENT;
			sf::Color RightCurveColor = TRANSPARENT;
			switch (this->SelectedIndex) {
				case 0: {
					LeftCurveColor = PRESSED_COLOR;
					break;
				}
				case 1: {
					RightCurveColor = PRESSED_COLOR;
					break;
				}
				case 2: {
					MiddleCurveColor = PRESSED_COLOR;
					break;
				}
			}
			for (std::size_t i = 0; i < this->MiddleClickCurve.getVertexCount(); i++) {
				this->MiddleClickCurve[i].color = MT::Shift(this->MiddleClickCurve[i].color, MiddleCurveColor, SLOW);
			}
			for (std::size_t i = 0; i < this->LeftClickCurve.getVertexCount(); i++) {
				this->LeftClickCurve[i].color = MT::Shift(this->LeftClickCurve[i].color, LeftCurveColor, SLOW);
			}
			for (std::size_t i = 0; i < this->RightClickCurve.getVertexCount(); i++) {
				this->RightClickCurve[i].color = MT::Shift(this->RightClickCurve[i].color, RightCurveColor, SLOW);
			}
		}
	}
	else {
		this->MousePressed = false;
		sf::Color MiddleCurveColor = TRANSPARENT;
		sf::Color LeftCurveColor = TRANSPARENT;
		sf::Color RightCurveColor = TRANSPARENT;
		switch (this->SelectedIndex) {
		case 0: {
			LeftCurveColor = PRESSED_COLOR;
			break;
		}
		case 1: {
			RightCurveColor = PRESSED_COLOR;
			break;
		}
		case 2: {
			MiddleCurveColor = PRESSED_COLOR;
			break;
		}
		}
		for (std::size_t i = 0; i < this->MiddleClickCurve.getVertexCount(); i++) {
			this->MiddleClickCurve[i].color = MT::Shift(this->MiddleClickCurve[i].color, MiddleCurveColor, SLOW);
		}
		for (std::size_t i = 0; i < this->LeftClickCurve.getVertexCount(); i++) {
			this->LeftClickCurve[i].color = MT::Shift(this->LeftClickCurve[i].color, LeftCurveColor, SLOW);
		}
		for (std::size_t i = 0; i < this->RightClickCurve.getVertexCount(); i++) {
			this->RightClickCurve[i].color = MT::Shift(this->RightClickCurve[i].color, RightCurveColor, SLOW);
		}
	}

	delete KeyBoundaries;
}

//---------------------------------------------- Draw -----------------------------------------------//

void MouseKey::Draw() {
	GameWindow->draw(this->Mouse);
	GameWindow->draw(this->LeftClickCurve);
	GameWindow->draw(this->RightClickCurve);
	GameWindow->draw(this->MiddleClickCurve);
}

//-------------------------------------------- Get Value --------------------------------------------//

std::string MouseKey::GetValue() {
	std::string Result = "";
	switch (this->SelectedIndex)
	{
		case 0: {
			Result = "Left Click";
			break;
		}
		case 1: {
			Result = "Right Click";
			break;
		}
		case 2: {
			Result = "Middle Click";
			break;
		}
	}
	return Result;
}