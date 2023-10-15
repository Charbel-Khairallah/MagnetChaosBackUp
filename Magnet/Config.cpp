#pragma once
#include "Config.h"

//------------------------------------ Constructor ------------------------------------//

Config::Config() {

}

//------------------------------------ GetSingleton -----------------------------------//

Config & Config::Instance(){
	static Config Configuration;
	return Configuration;
}

//---------------------------------------- Init ----------------------------------------//

void Config::Init() {
	if (!this->TextFont.loadFromFile("../GameData/Fonts/sansation.ttf")) {
		std::cout << "Cannot Load Font." << std::endl;
	}
	else std::cout << "Font Loaded Successfully." << std::endl;

	if (!this->IronTexture.loadFromFile("../GameData/Images/Metal.jpg")) {
		std::cout << "Could Not Load Texture." << std::endl;
	}
	else {
		std::cout << "Iron Texture Loaded Successfully." << std::endl;
	}

	if (!this->CopperTexture.loadFromFile("../GameData/Images/Copper.jpg")) {
		std::cout << "Could Not Load Texture." << std::endl;
	}
	else {
		std::cout << "Iron Texture Loaded Successfully." << std::endl;
	}

	if (!this->BotTexture.loadFromFile("../GameData/Images/Robot.png")) {
		std::cout << "Could Not Load Bot Texture." << std::endl;
	}
	else {
		std::cout << "Bot Texture Loaded Successfully." << std::endl;
	}

	if (!this->BotHealthTexture100.loadFromFile("../GameData/Images/RobotHealth100.png")) {
		std::cout << "Could Not Load Health Texture." << std::endl;
	}
	else {
		std::cout << "Health Texture Loaded Successfully." << std::endl;
	}

	if (!this->BotHealthTexture075.loadFromFile("../GameData/Images/RobotHealth075.png")) {
		std::cout << "Could Not Load Health Texture." << std::endl;
	}
	else {
		std::cout << "Health Texture Loaded Successfully." << std::endl;
	}

	if (!this->BotHealthTexture050.loadFromFile("../GameData/Images/RobotHealth050.png")) {
		std::cout << "Could Not Load Health Texture." << std::endl;
	}
	else {
		std::cout << "Health Texture Loaded Successfully." << std::endl;
	}

	if (!this->BotHealthTexture025.loadFromFile("../GameData/Images/RobotHealth025.png")) {
		std::cout << "Could Not Load Health Texture." << std::endl;
	}
	else {
		std::cout << "Health Texture Loaded Successfully." << std::endl;
	}

	if (!this->BotHealthTexture000.loadFromFile("../GameData/Images/RobotHealth000.png")) {
		std::cout << "Could Not Load Health Texture." << std::endl;
	}
	else {
		std::cout << "Health Texture Loaded Successfully." << std::endl;
	}

	this->TextColor = sf::Color(255, 255, 255, 255);
	this->TextHoverColor = sf::Color(0, 255, 0, 255);
	this->TextPressedColor = sf::Color(0, 0, 255, 255);

	this->Background = sf::Color(0, 0, 0, 255);
	this->SecondaryBackground = sf::Color(10, 10, 10, 255);

	this->Transparent = sf::Color(0, 0, 0, 0);
	this->Error = sf::Color(255, 0, 0, 255);
	this->Field = sf::Color(0, 255, 255, 20);
	this->Warning = sf::Color(255, 255, 0, 255);
	this->TextDisabledColor = sf::Color(100, 100, 100, 255);
	this->TextDisabledFill = sf::Color(0, 0, 0, 60);
	
	this->Hand.loadFromSystem(sf::Cursor::Hand);
	this->Arrow.loadFromSystem(sf::Cursor::Arrow);

	this->HeaderCharacterSize = 50;
	this->SubHeaderCharacterSize = 36;
	this->NormalCharacterSize = 20;
	this->SmallCharacterSize = 15;

	this->SlowTransitionSpeed = 30;
	this->NormalTransitionSpeed = 20;
	this->FastTransitionSpeed = 10;
}


//----------------------------------------- GetFont ---------------------------------------//

sf::Font & Config::Font() {
	return Instance().TextFont;
}

//----------------------------------------- GetColor --------------------------------------//

sf::Color Config::Color() {
	return Instance().TextColor;
}

//-------------------------------------- GetHoverColor ------------------------------------//

sf::Color Config::HoverColor() {
	return Instance().TextHoverColor;
}

//------------------------------------- GetPressedColor -----------------------------------//

sf::Color Config::PressedColor() {
	return Instance().TextPressedColor;
}

//-------------------------------------- GetErrorColor ------------------------------------//

sf::Color Config::ErrorColor() {
	return Instance().Error;
}

//-------------------------------------- GetFieldColor ------------------------------------//

sf::Color Config::FieldColor() {
	return Instance().Field;
}

//------------------------------------- GetWarningColor -----------------------------------//

sf::Color Config::WarningColor() {
	return Instance().Warning;
}


//----------------------------------- GetTransparentColor ---------------------------------//

sf::Color Config::TransparentColor() {
	return Instance().Transparent;
}

//------------------------------------ GetBackgroundColor ---------------------------------//

sf::Color Config::BackgroundColor() {
	return Instance().Background;
}

//-------------------------------- GetSecondaryBackgroundColor ----------------------------//

sf::Color Config::SecondaryBackgroundColor() {
	return Instance().SecondaryBackground;
}


//-------------------------------------- GetHandCursor ------------------------------------//

sf::Cursor & Config::GetHand() {
	return Instance().Hand;
}

//------------------------------------- GetArrowCursor ------------------------------------//

sf::Cursor& Config::GetArrow() {
	return Instance().Arrow;
}

//------------------------------------------- H1 ------------------------------------------//

int Config::GetHeaderCharacterSize() {
	return Instance().HeaderCharacterSize;
}

//------------------------------------------- H2 ------------------------------------------//

int Config::GetSubHeaderCharacterSize() {
	return Instance().SubHeaderCharacterSize;
}

//------------------------------------------- H3 ------------------------------------------//

int Config::GetNormalCharacterSize() {
	return Instance().NormalCharacterSize;
}

//------------------------------------------- H4 ------------------------------------------//

int Config::GetSmallCharacterSize() {
	return Instance().SmallCharacterSize;
}

//-------------------------------- Get Fast Transition Speed ------------------------------//

int Config::GetFastTransitionSpeed() {
	return Instance().FastTransitionSpeed;
}

//------------------------------- Get Normal Transition Speed -----------------------------//

int Config::GetNormalTransitionSpeed() {
	return Instance().NormalTransitionSpeed;
}

//-------------------------------- Get Slow Transition Speed ------------------------------//

int Config::GetSlowTransitionSpeed() {
	return Instance().SlowTransitionSpeed;
}

//----------------------------------- Get Disabled Color ---------------------------------//

sf::Color Config::DisabledColor() {
	return Instance().TextDisabledColor;
}

//----------------------------------- Get Disabled Fill ----------------------------------//

sf::Color Config::DisabledFill() {
	return Instance().TextDisabledFill;
}

//----------------------------------- Get Iron Texture -----------------------------------//

sf::Texture & Config::GetIronTexture() {
	return Instance().IronTexture;
}

//---------------------------------- Get Copper Texture ----------------------------------//

sf::Texture & Config::GetCopperTexture() {
	return Instance().CopperTexture;
}

//----------------------------------- Get Bot Texture ------------------------------------//

sf::Texture & Config::GetBotTexture() {
	return Instance().BotTexture;
}

//------------------------------- Get Health Texture 100% --------------------------------//

sf::Texture& Config::GetHealthTexture100() {
	return Instance().BotHealthTexture100;
}

//-------------------------------- Get Health Texture 75% --------------------------------//

sf::Texture & Config::GetHealthTexture075() {
	return Instance().BotHealthTexture075;
}

//-------------------------------- Get Health Texture 50% --------------------------------//

sf::Texture & Config::GetHealthTexture050() {
	return Instance().BotHealthTexture050;
}

//-------------------------------- Get Health Texture 25% --------------------------------//

sf::Texture & Config::GetHealthTexture025() {
	return Instance().BotHealthTexture025;
}

//-------------------------------- Get Health Texture 00% --------------------------------//

sf::Texture & Config::GetHealthTexture000() {
	return Instance().BotHealthTexture000;
}