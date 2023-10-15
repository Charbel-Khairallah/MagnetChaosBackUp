#pragma once
#include "UserInput.h"

//------------------------------------ Constructors -----------------------------------//

UserInput::UserInput(int KeyCode, int KeyType, int Index, bool FireOnPress) {
	this->KeyCode = KeyCode;
	this->KeyType = KeyType;
	this->Index = Index;

	this->FireOnPress = FireOnPress;

	this->Active = false;
	this->Pressed = false;
}

UserInput::UserInput(std::string Input, bool FireOnPress) {
	std::vector<std::string> Values = MT::Split(Input, {':', ';'});

	this->KeyType = std::stoi(Values[0]);
	this->KeyCode = std::stoi(Values[1]);
	this->Index = std::stoi(Values[2]);

	this->FireOnPress = FireOnPress;

	this->Active = false;
	this->Pressed = false;
}


UserInput::UserInput() {}

//------------------------------------- Destructor ------------------------------------//

UserInput::~UserInput() {
	
}

//--------------------------------------- ToString ------------------------------------//

std::string UserInput::ToString() const {
	return std::to_string(this->KeyType) + ":" + std::to_string(this->KeyCode) + ";" + std::to_string(this->Index);
}

//-------------------------------------- == Operator ----------------------------------//

bool UserInput::operator == (const UserInput &Other) {
	return this->ToString() == Other.ToString();
}

//--------------------------------------- Is Active -----------------------------------//

bool UserInput::IsActive() {
	return this->Active;
}

//--------------------------------------- Check State -----------------------------------//

void UserInput::CheckState() {
	sf::Mouse::Button CurrentButton;
	bool Continue = false;
	switch (this->Index)
	{
		case -1: {
			if (this->FireOnPress) {
				this->Active = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(this->KeyCode));
			}
			else {
				this->Active = this->Pressed && !sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(this->KeyCode));
				this->Pressed = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(this->KeyCode));
			}
			break;
		}
		case 0: {
			CurrentButton = sf::Mouse::Left;
			Continue = true;
			break;
		}
		case 1: {
			CurrentButton = sf::Mouse::Right;
			Continue = true;
			break;
		}
		case 2: {
			CurrentButton = sf::Mouse::Middle;
			Continue = true;
			break;
		}
	}
	if (Continue) {
		if (this->FireOnPress) {
			this->Active = sf::Mouse::isButtonPressed(CurrentButton);
		}
		else {
			this->Active = this->Pressed && !sf::Mouse::isButtonPressed(CurrentButton);
			this->Pressed = sf::Mouse::isButtonPressed(CurrentButton);
		}
	}
}
