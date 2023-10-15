#pragma once
#include "Bar.h"
#include "Methods.h"
#include "Frame.h"

//------------------------------------- Constructor ------------------------------------//

Bar::Bar(Point Origin, Dimension Size, double CenterOffsetPercentage, double Thickness, double Rate, double InitialValue, sf::Color BackgroundColor) {
	this->Origin = Origin;
	this->Size = Size;
	this->CenterOffsetPercentage = CenterOffsetPercentage;
	this->Thickness = Thickness;
	this->Rate = Rate;
	this->ActualValue = this->CurrentValue = InitialValue;
	this->InitialValue = InitialValue;

	/* Top Left Corner */
	this->FrontTopLeftCover = CurvilinearTriangle(Origin, Dimension(Size.GetHeight() / 2.0, Size.GetHeight() / 2.0), Thickness, Corner::TopLeft, COLOR);
	this->BackTopLeftCover = CurvilinearTriangle(Origin - Dimension(Thickness, Thickness), Dimension(Size.GetHeight() / 2.0, Size.GetHeight() / 2.0), Thickness, Corner::TopLeft, BackgroundColor);
	
	/* Bottom Left Corner */
	this->FrontBottomLeftCover = CurvilinearTriangle(Origin + Dimension(0, Size.GetHeight() / 2.0), Dimension(Size.GetHeight() / 2.0, Size.GetHeight() / 2.0), Thickness, Corner::BottomLeft, COLOR);
	this->BackBottomLeftCover = CurvilinearTriangle(Origin - Dimension(Thickness, - Thickness - Size.GetHeight() / 2.0), Dimension(Size.GetHeight() / 2.0, Size.GetHeight() / 2.0), Thickness, Corner::BottomLeft, BackgroundColor);

	/* Top Right Corner */
	this->FrontTopRightCover = CurvilinearTriangle(Origin + Dimension(Size.GetWidth() - Size.GetHeight() / 2.0, 0), Dimension(Size.GetHeight() / 2.0, Size.GetHeight() / 2.0), Thickness, Corner::TopRight, COLOR);
	this->BackTopRightCover = CurvilinearTriangle(Origin - Dimension(-Thickness - Size.GetWidth() + Size.GetHeight() / 2.0, Thickness), Dimension(Size.GetHeight() / 2.0, Size.GetHeight() / 2.0), Thickness, Corner::TopRight, BackgroundColor);

	/* Bottom Right Corner */
	this->FrontBottomRightCover = CurvilinearTriangle(Origin + Dimension(Size.GetWidth() - Size.GetHeight() / 2.0, Size.GetHeight() / 2.0), Dimension(Size.GetHeight() / 2.0, Size.GetHeight() / 2.0), Thickness, Corner::BottomRight, COLOR);
	this->BackBottomRightCover = CurvilinearTriangle(Origin - Dimension(-Thickness - Size.GetWidth() + Size.GetHeight() / 2.0, - Thickness - Size.GetHeight() / 2.0), Dimension(Size.GetHeight() / 2.0, Size.GetHeight() / 2.0), Thickness, Corner::BottomRight, BackgroundColor);
	
	/* Top Border */
	this->TopBorderRectangle = sf::RectangleShape(sf::Vector2f(Size.GetWidth() - Size.GetHeight(), Thickness));
	this->TopBorderRectangle.setPosition(Origin.GetX() + Size.GetHeight() / 2.0, Origin.GetY() - Thickness);
	this->TopBorderRectangle.setFillColor(COLOR);
	
	/* Bottom Border */
	this->BottomBorderRectangle = sf::RectangleShape(sf::Vector2f(Size.GetWidth() - Size.GetHeight(), Thickness));
	this->BottomBorderRectangle.setPosition(Origin.GetX() + Size.GetHeight() / 2.0, Origin.GetY() + Size.GetHeight());
	this->BottomBorderRectangle.setFillColor(COLOR);

	/* Actual Bar */
	this->BarValue = sf::RectangleShape(sf::Vector2f(Size.GetWidth() * 0.5, Size.GetHeight()));
	this->BarValue.setPosition(Origin.GetX(), Origin.GetY());
	this->BarValue.setFillColor(ERROR_COLOR);
	this->Refresh();

}

Bar::Bar() {

}

//------------------------------------- Destructor ------------------------------------//

Bar::~Bar() {
	
}

//--------------------------------------- Refresh -------------------------------------//

void Bar::Refresh() {
	this->CurrentValue = MT::Shift(this->CurrentValue, this->ActualValue, NORMAL);

	if (this->CurrentValue >= this->CenterOffsetPercentage) {
		double PositionShift = this->Origin.GetX() + this->Size.GetWidth() * this->CenterOffsetPercentage / 100.0;
		double ActualWidth = this->Size.GetWidth() * (this->CurrentValue - this->CenterOffsetPercentage) / 100.0;
		this->BarValue.setPosition(PositionShift, this->BarValue.getGlobalBounds().top);
		this->BarValue.setSize(sf::Vector2f(ActualWidth, this->BarValue.getGlobalBounds().height));

		double Factor = (this->CurrentValue - this->CenterOffsetPercentage) / (double)(100 - this->CenterOffsetPercentage);
		this->BarValue.setFillColor(MT::Mix(ERROR_COLOR, sf::Color(125, 125, 125, 255), Factor));
	}
	else {
		double ActualWidth = this->Size.GetWidth() * (this->CenterOffsetPercentage - this->CurrentValue) / 100.0;
		double PositionShift = this->Origin.GetX() + this->Size.GetWidth() * this->CenterOffsetPercentage / 100.0 - ActualWidth;
		this->BarValue.setPosition(PositionShift, this->BarValue.getGlobalBounds().top);
		this->BarValue.setSize(sf::Vector2f(ActualWidth, this->BarValue.getGlobalBounds().height));
		
		double Factor = (this->CenterOffsetPercentage - this->CurrentValue) / (double)(this->CenterOffsetPercentage);
		this->BarValue.setFillColor(MT::Mix(PRESSED_COLOR, sf::Color(125, 125, 125, 255), Factor));
	}
}

//---------------------------------------- Draw ---------------------------------------//

void Bar::Draw() {
	GameWindow->draw(this->BarValue);

	this->FrontBottomLeftCover.Draw();
	this->FrontBottomRightCover.Draw();
	this->FrontTopLeftCover.Draw();
	this->FrontTopRightCover.Draw();

	this->BackBottomLeftCover.Draw();
	this->BackBottomRightCover.Draw();
	this->BackTopLeftCover.Draw();
	this->BackTopRightCover.Draw();

	GameWindow->draw(this->TopBorderRectangle);
	GameWindow->draw(this->BottomBorderRectangle);
}

//------------------------------------------ Clamp -----------------------------------------//

void Bar::Clamp() {
	if (this->ActualValue > 100)this->ActualValue = 100;
	if (this->ActualValue < 0)this->ActualValue = 0;
}


//---------------------------------------- Get Value ---------------------------------------//

double Bar::GetValue() {
	return this->ActualValue;
}

//----------------------------------------- Get Rate ---------------------------------------//

double Bar::GetRate() {
	return this->Rate;
}

//----------------------------------------- Set Rate ---------------------------------------//

void Bar::SetRate(double NewRate) {
	this->Rate = NewRate;
}

//------------------------------------------- Reset ----------------------------------------//

void Bar::Reset() {
	this->ActualValue = this->InitialValue;
}

//-------------------------------------- Get Bar Color -------------------------------------//

sf::Color Bar::GetBarColor() {
	return this->BarValue.getFillColor();
}


//---------------------------------------- + Operator --------------------------------------//

Bar& Bar::operator += (const double& Value) {
	this->ActualValue += Value;
	this->Clamp();
	return *this;
}

//---------------------------------------- - Operator --------------------------------------//

Bar& Bar::operator -= (const double& Value) {
	this->ActualValue -= Value;
	this->Clamp();
	return *this;
}

//---------------------------------------- ++ Operator -------------------------------------//

Bar& Bar::operator ++() {
	this->ActualValue += this->Rate;
	this->Clamp();
	return *this;
}

//---------------------------------------- -- Operator -------------------------------------//

Bar& Bar::operator --() {
	this->ActualValue -= this->Rate;
	this->Clamp();
	return *this;
}

//------------------------------------------ GetX -----------------------------------------//

double Bar::GetX() {
	return this->Origin.GetX();
}

//------------------------------------------ GetX -----------------------------------------//

double Bar::GetY() {
	return this->Origin.GetY();
}
//------------------------------------------ GetX -----------------------------------------//

double Bar::GetWidth() {
	return this->Size.GetWidth();
}
//------------------------------------------ GetX -----------------------------------------//

double Bar::GetHeight() {
	return this->Size.GetHeight();
}