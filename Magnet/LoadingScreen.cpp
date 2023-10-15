#pragma once
#include "LoadingScreen.h"

//--------------------------------------- Constructor -----------------------------------//

LoadingScreen::LoadingScreen() {
	this->VideoLoadThread = std::thread([this]() {this->LoadVideos(); });

	double X, Y, Width, Height;
	this->FadingIn = true;
	this->FadingOut = false;
	this->GoingUp = true;
	this->Finished = false;
	this->Value = 0;
	this->Rate = 1;
	this->Limit = 100;

	/* Title */
	this->Title = sf::Text("MAGNET CHAOS", FONT, H1 * 1.4);
	this->Title.setFillColor(COLOR);
	Width = this->Title.getGlobalBounds().width;
	Height = this->Title.getGlobalBounds().height;
	X = (GameWindow->getSize().x - Width) / 2.0;
	Y = (GameWindow->getSize().y - Height) / 3.0;
	this->Title.setPosition(X, Y);

	/* Red Circle */
	this->RedCircle = sf::CircleShape(GameWindow->getSize().x * 0.02);
	Width = Height = this->RedCircle.getRadius();
	X = (GameWindow->getSize().x - Width * 2) / 3;
	Y = GameWindow->getSize().y - Height - Y;
	this->RedCircle.setPosition(X, Y);
	this->RedCircle.setFillColor(TRANSPARENT);

	/* Blue Circle */
	this->BlueCircle = sf::CircleShape(GameWindow->getSize().x * 0.02);
	Width = Height = this->BlueCircle.getRadius();
	X = GameWindow->getSize().x - Width - X;
	Y = Y;
	this->BlueCircle.setPosition(X, Y);
	this->BlueCircle.setFillColor(PRESSED_COLOR);

	/* Block Rectangle */
	Width = GameWindow->getSize().x;
	Height = GameWindow->getSize().y;
	this->BlockRectangle = sf::RectangleShape(sf::Vector2f(Width, Height));
	this->BlockRectangle.setPosition(0, 0);
	this->BlockRectangle.setFillColor(BACKGROUND);
}

//-------------------------------------- Destructor ------------------------------------//

LoadingScreen::~LoadingScreen() {
	
}

//----------------------------------------- Draw ---------------------------------------//

void LoadingScreen::Draw() {
	GameWindow->draw(this->Title);
	GameWindow->draw(this->RedCircle);
	GameWindow->draw(this->BlueCircle);
	GameWindow->draw(this->BlockRectangle);
}

//--------------------------------------- Refresh --------------------------------------//

void LoadingScreen::Refresh() {
	int i = 0;
	for (i = 0; i < this->Videos.size(); i++) {
		if (this->Videos[i]->IsReady() == false)break;
	}
	if (i == this->Videos.size()) {
		if (this->VideoLoadThread.joinable())this->VideoLoadThread.join();
		this->FadingOut = true;
	}

	if (this->FadingIn) {
		this->BlockRectangle.setFillColor(MT::Shift(this->BlockRectangle.getFillColor(), TRANSPARENT, SLOW));
		if (this->BlockRectangle.getFillColor() == TRANSPARENT) {
			this->FadingIn = false;
		}
	}
	else if (this->FadingOut) {
		this->BlockRectangle.setFillColor(MT::Shift(this->BlockRectangle.getFillColor(), BACKGROUND, SLOW));
		if (this->BlockRectangle.getFillColor() == BACKGROUND) {
			this->Finished = true;
		}
	}
	else {
		this->RedCircle.setFillColor(MT::Mix(ERROR_COLOR, TRANSPARENT, this->Value / (double)this->Limit));
		this->BlueCircle.setFillColor(MT::Mix(PRESSED_COLOR, TRANSPARENT, (this->Limit - this->Value) / (double)this->Limit));
		
		if (this->GoingUp) {
			this->Value += this->Rate;
			if (this->Value == this->Limit)this->GoingUp = false;
		}
		else {
			this->Value -= this->Rate;
			if (this->Value == 0)this->GoingUp = true;
		}
	}
}

//----------------------------------- Get Loaded Videos ----------------------------------//

std::vector<Video*> LoadingScreen::GetLoadedVideos() {
	return this->Videos;
}

//-------------------------------------- Load Videos -------------------------------------//

void LoadingScreen::LoadVideos() {
	this->Videos.push_back(new Video(1, 334, "../GameData/Videos/0/"));
	this->Videos.push_back(new Video(1, 589, "../GameData/Videos/1/"));
	this->Videos.push_back(new Video(1, 524, "../GameData/Videos/2/"));
	this->Videos.push_back(new Video(1, 241, "../GameData/Videos/3/"));
	this->Videos.push_back(new Video(1, 379, "../GameData/Videos/4/"));
	int Branches = MT::Max<int>(std::thread::hardware_concurrency() - 1, 1);
	for (int i = 0; i < this->Videos.size(); i++) {
		this->Videos[i]->LoadInParallel(Branches);
	}
}

//-------------------------------------- Has Finished ------------------------------------//

bool LoadingScreen::HasFinished() {
	return this->Finished;
}