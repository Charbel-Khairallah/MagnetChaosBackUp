#pragma once
#include "Mainframe.h"
#include "Methods.h"

bool MainFrame::Loading = true;

//------------------------------------ Constructor ------------------------------------//

MainFrame::MainFrame() : Frame() {

	int Columns = 1;
	int Rows = 4;
	double ContainerWidth = GameWindow->getSize().x / double(Columns);
	double ContainerHeight = GameWindow->getSize().y / double(Rows);

	this->Labels.push_back(sf::Text("Start", FONT, H1));
	this->Labels.push_back(sf::Text("Controls", FONT, H1));
	this->Labels.push_back(sf::Text("Tutorial", FONT, H1));
	this->Labels.push_back(sf::Text("Exit", FONT, H1));

	for (int i = 0; i < Labels.size(); i++) {
		this->Labels[i].setFillColor(TRANSPARENT);
		double X_Shift = ContainerWidth * (i % Columns) + (ContainerWidth - this->Labels[i].getGlobalBounds().width) / 2.0;
		double Y_Shift = ContainerHeight * (i / Columns) + (ContainerHeight - this->Labels[i].getGlobalBounds().height) / 2.0;
		this->Labels[i].setPosition(sf::Vector2f(X_Shift, Y_Shift));
	}

	if(MainFrame::Loading)this->Load = new LoadingScreen();
}

//------------------------------------- Destructor ------------------------------------//

MainFrame::~MainFrame() {
	
}

//-------------------------------------- DrawFrame ------------------------------------//

void MainFrame::DrawFrame() {
	GameWindow->clear();
	if (MainFrame::Loading) {
		this->Load->Draw();
	}
	else {
		if (this->FrameState == Activating)this->FadeIn();
		if (this->FrameState == Deactivating)this->FadeOut();
		for (int i = 0; i < this->Labels.size(); i++) {
			GameWindow->draw(this->Labels[i]);
		}
	}
	GameWindow->display();
}

//--------------------------------------- Do Events ------------------------------------//

void MainFrame::DoEvents() {
	if (MainFrame::Loading) {
		this->Load->Refresh();
		if (this->Load->HasFinished()) {
			MainFrame::Loading = false;
			TutorialFrame::SetVideos(this->Load->GetLoadedVideos());
			delete this->Load;
			this->Load = NULL;
		}
	}
	else {
		if (this->FrameState == Activating || this->FrameState == Active)
			Frame::BackgroundSound.setVolume(MT::Shift(Frame::BackgroundSound.getVolume(), LOW, 15));
		else {
			if (this->NavigateTo == NONE)Frame::BackgroundSound.setVolume(MT::Shift(Frame::BackgroundSound.getVolume(), MUTE, 15));
		}
		if (this->FrameState == Active) {
			bool HandCursor = false;
			for (int i = 0; i < this->Labels.size(); i++) {
				if (MT::MouseOverText(this->Labels[i])) {
					HandCursor = true;
					GameWindow->setMouseCursor(HAND);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
						this->Labels[i].setFillColor(MT::Shift(this->Labels[i].getFillColor(), PRESSED_COLOR, FAST));
					}
					else {
						this->Labels[i].setFillColor(MT::Shift(this->Labels[i].getFillColor(), HOVER_COLOR, SLOW));
					}
				}
				else {
					this->Labels[i].setFillColor(MT::Shift(this->Labels[i].getFillColor(), COLOR, SLOW));
				}
			}
			if (!HandCursor)GameWindow->setMouseCursor(ARROW);
		}
	}
}

//--------------------------------------- Do Action ------------------------------------//

void MainFrame::DoAction(sf::Event& CurrentEvent) {

	if (this->FrameState == Active) {
		bool MouseDown = false;
		if (CurrentEvent.type == sf::Event::Closed) {
			this->FrameState = Deactivating;
			this->FadeOut();
			this->NavigateTo = NONE;
		}
		if ((CurrentEvent.type == sf::Event::KeyReleased) && (CurrentEvent.key.code == sf::Keyboard::Escape)) {
			this->FrameState = Deactivating;
			this->FadeOut();
			this->NavigateTo = NONE;
		}

		for (int i = 0; i < this->Labels.size(); i++) {
			if (MT::MouseOverText(this->Labels[i]) && CurrentEvent.type == sf::Event::MouseButtonReleased) {
				this->FrameState = Deactivating;
				this->FadeOut();
				switch (i){
					case 0: {
						this->NavigateTo = START_FRAME;
						break;
					}
					case 1: {
						this->NavigateTo = CONTROLS_FRAME;
						break;
					}
					case 2: {
						this->NavigateTo = TUTORIAL_FRAME;
						break;
					}
					case 3: {
						this->NavigateTo = NONE;
						break;
					}
					default: {
						this->NavigateTo = NONE;
						break;
					}
				}
			}
		}
	}
}

//---------------------------------------- FadeIn -------------------------------------//

void MainFrame::FadeIn() {
	int Count = 0;
	for (int i = 0; i < Labels.size(); i++) {
		this->Labels[i].setFillColor(MT::Shift(this->Labels[i].getFillColor(), COLOR, SLOW));
		if (this->Labels[i].getFillColor() == COLOR) Count++;
	}
	if (Count == Labels.size()) {
		this->FrameState = Active;
	}
}

//---------------------------------------- FadeOut -------------------------------------//

void MainFrame::FadeOut() {
	int Count = 0;
	for (int i = 0; i < Labels.size(); i++) {
		this->Labels[i].setFillColor(MT::Shift(this->Labels[i].getFillColor(), TRANSPARENT, SLOW));
		if (this->Labels[i].getFillColor() == TRANSPARENT) Count++;
	}
	if (Count == Labels.size()) {
		this->FrameState = Inactive;
	}

}