#pragma once
#include "Key.h"

Key * Key::SelectedKey = NULL;

//------------------------------------------- Contructor -------------------------------------------//

Key::Key(int KeyType, int KeyCode) {
	this->Selected = false;
	this->MouseOver = false;
	this->MousePressed = false;
	this->KeyType = KeyType;
	this->KeyCode = KeyCode;

	this->MainColor = sf::Color(50, 50, 50, 255);
	this->SecondaryColor = sf::Color(60, 60, 60, 255);

	this->FirstEdgeColor = sf::Color(40, 40, 40, 255);
	this->SecondEdgeColor = sf::Color(30, 30, 30, 255);
	this->ThirdEdgeColor = sf::Color(20, 20, 20, 255);
}

//------------------------------------------- Destructor -------------------------------------------//

Key::~Key() {
	Key::SelectedKey = NULL;
}


//--------------------------------------------- Get ID ----------------------------------------------//

std::string Key::GetID() {
	std::string ID = "";

	ID += std::to_string(this->KeyType);
	ID += ":";
	ID += std::to_string(this->KeyCode);

	return ID;
}