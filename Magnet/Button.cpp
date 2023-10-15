#pragma once
#include "Button.h"

//------------------------------------ Constructor ------------------------------------//

Button::Button(Point Position, Dimension Size, std::string ButtonText, double Thickness, double BorderRadius) {
	double X, Y, Width, Height;
	this->Position = Position;
	this->Size = Size;
	this->Thickness = Thickness;
	this->BorderRadius = BorderRadius;
	this->Disabled = false;

	/* Colors */
	this->MainColor = COLOR;
	this->HoverColor = HOVER_COLOR;
	this->PressedColor = PRESSED_COLOR;
	this->DisabledColor = DISABLED_COLOR;

	this->MainFill = SECONDARY_BACKGROUND;
	this->HoverFill = BACKGROUND;
	this->PressedFill = BACKGROUND;
	this->DisabledFill = BACKGROUND;

	this->BorderColor = SECONDARY_BACKGROUND;
	this->BorderHoverColor = HOVER_COLOR;
	this->BorderPressedColor = PRESSED_COLOR;
	this->DisabledBorderColor = DISABLED_COLOR;

	/* Top Left Inner Circle */
	this->TopLeftInnerCircle = sf::CircleShape(this->BorderRadius - this->Thickness);
	this->TopLeftInnerCircle.setFillColor(this->MainFill);

	X = this->TopLeftInnerCircle.getOrigin().x;
	Y = this->TopLeftInnerCircle.getOrigin().y;
	Width = this->TopLeftInnerCircle.getRadius() * 2;
	Height = this->TopLeftInnerCircle.getRadius() * 2;
	this->TopLeftInnerCircle.setOrigin(X + Width / 2.0, Y + Height / 2.0);

	X = this->Position.GetX() + this->BorderRadius;
	Y = this->Position.GetY() + this->BorderRadius;
	this->TopLeftInnerCircle.setPosition(X, Y);


	/* Top Right Inner Circle */
	this->TopRightInnerCircle = sf::CircleShape(this->BorderRadius - this->Thickness);
	this->TopRightInnerCircle.setFillColor(this->MainFill);

	X = this->TopRightInnerCircle.getOrigin().x;
	Y = this->TopRightInnerCircle.getOrigin().y;
	Width = this->TopRightInnerCircle.getRadius() * 2;
	Height = this->TopRightInnerCircle.getRadius() * 2;
	this->TopRightInnerCircle.setOrigin(X + Width / 2.0, Y + Height / 2.0);

	X = this->Position.GetX() + this->Size.GetWidth() - this->BorderRadius;
	Y = this->Position.GetY() + this->BorderRadius;
	this->TopRightInnerCircle.setPosition(X, Y);


	/* Bottom Left Inner Circle */
	this->BottomLeftInnerCircle = sf::CircleShape(this->BorderRadius - this->Thickness);
	this->BottomLeftInnerCircle.setFillColor(this->MainFill);

	X = this->BottomLeftInnerCircle.getOrigin().x;
	Y = this->BottomLeftInnerCircle.getOrigin().y;
	Width = this->BottomLeftInnerCircle.getRadius() * 2;
	Height = this->BottomLeftInnerCircle.getRadius() * 2;
	this->BottomLeftInnerCircle.setOrigin(X + Width / 2.0, Y + Height / 2.0);

	X = this->Position.GetX() + this->BorderRadius;
	Y = this->Position.GetY() + this->Size.GetHeight() - this->BorderRadius;
	this->BottomLeftInnerCircle.setPosition(X, Y);


	/* Bottom Right Inner Circle */
	this->BottomRightInnerCircle = sf::CircleShape(this->BorderRadius - this->Thickness);
	this->BottomRightInnerCircle.setFillColor(this->MainFill);

	X = this->BottomRightInnerCircle.getOrigin().x;
	Y = this->BottomRightInnerCircle.getOrigin().y;
	Width = this->BottomRightInnerCircle.getRadius() * 2;
	Height = this->BottomRightInnerCircle.getRadius() * 2;
	this->BottomRightInnerCircle.setOrigin(X + Width / 2.0, Y + Height / 2.0);

	X = this->Position.GetX() + this->Size.GetWidth() - this->BorderRadius;
	Y = this->Position.GetY() + this->Size.GetHeight() - this->BorderRadius;
	this->BottomRightInnerCircle.setPosition(X, Y);

	/* ============================= */

	/* Top Left Outer Circle */
	this->TopLeftOuterCircle = sf::CircleShape(this->BorderRadius);
	this->TopLeftOuterCircle.setFillColor(this->BorderColor);

	X = this->TopLeftOuterCircle.getOrigin().x;
	Y = this->TopLeftOuterCircle.getOrigin().y;
	Width = this->TopLeftOuterCircle.getRadius() * 2;
	Height = this->TopLeftOuterCircle.getRadius() * 2;
	this->TopLeftOuterCircle.setOrigin(X + Width / 2.0, Y + Height / 2.0);

	X = this->Position.GetX() + this->BorderRadius;
	Y = this->Position.GetY() + this->BorderRadius;
	this->TopLeftOuterCircle.setPosition(X, Y);


	/* Top Right Outer Circle */
	this->TopRightOuterCircle = sf::CircleShape(this->BorderRadius);
	this->TopRightOuterCircle.setFillColor(this->BorderColor);

	X = this->TopRightOuterCircle.getOrigin().x;
	Y = this->TopRightOuterCircle.getOrigin().y;
	Width = this->TopRightOuterCircle.getRadius() * 2;
	Height = this->TopRightOuterCircle.getRadius() * 2;
	this->TopRightOuterCircle.setOrigin(X + Width / 2.0, Y + Height / 2.0);

	X = this->Position.GetX() + this->Size.GetWidth() - this->BorderRadius;
	Y = this->Position.GetY() + this->BorderRadius;
	this->TopRightOuterCircle.setPosition(X, Y);


	/* Bottom Left Outer Circle */
	this->BottomLeftOuterCircle = sf::CircleShape(this->BorderRadius);
	this->BottomLeftOuterCircle.setFillColor(this->BorderColor);

	X = this->BottomLeftOuterCircle.getOrigin().x;
	Y = this->BottomLeftOuterCircle.getOrigin().y;
	Width = this->BottomLeftOuterCircle.getRadius() * 2;
	Height = this->BottomLeftOuterCircle.getRadius() * 2;
	this->BottomLeftOuterCircle.setOrigin(X + Width / 2.0, Y + Height / 2.0);

	X = this->Position.GetX() + this->BorderRadius;
	Y = this->Position.GetY() + this->Size.GetHeight() - this->BorderRadius;
	this->BottomLeftOuterCircle.setPosition(X, Y);


	/* Bottom Right Outer Circle */
	this->BottomRightOuterCircle = sf::CircleShape(this->BorderRadius);
	this->BottomRightOuterCircle.setFillColor(this->BorderColor);

	X = this->BottomRightOuterCircle.getOrigin().x;
	Y = this->BottomRightOuterCircle.getOrigin().y;
	Width = this->BottomRightOuterCircle.getRadius() * 2;
	Height = this->BottomRightOuterCircle.getRadius() * 2;
	this->BottomRightOuterCircle.setOrigin(X + Width / 2.0, Y + Height / 2.0);

	X = this->Position.GetX() + this->Size.GetWidth() - this->BorderRadius;
	Y = this->Position.GetY() + this->Size.GetHeight() - this->BorderRadius;
	this->BottomRightOuterCircle.setPosition(X, Y);

	/* ============================= */

	/* Main Vertical Rectangle */
	Width = this->Size.GetWidth() - this->BorderRadius * 2;
	Height = this->Size.GetHeight() - this->Thickness * 2;
	this->MainVerticalRectangle = sf::RectangleShape(sf::Vector2f(Width, Height));

	X = this->Position.GetX() + this->BorderRadius;
	Y = this->Position.GetY() + this->Thickness;
	this->MainVerticalRectangle.setPosition(X, Y);

	this->MainVerticalRectangle.setFillColor(this->MainFill);

	/* Main Horizontal Rectangle */
	Width = this->Size.GetWidth() - this->Thickness * 2;
	Height = this->Size.GetHeight() - this->BorderRadius * 2;
	this->MainHorizontalRectangle = sf::RectangleShape(sf::Vector2f(Width, Height));

	X = this->Position.GetX() + this->Thickness;
	Y = this->Position.GetY() + this->BorderRadius;
	this->MainHorizontalRectangle.setPosition(X, Y);

	this->MainHorizontalRectangle.setFillColor(this->MainFill);

	/* ============================= */

	/* Top Edge Rectangle */
	Width = this->Size.GetWidth() - this->BorderRadius * 2;
	Height = this->Thickness;
	this->TopEdgeRectangle = sf::RectangleShape(sf::Vector2f(Width, Height));

	X = this->Position.GetX() + this->BorderRadius;
	Y = this->Position.GetY();
	this->TopEdgeRectangle.setPosition(X, Y);

	this->TopEdgeRectangle.setFillColor(this->BorderColor);

	/* Bottom Edge Rectangle */
	Width = this->Size.GetWidth() - this->BorderRadius * 2;
	Height = this->Thickness;
	this->BottomEdgeRectangle = sf::RectangleShape(sf::Vector2f(Width, Height));

	X = this->Position.GetX() + this->BorderRadius;
	Y = this->Position.GetY() + this->Size.GetHeight() - this->Thickness;
	this->BottomEdgeRectangle.setPosition(X, Y);

	this->BottomEdgeRectangle.setFillColor(this->BorderColor);

	/* Left Edge Rectangle */
	Width = this->Thickness;
	Height = this->Size.GetHeight() - this->BorderRadius * 2;
	this->LeftEdgeRectangle = sf::RectangleShape(sf::Vector2f(Width, Height));

	X = this->Position.GetX();
	Y = this->Position.GetY() + this->BorderRadius;
	this->LeftEdgeRectangle.setPosition(X, Y);

	this->LeftEdgeRectangle.setFillColor(this->BorderColor);

	/* Right Edge Rectangle */
	Width = this->Thickness;
	Height = this->Size.GetHeight() - this->BorderRadius * 2;
	this->RightEdgeRectangle = sf::RectangleShape(sf::Vector2f(Width, Height));

	X = this->Position.GetX() + this->Size.GetWidth() - this->Thickness;
	Y = this->Position.GetY() + this->BorderRadius;
	this->RightEdgeRectangle.setPosition(X, Y);

	this->RightEdgeRectangle.setFillColor(this->BorderColor);

	/* ============================= */

	/* Text */
	this->ButtonText = sf::Text(ButtonText, FONT, H3);
	this->ButtonText.setFillColor(this->MainColor);

	Width = this->ButtonText.getGlobalBounds().width;
	Height = this->ButtonText.getCharacterSize();
	X = Position.GetX() + (Size.GetWidth() - Width) / 2.0;
	Y = Position.GetY() + (Size.GetHeight() - Height) / 2.0;
	this->ButtonText.setPosition(X, Y);
}

Button::Button() {
	
}

//------------------------------------ Destructor ------------------------------------//

Button::~Button() {
	
}

//-------------------------------------- Enable --------------------------------------//

void Button::Enable() {
	this->Disabled = false;
}

//-------------------------------------- Disable -------------------------------------//

void Button::Disable() {
	this->Disabled = true;
}

//------------------------------------ Is Enabled ------------------------------------//

bool Button::IsEnabled() {
	return !this->Disabled;
}

//------------------------------------ Mouse Over ------------------------------------//

bool Button::MouseOver() {
	bool Result;
	Point TopLeftCorner = this->Position;
	Point BottomRightCorner = this->Position + this->Size;
	Shape * ButtonBoundaries = new Rectangle(TopLeftCorner, BottomRightCorner);
	Point MousePosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
	Result = ButtonBoundaries->ContainsPoint(MousePosition);
	delete ButtonBoundaries;
	return Result;
}

//------------------------------------- Refresh --------------------------------------//

void Button::Refresh() {
	sf::Color CurrentColor;
	sf::Color CurrentFill;
	sf::Color CurrentBorderColor;
	if (this->Disabled) {
		CurrentColor = this->DisabledColor;
		CurrentFill = this->DisabledFill;
		CurrentBorderColor = this->DisabledBorderColor;
	}
	else {
		if (this->MouseOver()) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				CurrentColor = this->PressedColor;
				CurrentFill = this->PressedFill;
				CurrentBorderColor = this->BorderPressedColor;
			}
			else {
				CurrentColor = this->HoverColor;
				CurrentFill = this->HoverFill;
				CurrentBorderColor = this->BorderHoverColor;
			}
		}
		else {
			CurrentColor = this->MainColor;
			CurrentFill = this->MainFill;
			CurrentBorderColor = this->BorderColor;
		}
	}
	this->ButtonText.setFillColor(MT::Shift(this->ButtonText.getFillColor(), CurrentColor, NORMAL));

	this->TopLeftInnerCircle.setFillColor(MT::Shift(this->TopLeftInnerCircle.getFillColor(), CurrentFill, SLOW));
	this->TopRightInnerCircle.setFillColor(MT::Shift(this->TopRightInnerCircle.getFillColor(), CurrentFill, SLOW));
	this->BottomLeftInnerCircle.setFillColor(MT::Shift(this->BottomLeftInnerCircle.getFillColor(), CurrentFill, SLOW));
	this->BottomRightInnerCircle.setFillColor(MT::Shift(this->BottomRightInnerCircle.getFillColor(), CurrentFill, SLOW));

	this->MainVerticalRectangle.setFillColor(MT::Shift(this->MainVerticalRectangle.getFillColor(), CurrentFill, SLOW));
	this->MainHorizontalRectangle.setFillColor(MT::Shift(this->MainHorizontalRectangle.getFillColor(), CurrentFill, SLOW));

	this->TopLeftOuterCircle.setFillColor(MT::Shift(this->TopLeftOuterCircle.getFillColor(), CurrentBorderColor, SLOW));
	this->TopRightOuterCircle.setFillColor(MT::Shift(this->TopRightOuterCircle.getFillColor(), CurrentBorderColor, SLOW));
	this->BottomLeftOuterCircle.setFillColor(MT::Shift(this->BottomLeftOuterCircle.getFillColor(), CurrentBorderColor, SLOW));
	this->BottomRightOuterCircle.setFillColor(MT::Shift(this->BottomRightOuterCircle.getFillColor(), CurrentBorderColor, SLOW));

	this->TopEdgeRectangle.setFillColor(MT::Shift(this->TopEdgeRectangle.getFillColor(), CurrentBorderColor, SLOW));
	this->BottomEdgeRectangle.setFillColor(MT::Shift(this->BottomEdgeRectangle.getFillColor(), CurrentBorderColor, SLOW));
	this->LeftEdgeRectangle.setFillColor(MT::Shift(this->LeftEdgeRectangle.getFillColor(), CurrentBorderColor, SLOW));
	this->RightEdgeRectangle.setFillColor(MT::Shift(this->RightEdgeRectangle.getFillColor(), CurrentBorderColor, SLOW));
}

//--------------------------------------- Draw ---------------------------------------//

void Button::Draw() {
	GameWindow->draw(this->TopLeftOuterCircle);
	GameWindow->draw(this->TopRightOuterCircle);
	GameWindow->draw(this->BottomLeftOuterCircle);
	GameWindow->draw(this->BottomRightOuterCircle);

	GameWindow->draw(this->TopEdgeRectangle);
	GameWindow->draw(this->BottomEdgeRectangle);
	GameWindow->draw(this->LeftEdgeRectangle);
	GameWindow->draw(this->RightEdgeRectangle);


	GameWindow->draw(this->TopLeftInnerCircle);
	GameWindow->draw(this->TopRightInnerCircle);
	GameWindow->draw(this->BottomLeftInnerCircle);
	GameWindow->draw(this->BottomRightInnerCircle);

	GameWindow->draw(this->MainVerticalRectangle);
	GameWindow->draw(this->MainHorizontalRectangle);


	GameWindow->draw(this->ButtonText);
}