#pragma once
#include <chrono>
#include <random>

#include "Methods.h"
#include "Rectangle.h"

//--------------------------------------- Round Up ---------------------------------------//

long MT::RoundUp(double Value) {
	if(Value >= 0)return (long)Value + (AbsoluteValue((Value - (long)Value)) > 0);
	return(long)Value - (AbsoluteValue((Value - (long)Value)) > 0);
}

//-------------------------------------- Round Down --------------------------------------//

long MT::RoundDown(double Value) {
	if (Value >= 0)return (long)Value;
	return(long)Value - (AbsoluteValue((Value - (long)Value)) > 0);
}

//----------------------------------------- Round ----------------------------------------//

long MT::Round(double Value) {
	double FloatingValue = Value - (int)Value;
	return Value + (FloatingValue >= 0.5);
}

//-------------------------------------- Mix Color --------------------------------------//

sf::Color MT::Mix(sf::Color First, sf::Color Second, double Factor) {
	if (Factor > 1) Factor = 1;
	if (Factor < 0) Factor = 0;

	double Red, Green, Blue, Alpha;
	Red = First.r * Factor + Second.r * (1 - Factor);
	Green = First.g * Factor + Second.g * (1 - Factor);
	Blue = First.b * Factor + Second.b * (1 - Factor);
	Alpha = First.a * Factor + Second.a * (1 - Factor);

	return sf::Color(Red, Green, Blue, Alpha);
}

//-------------------------------------- Shfit Color --------------------------------------//

sf::Color MT::Shift(sf::Color First, sf::Color Second, double Factor) {
	if (First.r != Second.r) {
		if (First.r > Second.r)First.r -= RoundUp((First.r - Second.r) / (double)Factor);
		else First.r += RoundUp((Second.r - First.r) / (double)Factor);
	}
	if (First.g != Second.g) {
		if (First.g > Second.g)First.g -= RoundUp((First.g - Second.g) / (double)Factor);
		else First.g += RoundUp((Second.g - First.g) / (double)Factor);
	}
	if (First.b != Second.b) {
		if (First.b > Second.b)First.b -= RoundUp((First.b - Second.b) / (double)Factor);
		else First.b += RoundUp((Second.b - First.b) / (double)Factor);
	}
	if (First.a != Second.a) {
		if (First.a > Second.a)First.a -= RoundUp((First.a - Second.a) / (double)Factor);
		else First.a += RoundUp((Second.a - First.a) / (double)Factor);
	}
	return First;
}

//-------------------------------------- Shift Value --------------------------------------//

double MT::Shift(double Start, double End, double Factor) {
	return (Start * Factor + End) / (double)(Factor + 1);
}

//-------------------------------------- Shift Point --------------------------------------//

Point MT::Shift(Point Start, Point End, double Factor) {
	double X = Shift(Start.GetX(), End.GetX(), Factor);
	double Y = Shift(Start.GetY(), End.GetY(), Factor);
	return Point(X, Y);
}


//----------------------------------- Mouse Over Label -----------------------------------//

bool MT::MouseOverText(sf::Text & Label) {
	Point TopLeftCorner = Point(Label.getGlobalBounds().left, Label.getGlobalBounds().top);
	Point BottomRightCorner = TopLeftCorner + Dimension(Label.getGlobalBounds().width, Label.getGlobalBounds().height);
	Shape * LabelBoundaries = new Rectangle(TopLeftCorner, BottomRightCorner);
	bool Result = LabelBoundaries->ContainsPoint(Point(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
	delete LabelBoundaries;
	return Result;
}

//----------------------------------- Absolute Value -----------------------------------//

template<typename Any> 
Any MT::AbsoluteValue(Any Value) {
	if (Value >= 0)return Value;
	return -Value;
}

//--------------------------------- Element In Vector ----------------------------------//

template<typename Any> 
bool MT::ElementInVector(std::vector<Any> Elements, Any Element) {
	for (int i = 0; i < Elements.size(); i++) {
		if (Elements[i] == Element)return true;
	}
	return false;
}
/*
//---------------------------------------- Max -----------------------------------------//

template<typename Any>
Any MT::Max(Any First, Any Second) {
	if (First >= Second)return First;
	return Second;
}
*/
//------------------------------------ Almost Equal ------------------------------------//

bool MT::AlmostEqual(sf::Color First, sf::Color Second) {
	int Difference = 0;
	Difference = MT::Max<double>(Difference, MT::AbsoluteValue<double>(First.r - Second.r));
	Difference = MT::Max<double>(Difference, MT::AbsoluteValue<double>(First.g - Second.g));
	Difference = MT::Max<double>(Difference, MT::AbsoluteValue<double>(First.b - Second.b));
	Difference = MT::Max<double>(Difference, MT::AbsoluteValue<double>(First.a - Second.a));
	return Difference <= 1;
}


//------------------------------------ Resize Image ------------------------------------//


void MT::ResizeImage(const sf::Image& OriginalImage, sf::Image& ResizedImage)
{
	const sf::Vector2u OriginalImageSize{ OriginalImage.getSize() };
	const sf::Vector2u ResizedImageSize{ ResizedImage.getSize() };
	for (int y = 0; y < ResizedImageSize.y; y++)
	{
		for (int x = 0; x < ResizedImageSize.x; x++)
		{
			unsigned int OrigX{ static_cast<unsigned int>(static_cast<double>(x) / ResizedImageSize.x * OriginalImageSize.x) };
			unsigned int OrigY{ static_cast<unsigned int>(static_cast<double>(y) / ResizedImageSize.y * OriginalImageSize.y) };
			ResizedImage.setPixel(x, y, OriginalImage.getPixel(OrigX, OrigY));
		}
	}
}

//------------------------------------ Image To Curve ------------------------------------//

sf::VertexArray MT::ImageToCurve(const sf::Image& GivenImage, Point Shift) {

	sf::VertexArray Curve(sf::PrimitiveType::Points);

	for (int x = 0; x < GivenImage.getSize().x; x++) {
		for (int y = 0; y < GivenImage.getSize().y; y++) {
			if (GivenImage.getPixel(x, y) != sf::Color::Transparent) {
				Curve.append(sf::Vertex(sf::Vector2f(x + Shift.GetX(), y + Shift.GetY()), sf::Color::Transparent));
			}
		}
	}
	
	return Curve;
}

//----------------------------------------- Split ----------------------------------------//

std::vector<std::string> MT::Split(std::string String, char Separator) {
	std::vector<std::string> Result;
	std::string CurrentString = "";
	for (int i = 0; i < String.length(); i++) {
		if (String[i] == Separator) {
			Result.push_back(CurrentString);
			CurrentString = "";
		}
		else {
			CurrentString += String[i];
		}
	}
	Result.push_back(CurrentString);
	return Result;
}

//-------------------------------- Split On Multiple Chars -------------------------------//

std::vector<std::string> MT::Split(std::string String, std::vector<char> Separators) {
	std::vector<std::string> Result;
	std::string CurrentString = "";
	for (int i = 0; i < String.length(); i++) {
		if (MT::ElementInVector<char>(Separators, String[i])) {
			Result.push_back(CurrentString);
			CurrentString = "";
		}
		else {
			CurrentString += String[i];
		}
	}
	Result.push_back(CurrentString);
	return Result;
}

//------------------------------------------ Text -----------------------------------------//

std::string MT::Text(long Number, int Digits) {
	bool Negative = Number < 0;
	if (Negative)Number = -Number;
	std::string Result = std::to_string(Number);
	while (Result.length() < Digits) {
		Result = "0" + Result;
	}
	if (Negative)return ("-" + Result);
	return Result;
}

//--------------------------------------- Short Roman --------------------------------------//

std::string MT::ShortRoman(short Number) {
	switch (Number)
	{
		case 1: {
			return "I";
		}
		case 2: {
			return "II";
		}
		case 3: {
			return "III";
		}
		case 4: {
			return "IV";
		}
		case 5: {
			return "V";
		}
	}
	return "";
}

//-------------------------------------- Random Integer -------------------------------------//

int MT::GenerateRandomInteger(int Start, int End) {
	if (Start > End) {
		int Temp = Start;
		Start = End;
		End = Temp;
	}
	return std::rand() % (End - Start + 1) + Start;
}

//-------------------------------------- Get Unique ID -------------------------------------//

long long MT::GenerateUniqueID() {
	std::chrono::system_clock::time_point TimeNow = std::chrono::system_clock::now();
	std::chrono::system_clock::duration Duration = TimeNow.time_since_epoch();
	long long MilliSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(Duration).count();

	std::default_random_engine Generator(static_cast<unsigned int>(MilliSeconds));
	std::uniform_int_distribution<int> Distribution(1, 1000000);
	int Random = Distribution(Generator);

	long long UniqueID = MilliSeconds * 1000000 + Random;

	return UniqueID;
}

//----------------------------------- Generate Random State ----------------------------------//

void MT::GenerateRandomState(Dimension ObjectSize, double& X, double& Y, Angle& Rotation) {
	/*
		0   1
		-----
	  7 |   | 2
	  6 |   | 3
		-----
		5   4
	*/

	int Shift = 20;

	double ScreenWidth = GameWindow->getSize().x;
	double ScreenHeight = GameWindow->getSize().y;

	int Random = MT::GenerateRandomInteger(0, 7);
	switch (Random)
	{
		case 0: {
			X = MT::GenerateRandomInteger(0, ScreenWidth / 2);
			Y = -ObjectSize.GetHeight();
			Rotation = Angle(MT::GenerateRandomInteger(0 + Shift, 90 - Shift));
			break;
		}
		case 1: {
			X = MT::GenerateRandomInteger(ScreenWidth / 2, ScreenWidth);
			Y = -ObjectSize.GetHeight();
			Rotation = Angle(MT::GenerateRandomInteger(90 + Shift, 180 - Shift));
			break;
		}
		case 2: {
			X = ScreenWidth + ObjectSize.GetWidth();
			Y = MT::GenerateRandomInteger(0, ScreenHeight / 2);
			Rotation = Angle(MT::GenerateRandomInteger(90 + Shift, 180 - Shift));
			break;
		}
		case 3: {
			X = ScreenWidth + ObjectSize.GetWidth();
			Y = MT::GenerateRandomInteger(ScreenHeight / 2, ScreenHeight);
			Rotation = Angle(MT::GenerateRandomInteger(180 + Shift, 270 - Shift));
			break;
		}
		case 4: {
			X = MT::GenerateRandomInteger(ScreenWidth / 2, ScreenWidth);
			Y = ScreenHeight + ObjectSize.GetHeight();
			Rotation = Angle(MT::GenerateRandomInteger(180 + Shift, 270 - Shift));
			break;
		}
		case 5: {
			X = MT::GenerateRandomInteger(0, ScreenWidth / 2);
			Y = ScreenHeight + ObjectSize.GetHeight();
			Rotation = Angle(MT::GenerateRandomInteger(270 + Shift, 360 - Shift));
			break;
		}
		case 6: {
			X = -ObjectSize.GetWidth();
			Y = MT::GenerateRandomInteger(ScreenHeight / 2, ScreenHeight);
			Rotation = Angle(MT::GenerateRandomInteger(270 + Shift, 360 - Shift));
			break;
		}
		case 7: {
			X = -ObjectSize.GetWidth();
			Y = MT::GenerateRandomInteger(0, ScreenHeight / 2);
			Rotation = Angle(MT::GenerateRandomInteger(0 + Shift, 90 - Shift));
			break;
		}
	}

}

//-------------------------------------- Mid Point -------------------------------------//

Point MT::MidPoint(Point First, Point Second) {
	return Point((First.GetX() + Second.GetX()) / 2.0, (First.GetY() + Second.GetY()) / 2.0);
}

//----------------------------------- Get Projection -----------------------------------//

Point MT::GetProjection(Point MainPoint, Point FirstLineEdge, Point SecondLineEdge) {
	if (FirstLineEdge.GetX() == SecondLineEdge.GetX() || FirstLineEdge.GetY() == SecondLineEdge.GetY()) {
		if (FirstLineEdge.GetX() != SecondLineEdge.GetX()) {
			return Point(MainPoint.GetX(), FirstLineEdge.GetY());
		}
		else {
			if (FirstLineEdge.GetY() != SecondLineEdge.GetY()) {
				return Point(FirstLineEdge.GetX(), MainPoint.GetY());
			}
			else {
				return Point(0, 0);
			}
		}
	}
	else {
		/*
		* P2 = P1 * X1 + Y1
		* P2 = P1 * X2 + Y2
		*/

		double X1 = (SecondLineEdge.GetY() - FirstLineEdge.GetY()) / (double)(SecondLineEdge.GetX() - FirstLineEdge.GetX());
		double Y1 = FirstLineEdge.GetY() - X1 * FirstLineEdge.GetX();

		double X2 = (FirstLineEdge.GetX() - SecondLineEdge.GetX()) / (double)(SecondLineEdge.GetY() - FirstLineEdge.GetY());
		double Y2 = FirstLineEdge.GetY() - X2 * FirstLineEdge.GetX();

		double P1 = (Y2 - Y1) / (double)(X1 - X2);
		double P2 = P1 * X1 + Y1;

		return Point(P1, P2);
	}

}
