#pragma once
#include "Frame.h"
#include "BackIcon.h"
#include "UserInput.h"
#include "Text.h"
#include "BlockState.h"
#include "Button.h"
#include "Video.h"

class TutorialFrame : public Frame {
private:
	static std::vector<Video*> Videos;
	static int LeftShift;
	static int TopShift;

	int CurrentTextIndex;
	int FutureIndex;
	std::vector<Text> TutorialText;
	
	Text * VisibleText;
	sf::RectangleShape TransitionRectangle;
	sf::RectangleShape BlockRectangle;

	BlockState TransitionState;

	std::string Move;
	std::string MoveSelectionUp;
	std::string MoveSelectionDown;
	std::string PositiveShift;
	std::string NegativeShift;
	std::string Upgrade;

	sf::Clock LetterTimer;

	BackIcon Back;

	Button Next;
	Button Previous;
public:
	TutorialFrame();
	~TutorialFrame();

	void DrawFrame();
	void DoAction(sf::Event& CurrentEvent);
	void DoEvents();
	void FadeIn();
	void FadeOut();

	static void SetVideos(std::vector<Video*> Videos);
	static void FixVideoBounds();
};