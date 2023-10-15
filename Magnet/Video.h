#pragma once
#include <SFML/Graphics.hpp>
#include <thread>

#include "Methods.h"
#include "Point.h"
#include "Dimension.h"

class Video {
private:
	bool Repeate;
	bool Ready;
	int Start;
	int End;
	int Digits;
	int FrameIndex;

	std::vector<sf::Texture*> Frames;
	std::vector<std::vector<sf::Texture*>> Textures;
	std::string Path;
	std::string Prefix;
	std::string Format;

	sf::RectangleShape VideoFrame;

	Point Position;
	Dimension Size;

	int GapBetweenFrames;
	sf::Clock Timer;

	void FlattenTextures();
	void Load(int Index, int Start, int End);

public:
	Video(int Start, int End, std::string Path, bool Repeate = true);
	~Video();

	void SetSize(Dimension Size);
	void SetPosition(Point Position);
	void LoadInParallel(int Branches);
	void Reset();

	void Draw();
	void Refresh();
	
	bool IsReady();

	Video& operator ++();
};