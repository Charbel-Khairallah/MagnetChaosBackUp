#pragma once
#include "TutorialFrame.h"
#include "File.h"

std::vector<Video*> TutorialFrame::Videos;
int TutorialFrame::LeftShift;
int TutorialFrame::TopShift;

//------------------------------------ Constructor ------------------------------------//

TutorialFrame::TutorialFrame() : Frame() {
	double X, Y, Width, Height;
	this->FrameState = Activating;

	/* Block Rectangle */
	this->BlockRectangle.setPosition(0, 0);
	this->BlockRectangle.setSize(sf::Vector2f(GameWindow->getSize().x, GameWindow->getSize().y));
	this->BlockRectangle.setFillColor(BACKGROUND);

	/* User Input */
	std::vector<std::string> Data = File::Read("../GameData/Settings/Names.txt");

	this->Move = Data[0];
	this->PositiveShift = Data[1];
	this->NegativeShift = Data[2];
	this->Upgrade = Data[3];
	this->MoveSelectionUp = Data[4];
	this->MoveSelectionDown = Data[5];


	/* Tutorial Text */
	TutorialFrame::LeftShift = 150;
	TutorialFrame::TopShift = 10;
	this->CurrentTextIndex = 0;
	std::vector<std::string> TextToAdd;
	TextToAdd.push_back("Press '" + this->Move + "' To Move;                ");
	TextToAdd.push_back("The Magnet Follows The Mouse Cursor.                ");
	TextToAdd.push_back("Survive As Long As Possible While Avoiding The Robots.");
	this->TutorialText.push_back(Text(TextToAdd, H3, Point(TutorialFrame::LeftShift, TutorialFrame::TopShift)));

	TextToAdd.clear();
	TextToAdd.push_back("Press '" + this->NegativeShift + "' To Increase The Magnet's Polarity, Attracting Iron Blocks,                ");
	TextToAdd.push_back("And '" + this->PositiveShift + "' To Decrease The Magnet's Polarity, Repelling Iron Blocks.");
	this->TutorialText.push_back(Text(TextToAdd, H3, Point(TutorialFrame::LeftShift, TutorialFrame::TopShift)));

	TextToAdd.clear();
	TextToAdd.push_back("When 2 Iron Blocks Collide With Enough Force, They Combine To Form A Copper Block.                ");
	TextToAdd.push_back("This Block Emits A Magnetic Field When You Approach It, The Strength Of Which Depends On The Magnet's Field Strength.");
	this->TutorialText.push_back(Text(TextToAdd, H3, Point(TutorialFrame::LeftShift, TutorialFrame::TopShift)));

	TextToAdd.clear();
	TextToAdd.push_back("You Can Defeat The Robots By Striking Them With the Iron Blocks.                ");
	TextToAdd.push_back("You Can Also Lure Them Into The Magnetic Field Generated By The Copper Block.");
	this->TutorialText.push_back(Text(TextToAdd, H3, Point(TutorialFrame::LeftShift, TutorialFrame::TopShift)));

	TextToAdd.clear();
	TextToAdd.push_back("Lastly, You Can Enhance Your Magnet By Selecting An Upgrade And Pressing '" + this->Upgrade + "'.                ");
	TextToAdd.push_back("When And Upgrade Is Available, It Will Be Displayed In Green.");
	this->TutorialText.push_back(Text(TextToAdd, H3, Point(TutorialFrame::LeftShift, TutorialFrame::TopShift)));

	this->VisibleText = &this->TutorialText[this->CurrentTextIndex];

	/* Transition Rectangle */
	this->TransitionRectangle.setPosition(0, 0);
	this->TransitionRectangle.setSize(sf::Vector2f(GameWindow->getSize().x, GameWindow->getSize().y));
	this->TransitionRectangle.setFillColor(TRANSPARENT);

	/* Buttons */
	Width = 200;
	Height = 60;
	X = (GameWindow->getSize().x - 2 * (Width + 20)) / 2.0;
	Y = GameWindow->getSize().y - Height - 20;
	this->Previous = Button(Point(X, Y), Dimension(Width, Height), "Previous", 3, 15);
	this->Next = Button(Point(X + Width + 40, Y), Dimension(Width, Height), "Next", 3, 15);
	
	this->Previous.Disable();
}

//------------------------------------- Destructor ------------------------------------//

TutorialFrame::~TutorialFrame() {

}

//-------------------------------------- DrawFrame ------------------------------------//

void TutorialFrame::DrawFrame() {
	GameWindow->clear();

	
	this->VisibleText->Draw();
	TutorialFrame::Videos[this->CurrentTextIndex]->Draw();
	GameWindow->draw(this->TransitionRectangle);

	this->Previous.Draw();
	this->Next.Draw();
	this->Back.Draw();
	GameWindow->draw(this->BlockRectangle);

	GameWindow->display();
}

//--------------------------------------- Do Events ------------------------------------//

void TutorialFrame::DoEvents() {
	Frame::BackgroundSound.setVolume(MT::Shift(Frame::BackgroundSound.getVolume(), LOW, 15));
	if (this->FrameState == Activating)this->FadeIn();
	if (this->FrameState == Deactivating)this->FadeOut();
	if (this->FrameState == Active) {

		bool HandCursor = false;

		this->Back.Refresh();
		this->Previous.Refresh();
		this->Next.Refresh();
		TutorialFrame::Videos[this->CurrentTextIndex]->Refresh();

		if (this->Back.MouseOver())HandCursor = true;
		if (this->Next.MouseOver() && this->Next.IsEnabled())HandCursor = true;
		if (this->Previous.MouseOver() && this->Previous.IsEnabled())HandCursor = true;

		if (!HandCursor)GameWindow->setMouseCursor(ARROW);
		else GameWindow->setMouseCursor(HAND);

		this->VisibleText->Refresh();

		if (this->TransitionState == FadingOut) {
			this->TransitionRectangle.setFillColor(MT::Shift(this->TransitionRectangle.getFillColor(), BACKGROUND, FAST));
			if (this->TransitionRectangle.getFillColor() == BACKGROUND) {
				this->TransitionState = FadingIn;
				this->TutorialText[this->CurrentTextIndex].Reset();
				TutorialFrame::Videos[this->CurrentTextIndex]->Reset();
				this->CurrentTextIndex = this->FutureIndex;
				this->VisibleText = &this->TutorialText[this->FutureIndex];
			}
		}
		if (this->TransitionState == FadingIn) {
			this->TransitionRectangle.setFillColor(MT::Shift(this->TransitionRectangle.getFillColor(), TRANSPARENT, FAST));
			if (this->TransitionRectangle.getFillColor() == TRANSPARENT) {
				this->TransitionState = Default;
				if(this->CurrentTextIndex > 0)this->Previous.Enable();
				if(this->CurrentTextIndex < (this->TutorialText.size() - 1))this->Next.Enable();
			}
		}
	}
}

//--------------------------------------- Do Action ------------------------------------//

void TutorialFrame::DoAction(sf::Event& CurrentEvent) {
	if (this->FrameState == Active) {
		bool ActivateTransition = false;
		if (CurrentEvent.type == sf::Event::Closed) {
			this->FrameState = Deactivating;
			this->FadeOut();
			this->NavigateTo = MAIN_FRAME;
		}
		else if ((CurrentEvent.type == sf::Event::KeyReleased) && (CurrentEvent.key.code == sf::Keyboard::Escape)) {
			this->FrameState = Deactivating;
			this->FadeOut();
			this->NavigateTo = MAIN_FRAME;
		}
		else if (CurrentEvent.type == sf::Event::MouseButtonReleased && this->Back.MouseOver() && CurrentEvent.key.code == sf::Mouse::Left) {
			this->FrameState = Deactivating;
			this->FadeOut();
			this->NavigateTo = MAIN_FRAME;
		} 
		else if (CurrentEvent.type == sf::Event::KeyReleased && CurrentEvent.key.code == sf::Keyboard::Right) {
			if (this->CurrentTextIndex < (this->TutorialText.size() - 1) && this->TransitionState == Default) {
				this->FutureIndex = this->CurrentTextIndex + 1;
				ActivateTransition = true;
			}
		}
		else if (CurrentEvent.type == sf::Event::KeyReleased && CurrentEvent.key.code == sf::Keyboard::Left) {
			if (this->CurrentTextIndex > 0 && this->TransitionState == Default) {
				this->FutureIndex = this->CurrentTextIndex - 1;
				ActivateTransition = true;
			}
		}
		else if (CurrentEvent.type == sf::Event::MouseButtonReleased && this->Next.MouseOver() && CurrentEvent.key.code == sf::Mouse::Left) {
			if (this->CurrentTextIndex < (this->TutorialText.size() - 1) && this->TransitionState == Default) {
				this->FutureIndex = this->CurrentTextIndex + 1;
				ActivateTransition = true;
			}
		}
		else if (CurrentEvent.type == sf::Event::MouseButtonReleased && this->Previous.MouseOver() && CurrentEvent.key.code == sf::Mouse::Left) {
			if (this->CurrentTextIndex > 0 && this->TransitionState == Default) {
				this->FutureIndex = this->CurrentTextIndex - 1;
				ActivateTransition = true;
			}
		}
		

		if (ActivateTransition) {
			this->TransitionState = FadingOut;
			this->Previous.Disable();
			this->Next.Disable();
		}
	}
}

//---------------------------------------- FadeIn -------------------------------------//

void TutorialFrame::FadeIn() {
	this->BlockRectangle.setFillColor(MT::Shift(this->BlockRectangle.getFillColor(), TRANSPARENT, NORMAL));
	if (this->BlockRectangle.getFillColor() == TRANSPARENT) {
		this->FrameState = Active;
	}
}

//---------------------------------------- FadeOut -------------------------------------//

void TutorialFrame::FadeOut() {
	this->BlockRectangle.setFillColor(MT::Shift(this->BlockRectangle.getFillColor(), BACKGROUND, NORMAL));
	if (this->BlockRectangle.getFillColor() == BACKGROUND) {
		this->FrameState = Inactive;
	}
}

//-------------------------------------- Set Videos ------------------------------------//

void TutorialFrame::SetVideos(std::vector<Video*> CurrentVideos) {
	TutorialFrame::Videos = CurrentVideos;
	TutorialFrame::FixVideoBounds();
}

//----------------------------------- Fix Video Bounds ---------------------------------//

void TutorialFrame::FixVideoBounds() {
	Point Position(200, (TutorialFrame::TopShift + 100) * 2);
	Dimension Size((GameWindow->getSize().x - Position.GetX() * 2), (GameWindow->getSize().y - Position.GetY() * 2));
	for (int i = 0; i < TutorialFrame::Videos.size(); i++) {
		TutorialFrame::Videos[i]->SetPosition(Position);
		TutorialFrame::Videos[i]->SetSize(Size);
	}
}