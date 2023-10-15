#pragma once
#include "BackIcon.h"
#include "Point.h"
#include "Circle.h"
#include "Methods.h"
#include "Frame.h"

//------------------------------------ Constructor ------------------------------------//

BackIcon::BackIcon() {
	this->MouseInside = false;

	double X, Y, Width, Height;
	this->RotationSpeed = 0;

	this->OutterCircle = sf::CircleShape(40);
	this->OutterCircle.setFillColor(COLOR);
	this->OutterCircle.setPosition(10, 10);

	this->InnerCircle = sf::CircleShape(36);
	this->InnerCircle.setFillColor(BACKGROUND);
	this->InnerCircle.setPosition(14, 14);

	Width = 40;
	Height = 80;
	this->RectangleGap = sf::RectangleShape(sf::Vector2f(Width, Height));
	X = this->OutterCircle.getGlobalBounds().left + (this->OutterCircle.getGlobalBounds().width - this->RectangleGap.getGlobalBounds().width) / 2.0 + Width / 2.0;
	Y = this->OutterCircle.getGlobalBounds().top + Height / 2.0;
	this->RectangleGap.setPosition(X, Y);
	this->RectangleGap.setOrigin(Width / 2.0, Height / 2.0);
	this->RectangleGap.setFillColor(BACKGROUND);

	Width = 30;
	Height = 5;
	this->TopBackArrow = sf::RectangleShape(sf::Vector2f(Width, Height));
	X = X - this->OutterCircle.getGlobalBounds().width / 8.0;
	Y = this->OutterCircle.getGlobalBounds().top + (this->OutterCircle.getGlobalBounds().height - this->TopBackArrow.getGlobalBounds().height) / 2.0;
	this->TopBackArrow.setPosition(X , Y);
	this->TopBackArrow.setFillColor(COLOR);

	this->BottomBackArrow = sf::RectangleShape(sf::Vector2f(Width, Height));
	Y = this->OutterCircle.getGlobalBounds().top + (this->OutterCircle.getGlobalBounds().height - this->TopBackArrow.getGlobalBounds().height) / 2.0;
	this->BottomBackArrow.setPosition(X, Y + Height);
	this->BottomBackArrow.setFillColor(COLOR);
	this->BottomBackArrow.setOrigin(this->BottomBackArrow.getOrigin().x, this->BottomBackArrow.getOrigin().y + Height);

	this->TopBackArrow.setRotation(45);
	this->BottomBackArrow.setRotation(-45);

}

//------------------------------------ Destructor ------------------------------------//

BackIcon::~BackIcon() {
	
}

//-------------------------------------- Fade In -------------------------------------//

void BackIcon::FadeIn() {

}

//------------------------------------- Fade Out -------------------------------------//

void BackIcon::FadeOut() {

}

//------------------------------------- Refresh --------------------------------------//

void BackIcon::Refresh() {
	Point Center(this->OutterCircle.getGlobalBounds().left + this->OutterCircle.getGlobalBounds().width / 2.0, this->OutterCircle.getGlobalBounds().top + this->OutterCircle.getGlobalBounds().height / 2.0);
	double Radius = this->OutterCircle.getGlobalBounds().width / 2.0;
	Shape* BackBoundaries = new Circle(Center, Radius);

	Point MousePosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

	if (BackBoundaries->ContainsPoint(MousePosition)) {
		this->RotationSpeed += 0.1;
		if (this->RotationSpeed > 3)this->RotationSpeed = 3;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			this->OutterCircle.setFillColor(MT::Shift(this->OutterCircle.getFillColor(), PRESSED_COLOR, SLOW));
			this->TopBackArrow.setFillColor(MT::Shift(this->TopBackArrow.getFillColor(), PRESSED_COLOR, SLOW));
			this->BottomBackArrow.setFillColor(MT::Shift(this->BottomBackArrow.getFillColor(), PRESSED_COLOR, SLOW));
		}
		else {
			this->OutterCircle.setFillColor(MT::Shift(this->OutterCircle.getFillColor(), HOVER_COLOR, SLOW));
			this->TopBackArrow.setFillColor(MT::Shift(this->TopBackArrow.getFillColor(), HOVER_COLOR, SLOW));
			this->BottomBackArrow.setFillColor(MT::Shift(this->BottomBackArrow.getFillColor(), HOVER_COLOR, SLOW));
		}
		this->MouseInside = true;
	}
	else {
		this->RotationSpeed -= 0.05;
		if (this->RotationSpeed < 0)this->RotationSpeed = 0;

		this->OutterCircle.setFillColor(MT::Shift(this->OutterCircle.getFillColor(), COLOR, SLOW));
		this->TopBackArrow.setFillColor(MT::Shift(this->TopBackArrow.getFillColor(), COLOR, SLOW));
		this->BottomBackArrow.setFillColor(MT::Shift(this->BottomBackArrow.getFillColor(), COLOR, SLOW));
		this->MouseInside = false;
	}

	this->RectangleGap.setRotation(this->RectangleGap.getRotation() + this->RotationSpeed);

	delete BackBoundaries;
}

//--------------------------------------- Draw ---------------------------------------//

void BackIcon::Draw() {
	GameWindow->draw(this->OutterCircle);
	GameWindow->draw(this->InnerCircle);
	GameWindow->draw(this->RectangleGap);
	GameWindow->draw(this->TopBackArrow);
	GameWindow->draw(this->BottomBackArrow);
}

//------------------------------------ Mouse Over ------------------------------------//

bool BackIcon::MouseOver() {
	return this->MouseInside;
}