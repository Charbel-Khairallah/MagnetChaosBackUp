#pragma once
#include "Frame.h"
#include "LoadingScreen.h"
#include "TutorialFrame.h"

class MainFrame : public Frame {
private:
	static bool Loading;

	std::vector<sf::Text> Labels;

	LoadingScreen * Load;
public:
	MainFrame();
	~MainFrame();

	void DrawFrame();
	void DoAction(sf::Event& CurrentEvent);
	void DoEvents();
	void FadeIn();
	void FadeOut();
};