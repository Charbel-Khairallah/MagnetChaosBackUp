#pragma once
#include "CurvilinearTriangle.h"
#include "Config.h"

class Bar {
private:
	double InitialValue;
	double CurrentValue;
	double ActualValue;
	double Rate;
	Point Origin;
	Dimension Size;
	double Thickness;
	double CenterOffsetPercentage;

	CurvilinearTriangle FrontTopLeftCover;
	CurvilinearTriangle FrontTopRightCover;
	CurvilinearTriangle FrontBottomLeftCover;
	CurvilinearTriangle FrontBottomRightCover;

	CurvilinearTriangle BackTopLeftCover;
	CurvilinearTriangle BackTopRightCover;
	CurvilinearTriangle BackBottomLeftCover;
	CurvilinearTriangle BackBottomRightCover;

	sf::RectangleShape TopBorderRectangle;
	sf::RectangleShape BottomBorderRectangle;

	sf::RectangleShape BarValue;

	void Clamp();

public:
	Bar();
	Bar(Point Origin, Dimension Size, double CenterOffsetPercentage, double Thickness, double Rate, double InitialValue, sf::Color BackgroundColor);
	~Bar();

	void Draw();
	void Refresh();
	/*void Increment();
	void Decrement();*/
	void SetRate(double NewRate);
	void Reset();

	double GetRate();
	double GetValue();
	sf::Color GetBarColor();

	double GetX();
	double GetY();
	double GetWidth();
	double GetHeight();

	Bar& operator += (const double &Value);
	Bar& operator -= (const double &Value);
	Bar& operator ++();
	Bar& operator --();
};