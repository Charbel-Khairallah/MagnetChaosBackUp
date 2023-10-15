#pragma once
#include "Video.h"

//--------------------------------------- Constructor ------------------------------------//

Video::Video(int Start, int End, std::string Path, bool Repeate) {
	this->Repeate = Repeate;
	this->Start = Start;
	this->End = End;
	this->Path = Path;

	this->Prefix = "Image";
	this->Format = ".png";
	this->Digits = 5;
	this->Ready = false;
	this->FrameIndex = 0;
	this->GapBetweenFrames = 20; // 20 MS

	this->VideoFrame.setOutlineThickness(3);
	this->VideoFrame.setOutlineColor(SECONDARY_BACKGROUND);
}

//---------------------------------------- Destructor ------------------------------------//

Video::~Video() {
	for (int i = 0; i < this->Textures.size(); i++) {
		for (int j = 0; j < this->Textures[i].size(); j++) {
			delete this->Textures[i][j];
		}
	}
}

//------------------------------------- Flatten 2D Vector --------------------------------//

void Video::FlattenTextures() {
	for (int i = 0; i < this->Textures.size(); i++) {
		for (int j = 0; j < this->Textures[i].size(); j++) {
			this->Frames.push_back(this->Textures[i][j]);
		}
	}
}

//-------------------------------------- Load In Parallel --------------------------------//

void Video::LoadInParallel(int Branches) {
	std::vector<std::thread> Threads;
	int Steps = (End - Start) / Branches;
	int Current = this->Start;

	for (int i = 0; i < Branches; i++) {
		std::vector<sf::Texture*> CurrentTextureVector;
		this->Textures.push_back(CurrentTextureVector);
		Threads.emplace_back([i, Current, Steps, this]() {this->Load(i, Current, MT::Min(Current + Steps, this->End)); });
		Current += Steps + 1;
	}
	
	for (int i = 0; i < Threads.size(); i++) {
		if(Threads[i].joinable())Threads[i].join();
	}

	this->FlattenTextures();
	this->VideoFrame.setTexture(this->Frames[this->FrameIndex]);
	this->Ready = true;
}

//-------------------------------------------- Load --------------------------------------//

void Video::Load(int Index, int Start, int End) {
	for (int i = Start; i <= End; i++) {
		sf::Image CurrentImage;
		sf::Texture * CurrentTexture = new sf::Texture();
		std::string CurrentPath = this->Path + this->Prefix + MT::Text(i, this->Digits) + this->Format;
		CurrentImage.loadFromFile(CurrentPath);
		CurrentTexture->loadFromImage(CurrentImage);
		this->Textures[Index].push_back(CurrentTexture);
	}
}

//------------------------------------------ Is Ready -------------------------------------//

bool Video::IsReady() {
	return this->Ready;
}

//------------------------------------------ Set Size -------------------------------------//

void Video::SetSize(Dimension Size) {
	this->Size = Size;
	this->VideoFrame.setSize(sf::Vector2f(this->Size.GetWidth(), this->Size.GetHeight()));
}

//---------------------------------------- Set Position -----------------------------------//

void Video::SetPosition(Point Position) {
	this->Position = Position;
	this->VideoFrame.setPosition(this->Position.GetX(), this->Position.GetY());
}

//---------------------------------------- ++ Operator ------------------------------------//

Video & Video::operator++() {
	this->FrameIndex++;
	if (this->FrameIndex >= this->Frames.size()) {
		if (this->Repeate)this->FrameIndex = 0;
		else this->FrameIndex--;
	}
	this->VideoFrame.setTexture(this->Frames[this->FrameIndex]);
	return * this;
}

//------------------------------------------ Reset ---------------------------------------//

void Video::Reset() {
	this->FrameIndex = 0;
}

//------------------------------------------- Draw ---------------------------------------//

void Video::Draw() {
	GameWindow->draw(this->VideoFrame);
}

//----------------------------------------- Refresh --------------------------------------//

void Video::Refresh() {
	if (this->Timer.getElapsedTime().asMilliseconds() >= this->GapBetweenFrames) {
		++(*this);
		this->Timer.restart();
	}
}