#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#define FONT Config::Font()
#define COLOR Config::Color()
#define HOVER_COLOR Config::HoverColor()
#define PRESSED_COLOR Config::PressedColor()
#define ERROR_COLOR Config::ErrorColor()
#define FIELD_COLOR Config::FieldColor()
#define WARNING_COLOR Config::WarningColor()
#define TRANSPARENT Config::TransparentColor()
#define BACKGROUND Config::BackgroundColor()
#define SECONDARY_BACKGROUND Config::SecondaryBackgroundColor()
#define DISABLED_COLOR Config::DisabledColor()
#define DISABLED_FILL Config::DisabledFill()

#define IRON Config::GetIronTexture()
#define COPPER Config::GetCopperTexture()
#define BOT Config::GetBotTexture()
#define H100 Config::GetHealthTexture100()
#define H075 Config::GetHealthTexture075()
#define H050 Config::GetHealthTexture050()
#define H025 Config::GetHealthTexture025()
#define H000 Config::GetHealthTexture000()

#define HAND Config::GetHand()
#define ARROW Config::GetArrow()

#define H1 Config::GetHeaderCharacterSize()
#define H2 Config::GetSubHeaderCharacterSize()
#define H3 Config::GetNormalCharacterSize()
#define H4 Config::GetSmallCharacterSize()

#define SLOW Config::GetSlowTransitionSpeed()
#define NORMAL Config::GetNormalTransitionSpeed()
#define FAST Config::GetFastTransitionSpeed()

#define PI 3.1415926535

#define MUTE 0
#define LOW 10
#define MID 20
#define HIGH 40
#define LOUD 100

class Config {
private:
	sf::Texture IronTexture;
	sf::Texture CopperTexture;
	sf::Texture BotTexture;
	sf::Texture BotHealthTexture100;
	sf::Texture BotHealthTexture075;
	sf::Texture BotHealthTexture050;
	sf::Texture BotHealthTexture025;
	sf::Texture BotHealthTexture000;

	sf::Font TextFont;
	sf::Color TextColor;
	sf::Color TextHoverColor;
	sf::Color TextPressedColor;
	sf::Color Field;
	sf::Color Error;
	sf::Color Warning;
	sf::Color Transparent;
	sf::Color Background;
	sf::Color SecondaryBackground;

	sf::Color TextDisabledColor;
	sf::Color TextDisabledFill;

	sf::Cursor Hand;
	sf::Cursor Arrow;
	int HeaderCharacterSize;
	int SubHeaderCharacterSize;
	int NormalCharacterSize;
	int SmallCharacterSize;

	int FastTransitionSpeed;
	int NormalTransitionSpeed;
	int SlowTransitionSpeed;

	Config();

public:

	static Config & Instance();
	Config(const Config &) = delete;
	Config& operator = (const Config&) = delete;

	void Init();

	static sf::Font& Font();
	static sf::Color Color();
	static sf::Color HoverColor();
	static sf::Color PressedColor();
	static sf::Color FieldColor();
	static sf::Color ErrorColor();
	static sf::Color WarningColor();
	static sf::Color TransparentColor();
	static sf::Color BackgroundColor();
	static sf::Color SecondaryBackgroundColor();

	static sf::Color DisabledColor();
	static sf::Color DisabledFill();

	static sf::Cursor & GetHand();
	static sf::Cursor & GetArrow();

	static sf::Texture & GetIronTexture();
	static sf::Texture & GetCopperTexture();
	static sf::Texture & GetBotTexture();
	static sf::Texture & GetHealthTexture100();
	static sf::Texture & GetHealthTexture075();
	static sf::Texture & GetHealthTexture050();
	static sf::Texture & GetHealthTexture025();
	static sf::Texture & GetHealthTexture000();

	static int GetHeaderCharacterSize();
	static int GetSubHeaderCharacterSize();
	static int GetNormalCharacterSize();
	static int GetSmallCharacterSize();

	static int GetFastTransitionSpeed();
	static int GetNormalTransitionSpeed();
	static int GetSlowTransitionSpeed();
};
