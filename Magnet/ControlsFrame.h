#pragma once
#include "Frame.h"
#include "Key.h"
#include "ControlItem.h"
#include "BackIcon.h"


class ControlsFrame : public Frame {
private:
	Point ItemsReferenceOrigin;
	Point CurrentItemsOrigin;

	double TopLimit;
	double BottomLimit;
	int TimerDuration;

	sf::Text TitleLabel;
	sf::Text ErrorMessage;

	sf::Vertex TopGradientVertex[4];
	sf::Vertex BottomGradientVertex[4];
	sf::RectangleShape TopRectangle;
	sf::RectangleShape BottomRectangle;
	sf::RectangleShape BlockRectangle;

	sf::Clock * Timer;

	std::vector<std::vector<Key * >> Keys;
	std::vector<ControlItem> Items;
	std::string DataKeyPath;
	std::string DataValuePath;

	BackIcon Back;

	double Shift;
	double ShiftDifference;

public:
	ControlsFrame();
	~ControlsFrame();

	void DrawFrame();
	void DoAction(sf::Event& CurrentEvent);
	void DoEvents();
	void FadeIn();
	void FadeOut();
	void Scroll();
	void ClearSelection();
};