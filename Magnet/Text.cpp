#pragma once
#include "Text.h"


//--------------------------------------- Constructor ---------------------------------------//

Text::Text(std::vector<std::string> Lines, double TextSize, Point Position) {
	this->Lines = Lines;
	this->TextSize = TextSize;
	this->Position = Position;

	this->TimeGap = 30; //30 ms
	this->TextColor = COLOR;
	this->CharacterGapTimer.restart();

	this->Reset();
}

Text::Text() {

}

//--------------------------------------- Destructor ---------------------------------------//

Text::~Text() {
	
}

//----------------------------------------- Draw ------------------------------------------//

void Text::Draw() {
	double X = this->Position.GetX();
	double Y = this->Position.GetY();
	for (int i = 0; i < this->VisibleLines.size(); i++) {
		this->VisibleLines[i].setPosition(X, Y);
		GameWindow->draw(this->VisibleLines[i]);
		Y += this->VisibleLines[i].getGlobalBounds().height * 1.5;
	}
}

//--------------------------------------- Refresh ----------------------------------------//

void Text::Refresh() {
	if (this->CharacterGapTimer.getElapsedTime().asMilliseconds() >= this->TimeGap) {
		this->CalculateNextCharacter();
		if (this->HasNext) {
			std::string CurrentText = this->VisibleLines[this->CurrentRow].getString();
			CurrentText += this->Lines[this->CurrentRow][this->CurrentColumn];
			this->VisibleLines[this->CurrentRow].setString(CurrentText);
		}
		this->CharacterGapTimer.restart();
	}
}

//------------------------------- Calculate Next Character --------------------------------//

void Text::CalculateNextCharacter() {
	if (this->HasNext) {
		int CurrentColumnCopy = this->CurrentColumn;
		int CurrentRowCopy = this->CurrentRow;
		CurrentColumnCopy++;
		while (CurrentRowCopy < this->Lines.size() && this->Lines[CurrentRowCopy].length() <= CurrentColumnCopy) {
			CurrentColumnCopy = 0;
			CurrentRowCopy++;
		}
		if (CurrentRowCopy < this->Lines.size() && CurrentColumnCopy < this->Lines[CurrentRowCopy].length()) {
			this->CurrentColumn = CurrentColumnCopy;
			this->CurrentRow = CurrentRowCopy;
		}
		else {
			this->HasNext = false;
		}
	}
}

//---------------------------------------- Reset -----------------------------------------//

void Text::Reset() {
	this->CurrentColumn = -1;
	this->CurrentRow = 0;
	this->HasNext = true;

	this->VisibleLines.clear();
	for (int i = 0; i < this->Lines.size(); i++) {
		this->VisibleLines.push_back(sf::Text("", FONT, this->TextSize));
		this->VisibleLines[i].setFillColor(this->TextColor);
	}
}