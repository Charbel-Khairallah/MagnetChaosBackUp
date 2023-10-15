#pragma once
#include "CurvilinearTriangle.h"
#include "Frame.h"

// X^2 / Width^2 + Y^2 / Height^2 = 1

//------------------------------------- Constructor ------------------------------------//

CurvilinearTriangle::CurvilinearTriangle(Point Origin, Dimension Size, double Thickness, Corner Position, sf::Color FillColor) {
	//this->Origin = Origin + Dimension(Thickness, Thickness);
	this->Origin = Origin;
	this->Size = Size;
	this->Position = Position;
	this->FillColor = FillColor;
	this->Thickness = Thickness;

	double X, Y;
	int i;
	int MaxPoints = 50;
	this->Shape = sf::VertexArray(sf::TriangleFan);

	this->HorizontalRectangle.setFillColor(this->FillColor);
	this->HorizontalRectangle.setSize(sf::Vector2f(this->Size.GetWidth() + this->Thickness, this->Thickness));

	this->VerticalRectangle.setFillColor(this->FillColor);
	this->VerticalRectangle.setSize(sf::Vector2f(this->Thickness, this->Size.GetHeight() + this->Thickness));


	/* Top Left Corner */
	if (this->Position == Corner::TopLeft) {
		for (i = 0; i <= MaxPoints; i++) {
			Y = this->Origin.GetY();
			X = this->Origin.GetX() + Size.GetWidth() * i / (double)MaxPoints;
			this->Shape.append(sf::Vertex(sf::Vector2f(X, Y), this->FillColor));
		}

		for (i = MaxPoints; i >= 0; i--) {
			X = this->Origin.GetX() + Size.GetWidth() * i / (double)MaxPoints;
			Y = this->Origin.GetY() + Size.GetHeight() - sqrt(1 - (Size.GetWidth() * (MaxPoints - i) / (double)MaxPoints * Size.GetWidth() * (MaxPoints - i) / (double)MaxPoints) / (Size.GetWidth() * Size.GetWidth())) * Size.GetHeight();
			this->Shape.append(sf::Vertex(sf::Vector2f(X, Y), this->FillColor));
		}

		for (i = MaxPoints; i >= 0; i--) {
			X = this->Origin.GetX();
			Y = this->Origin.GetY() + Size.GetHeight() * i / (double)MaxPoints;
			this->Shape.append(sf::Vertex(sf::Vector2f(X, Y), this->FillColor));
		}

		this->VerticalRectangle.setPosition(sf::Vector2f(this->Origin.GetX() - this->Thickness, Origin.GetY() - this->Thickness));
		this->HorizontalRectangle.setPosition(sf::Vector2f(this->Origin.GetX() - this->Thickness, Origin.GetY() - this->Thickness));
	}
	/* Top Right Corner */
	else if (this->Position == Corner::TopRight) {
		for (i = MaxPoints; i >= 0; i--) {
			X = this->Origin.GetX() + Size.GetWidth();
			Y = this->Origin.GetY() + Size.GetHeight() * (MaxPoints - i) / (double)MaxPoints;
			this->Shape.append(sf::Vertex(sf::Vector2f(X, Y), this->FillColor));
		}

		for (i = MaxPoints; i >= 0; i--) {
			X = this->Origin.GetX() + Size.GetWidth() * i / (double)MaxPoints;
			Y = this->Origin.GetY() + Size.GetHeight() - sqrt(1 - (Size.GetWidth() * i / (double)MaxPoints * Size.GetWidth() * i / (double)MaxPoints) / (Size.GetWidth() * Size.GetWidth())) * Size.GetHeight();
			this->Shape.append(sf::Vertex(sf::Vector2f(X, Y), this->FillColor));
		}

		for (i = 0; i <= MaxPoints; i++) {
			Y = this->Origin.GetY();
			X = this->Origin.GetX() + Size.GetWidth() * i / (double)MaxPoints;
			this->Shape.append(sf::Vertex(sf::Vector2f(X, Y), this->FillColor));
		}

		this->VerticalRectangle.setPosition(sf::Vector2f(this->Origin.GetX() + this->Size.GetWidth(), Origin.GetY() - this->Thickness));
		this->HorizontalRectangle.setPosition(sf::Vector2f(this->Origin.GetX(), Origin.GetY() - this->Thickness));
	}
	/* Bottom Left Corner */
	else if (this->Position == Corner::BottomLeft) {
		for (i = 0; i <= MaxPoints; i++) {
			X = this->Origin.GetX() + i * Size.GetWidth() / (double)MaxPoints;
			Y = this->Origin.GetY() + Size.GetHeight();
			this->Shape.append(sf::Vertex(sf::Vector2f(X, Y), this->FillColor));
		}

		for (i = MaxPoints; i >= 0; i--) {
			X = this->Origin.GetX() + Size.GetWidth() * i / (double)MaxPoints;
			Y = this->Origin.GetY() + sqrt(1 - (Size.GetWidth() * (MaxPoints - i) / (double)MaxPoints * Size.GetWidth() * (MaxPoints - i) / (double)MaxPoints) / (Size.GetWidth() * Size.GetWidth())) * Size.GetHeight();
			this->Shape.append(sf::Vertex(sf::Vector2f(X, Y), this->FillColor));
		}

		for (i = 0; i <= MaxPoints; i++) {
			Y = this->Origin.GetY() + Size.GetHeight() * i / (double)MaxPoints;
			X = this->Origin.GetX();
			this->Shape.append(sf::Vertex(sf::Vector2f(X, Y), this->FillColor));
		}

		this->VerticalRectangle.setPosition(sf::Vector2f(Origin.GetX() - this->Thickness, Origin.GetY()));
		this->HorizontalRectangle.setPosition(sf::Vector2f(Origin.GetX() - this->Thickness, Origin.GetY() + Size.GetHeight()));
	}
	/* Bottom Right Corner */
	else if (this->Position == Corner::BottomRight) {
		for (i = 0; i <= MaxPoints; i++) {
			X = this->Origin.GetX() + Size.GetWidth();
			Y = this->Origin.GetY() + Size.GetHeight() - i * Size.GetHeight() / (double)MaxPoints;
			this->Shape.append(sf::Vertex(sf::Vector2f(X, Y), this->FillColor));
		}

		for (i = 0; i <= MaxPoints; i++) {
			X = this->Origin.GetX() + Size.GetWidth() - Size.GetWidth() * i / (double)MaxPoints;
			Y = this->Origin.GetY() + sqrt(1 - (Size.GetWidth() * (MaxPoints - i) / (double)MaxPoints * Size.GetWidth() * (MaxPoints - i) / (double)MaxPoints) / (Size.GetWidth() * Size.GetWidth())) * Size.GetHeight();
			this->Shape.append(sf::Vertex(sf::Vector2f(X, Y), this->FillColor));
		}

		for (i = 0; i <= MaxPoints; i++) {
			Y = this->Origin.GetY() + Size.GetHeight();
			X = this->Origin.GetX() + i * Size.GetWidth() / (double)MaxPoints;
			this->Shape.append(sf::Vertex(sf::Vector2f(X, Y), this->FillColor));
		}

		this->VerticalRectangle.setPosition(sf::Vector2f(Origin.GetX() + Size.GetWidth(), Origin.GetY()));
		this->HorizontalRectangle.setPosition(sf::Vector2f(Origin.GetX(), Origin.GetY() + Size.GetHeight()));
	}

}

CurvilinearTriangle::CurvilinearTriangle() {

}

//--------------------------------------- Draw --------------------------------------//

void CurvilinearTriangle::Draw() {
	GameWindow->draw(this->Shape);
	GameWindow->draw(this->HorizontalRectangle);
	GameWindow->draw(this->VerticalRectangle);
}