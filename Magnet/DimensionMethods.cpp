#pragma once
#include "Dimension.h"
#include "Methods.h"

//------------------------------------ Constructors -----------------------------------//

Dimension::Dimension() {
	this->Width = this->Height = 0;
}


Dimension::Dimension(double Width, double Height) {
	this->Width = Width;
	this->Height = Height;
}

//-------------------------------------- GetWidth -------------------------------------//


double Dimension::GetWidth() {
	return this->Width;
}

//-------------------------------------- GetHeight ------------------------------------//

double Dimension::GetHeight() {
	return this->Height;
}

//-------------------------------------- GetLength ------------------------------------//

double Dimension::GetLength() {
	return sqrt(this->Width * this->Width + this->Height * this->Height);
}

//-------------------------------------- GetVector ------------------------------------//

sf::Vector2f Dimension::Vector2F() {
	return sf::Vector2f(this->Width, this->Height);
}

//------------------------------------- += Operator -----------------------------------//

Dimension & Dimension::operator+=(Dimension Other) {
	this->Width += Other.GetWidth();
	this->Height += Other.GetHeight();
	return *this;
}

//------------------------------------- -= Operator -----------------------------------//

Dimension & Dimension::operator-=(Dimension Other) {
	this->Width -= Other.GetWidth();
	this->Height -= Other.GetHeight();
	return *this;
}

//-------------------------------------- + Operator -----------------------------------//

Dimension Dimension::operator +(Dimension Other) {
	return Dimension(this->Width + Other.GetWidth(), this->Height + Other.GetHeight());
}

//-------------------------------------- - Operator -----------------------------------//

Dimension Dimension::operator -(Dimension Other) {
	return Dimension(this->Width - Other.GetWidth(), this->Height - Other.GetHeight());
}

//-------------------------------------- > Operator -----------------------------------//

bool Dimension::operator > (Dimension Other) {
	return this->GetLength() > Other.GetLength();
}

//-------------------------------------- < Operator -----------------------------------//


bool Dimension::operator < (Dimension Other) {
	return this->GetLength() < Other.GetLength();
}