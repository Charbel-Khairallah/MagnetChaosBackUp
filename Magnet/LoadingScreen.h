#pragma once
#include <SFML/Graphics.hpp>
#include <thread>

#include "Frame.h"
#include "Config.h"
#include "Methods.h"
#include "Video.h"

class LoadingScreen {
private:
	sf::Text Title;

	sf::CircleShape RedCircle;
	sf::CircleShape BlueCircle;

	sf::RectangleShape BlockRectangle;

	bool FadingIn;
	bool FadingOut;
	bool GoingUp;
	bool Finished;
	int Value;
	int Rate;
	int Limit;

	std::vector<Video*> Videos;

	std::thread VideoLoadThread;

	void LoadVideos();

public:
	LoadingScreen();
	~LoadingScreen();

	void Draw();
	void Refresh();

	bool HasFinished();

	std::vector<Video*> GetLoadedVideos();
};