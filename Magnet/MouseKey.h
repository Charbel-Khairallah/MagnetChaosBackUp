#pragma once
#include <SFML/Graphics.hpp>
#include "Key.h"
#include "Dimension.h"
#include "Point.h"

class MouseKey : public Key {
private:
	int SelectedIndex;

	sf::Texture MouseTexture;
	sf::Image MouseImage;
	sf::Image ResizedMouseImage;
	sf::RectangleShape Mouse;

	sf::Image MouseSelectionImage;
	sf::Image ResizedMouseSelectionImage;

	sf::Image LeftClickImage;
	sf::Image ResizedLeftClickImage;
	sf::Image RightClickImage;
	sf::Image ResizedRightClickImage;
	sf::Image MiddleClickImage;
	sf::Image ResizedMiddleClickImage;

	sf::VertexArray LeftClickCurve;
	sf::VertexArray RightClickCurve;
	sf::VertexArray MiddleClickCurve;

	std::vector<std::vector<sf::RectangleShape>> Pixels;


public:

	MouseKey(Point Origin, Dimension Size, int KeyType, int KeyCode);
	~MouseKey();

	void Select(int Index);
	void UnSelect();
	void Refresh();

	double GetX();
	double GetY();
	double GetWidth();
	double GetHeight();

	std::string GetValue();

	void Draw();
};