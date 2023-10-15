#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Frame.h"

class Key {
protected:
	static Key* SelectedKey;

	bool Selected;
	bool MouseOver;
	bool MousePressed;

	int KeyType;
	int KeyCode;

	sf::Color MainColor;
	sf::Color SecondaryColor;

	sf::Color FirstEdgeColor;
	sf::Color SecondEdgeColor;
	sf::Color ThirdEdgeColor;
	
public:
	Key(int KeyType, int KeyCode);
	virtual ~Key();
	std::string GetID();

	virtual void Select(int Index) = NULL;
	virtual void UnSelect() = NULL;
	virtual void Refresh() = NULL;
	virtual void Draw() = NULL;

	virtual double GetX() = NULL;
	virtual double GetY() = NULL;
	virtual double GetWidth() = NULL;
	virtual double GetHeight() = NULL;

	virtual std::string GetValue() = NULL;
};