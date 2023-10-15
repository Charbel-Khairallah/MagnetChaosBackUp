#pragma once
#include "MagneticField.h"

int MagneticField::MaxRadius = 75;

//-------------------------------------- Constructor --------------------------------------//

MagneticField::MagneticField(Point Center, Dimension BlockSize) {
	this->CurrentIntensity = 0;
	this->Center = Center;
	this->BlockSize = BlockSize;
	this->FadingOut = false;

	this->Field = sf::CircleShape(0);
	this->Field.setFillColor(TRANSPARENT);
}

//--------------------------------------- Destructor --------------------------------------//

MagneticField::~MagneticField() {
	
}

//------------------------------------ Clamp Intensity ------------------------------------//

void MagneticField::ClampIntensity() {
	if (this->CurrentIntensity > 2)this->CurrentIntensity = 2;
	if (this->CurrentIntensity < 0)this->CurrentIntensity = 0;
}

//---------------------------------------- Refresh ----------------------------------------//

void MagneticField::Refresh(double Intensity) {
	if (this->FadingOut) {
		this->Field.setFillColor(MT::Shift(this->Field.getFillColor(), TRANSPARENT, SLOW));
	}
	else {
		this->CurrentIntensity = Intensity;
		this->ClampIntensity();

		this->Field.setRadius(MagneticField::MaxRadius * this->CurrentIntensity);
		this->Field.setFillColor(MT::Mix(FIELD_COLOR, TRANSPARENT, Intensity));

		double X = this->Center.GetX() - this->Field.getRadius();
		double Y = this->Center.GetY() - this->Field.getRadius();
		this->Field.setPosition(X, Y);
	}

}

//------------------------------------------ Draw -----------------------------------------//

void MagneticField::Draw() {
	GameWindow->draw(this->Field);
}

//---------------------------------------- Fade Out ---------------------------------------//

void MagneticField::FadeOut() {
	this->FadingOut = true;
}

//------------------------------------- Get Intensity -------------------------------------//

double MagneticField::GetIntensity() {
	return this->CurrentIntensity;
}

//------------------------------------- Get Boundaries ------------------------------------//

Circle MagneticField::GetBoundaries() {
	Point Center(this->Field.getPosition().x, this->Field.getPosition().y);
	double Radius = this->Field.getRadius();
	return Circle(Center, Radius);
}