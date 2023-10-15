#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime> 

#include "Point.h"
#include "Angle.h"
#include "Frame.h"

namespace MT {
	sf::Color Mix(sf::Color First, sf::Color Second, double Factor);	// Instant Mix
	sf::Color Shift(sf::Color First, sf::Color Second, double Factor);	// Slow Mix
	double Shift(double Start, double End, double Factor);
	Point Shift(Point Start, Point End, double Factor);
	Point MidPoint(Point First, Point Second);
	Point GetProjection(Point MainPoint, Point FirstLineEdge, Point SecondLineEdge);
	long RoundUp(double Value);
	long RoundDown(double Value);
	long Round(double value);

	bool MouseOverText(sf::Text & Label);
	bool AlmostEqual(sf::Color First, sf::Color Second);

	template<typename Any> Any AbsoluteValue(Any);
	template<typename Any> Any Max(Any, Any);
	template<typename Any> Any Min(Any, Any);
	template<typename Any> bool ElementInVector(std::vector<Any>, Any);

	void ResizeImage(const sf::Image& originalImage, sf::Image& resizedImage);

	sf::VertexArray ImageToCurve(const sf::Image& GivenImage, Point Shift);

	std::string Text(long Number, int Digits);
	std::string ShortRoman(short Number);

	std::vector<std::string> Split(std::string, char Separator);
	std::vector<std::string> Split(std::string, std::vector<char> Separators);

	int GenerateRandomInteger(int Start, int End);
	void GenerateRandomState(Dimension ObjectSize, double& X, double& Y, Angle& Rotation);

	long long GenerateUniqueID();
}

/*
 * I Had To Define The Function Here In The Header File In Order To Be Able To Call It From Other Files
 * Else, I Would Get Linker Errors
 */

//---------------------------------------- Max -----------------------------------------//

template<typename Any>
Any MT::Max(Any First, Any Second) {
	if (First >= Second)return First;
	return Second;
}

//---------------------------------------- Min -----------------------------------------//

template<typename Any>
Any MT::Min(Any First, Any Second) {
	if (First <= Second)return First;
	return Second;
}