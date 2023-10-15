#pragma once
#include <unordered_map>

#include "ControlsFrame.h"
#include "Methods.h"
#include "KeyboardKey.h"
#include "Rectangle.h"
#include "MouseKey.h"
#include "File.h"

//------------------------------------ Constructor ------------------------------------//

ControlsFrame::ControlsFrame() : Frame() {
	this->Timer = NULL;

	this->Shift = 0;
	this->ShiftDifference = 0;
	this->TimerDuration = 3'000; // 3 seconds
	this->DataKeyPath = "../GameData/Settings/Controls.txt";
	this->DataValuePath = "../GameData/Settings/Names.txt";

	/* Block Rectangle */
	this->BlockRectangle.setPosition(0, 0);
	this->BlockRectangle.setSize(sf::Vector2f(GameWindow->getSize().x, GameWindow->getSize().y));
	this->BlockRectangle.setFillColor(BACKGROUND);

	/* Main Keyboard */
	std::vector<std::vector<double>> Multiplier =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
		{1.5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1.5},
		{2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
		{2.5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2.5},
		{4 / 3.0, 4 / 3.0, 4 / 3.0, 7, 4 / 3.0, 4 / 3.0, 4 / 3.0}
	};
	std::vector<std::vector<std::string>> Letter =
	{
		{"`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "<-"},
		{"Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[", "]", "\\"},
		{"Caps Lock", "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "Enter"},
		{"Shift", "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/", "Shift"},
		{"Ctrl", "@", "Alt", "Space", "Alt", "FN", "Ctrl"}
	};
	std::vector<std::vector<int>> EventCode = {
		{
			sf::Keyboard::Tilde, sf::Keyboard::Num1, sf::Keyboard::Num2, sf::Keyboard::Num3, sf::Keyboard::Num4, 
			sf::Keyboard::Num5, sf::Keyboard::Num6, sf::Keyboard::Num7, sf::Keyboard::Num8, sf::Keyboard::Num9, 
			sf::Keyboard::Num0, sf::Keyboard::Dash, sf::Keyboard::Equal, sf::Keyboard::BackSpace
		},
		{
			sf::Keyboard::Tab, sf::Keyboard::Q, sf::Keyboard::W, sf::Keyboard::E, sf::Keyboard::R, sf::Keyboard::T,
			sf::Keyboard::Y, sf::Keyboard::U, sf::Keyboard::I, sf::Keyboard::O, sf::Keyboard::P, sf::Keyboard::LBracket,
			sf::Keyboard::RBracket, sf::Keyboard::BackSlash
		},
		{
			-2, sf::Keyboard::A, sf::Keyboard::S, sf::Keyboard::D, sf::Keyboard::F, sf::Keyboard::G, sf::Keyboard::H,
			sf::Keyboard::J, sf::Keyboard::K, sf::Keyboard::L, sf::Keyboard::SemiColon, sf::Keyboard::Quote,
			sf::Keyboard::Enter
		},
		{
			sf::Keyboard::LShift, sf::Keyboard::Z, sf::Keyboard::X, sf::Keyboard::C, sf::Keyboard::V, sf::Keyboard::B,
			sf::Keyboard::N, sf::Keyboard::M, sf::Keyboard::Comma, sf::Keyboard::Period, sf::Keyboard::Slash, 
			sf::Keyboard::RShift
		},
		{
			sf::Keyboard::LControl, -3, sf::Keyboard::LAlt, sf::Keyboard::Space, sf::Keyboard::RAlt, -4, sf::Keyboard::RControl
		}
	};
	double X, Y;
	std::unordered_map<std::string, Key*> AllKeys;
	for (int i = 0; i < Multiplier.size(); i++) {
		X = 0;
		Y = i * KeyboardKey::Unit.GetHeight();
		this->Keys.push_back(std::vector<Key * >());
		for (int j = 0; j < Multiplier[i].size(); j++) {
			Key * NewKey = new KeyboardKey(0, Letter[i][j], Multiplier[i][j], Dimension(X, Y), sf::Event::KeyPressed, EventCode[i][j]);
			this->Keys[i].push_back(NewKey);
			AllKeys.insert({ NewKey->GetID(), NewKey });
			X += KeyboardKey::Unit.GetWidth() * Multiplier[i][j];
		}
	}

	
	/* Rest Of The Keys */
	Key * LastKey = this->Keys[this->Keys.size() - 1][this->Keys[this->Keys.size() - 1].size() - 1];
	Point BottomLeftReferencePoint(LastKey->GetX() + LastKey->GetWidth() * 2, LastKey->GetY());

	Key * LeftArrow = new KeyboardKey(180, ">", 1, Dimension(BottomLeftReferencePoint.GetX() - KeyboardKey::Origin.GetX(), BottomLeftReferencePoint.GetY() - KeyboardKey::Origin.GetY()), sf::Event::KeyPressed, sf::Keyboard::Left);
	Key * DownArrow = new KeyboardKey(90, ">", 1, Dimension(BottomLeftReferencePoint.GetX() + LeftArrow->GetWidth() - KeyboardKey::Origin.GetX(), BottomLeftReferencePoint.GetY() - KeyboardKey::Origin.GetY()), sf::Event::KeyPressed, sf::Keyboard::Down);
	Key * RightArrow = new KeyboardKey(0, ">", 1, Dimension(DownArrow->GetX() + DownArrow->GetWidth() - KeyboardKey::Origin.GetX(), BottomLeftReferencePoint.GetY() - KeyboardKey::Origin.GetY()), sf::Event::KeyPressed, sf::Keyboard::Right);
	Key * UpArrow = new KeyboardKey(270, ">", 1, Dimension(DownArrow->GetX() - KeyboardKey::Origin.GetX(), DownArrow->GetY() - DownArrow->GetHeight() - KeyboardKey::Origin.GetY()), sf::Event::KeyPressed, sf::Keyboard::Up);

	int Index = this->Keys.size();
	this->Keys.push_back(std::vector<Key*>());
	this->Keys[Index].push_back(LeftArrow);
	this->Keys[Index].push_back(DownArrow);
	this->Keys[Index].push_back(RightArrow);
	this->Keys[Index].push_back(UpArrow);

	AllKeys.insert({ LeftArrow->GetID(), LeftArrow });
	AllKeys.insert({ DownArrow->GetID(), DownArrow });
	AllKeys.insert({ RightArrow->GetID(), RightArrow });
	AllKeys.insert({ UpArrow->GetID(), UpArrow });

	Index = this->Keys.size();
	this->Keys.push_back(std::vector<Key*>());
	X = BottomLeftReferencePoint.GetX();
	Y = this->Keys[0][0]->GetY();
	Key * NewMouseKey = new MouseKey(Point(X + this->Keys[0][0]->GetWidth() * 0.6, Y), Dimension(this->Keys[0][0]->GetWidth() * 1.8, this->Keys[0][0]->GetHeight() * 2.5), sf::Event::MouseButtonPressed, 0);
	this->Keys[Index].push_back(NewMouseKey);

	AllKeys.insert({ NewMouseKey->GetID(), NewMouseKey });

	/* Title */

	this->TitleLabel = sf::Text("Controls", FONT, H1);
	X = (GameWindow->getSize().x - this->TitleLabel.getGlobalBounds().width) / 2.0;
	Y = (KeyboardKey::Origin.GetY() - this->TitleLabel.getGlobalBounds().height) / 2.0;
	this->TitleLabel.setPosition(X, Y);

	/* Error Message */

	this->ErrorMessage = sf::Text("Key Not Supported", FONT, H1);
	this->ErrorMessage.setFillColor(TRANSPARENT);
	X = (GameWindow->getSize().x - this->ErrorMessage.getGlobalBounds().width) / 2.0;
	double KeyboardBottomY = KeyboardKey::Origin.GetY() + KeyboardKey::Unit.GetHeight() * 5;
	Y = KeyboardBottomY + (GameWindow->getSize().y - KeyboardBottomY - this->ErrorMessage.getGlobalBounds().height) / 2.0;
	this->ErrorMessage.setPosition(X, Y);

	/* Gradiants */
	
	double ListWidth = KeyboardKey::Origin.GetX() * 0.8;
	double VerticalPadding = KeyboardKey::Origin.GetY();

	this->TopGradientVertex[0] = sf::Vertex(sf::Vector2f(0, VerticalPadding / 2.0), BACKGROUND);
	this->TopGradientVertex[1] = sf::Vertex(sf::Vector2f(ListWidth, VerticalPadding / 2.0), BACKGROUND);
	this->TopGradientVertex[2] = sf::Vertex(sf::Vector2f(ListWidth, VerticalPadding), TRANSPARENT);
	this->TopGradientVertex[3] = sf::Vertex(sf::Vector2f(0, VerticalPadding), TRANSPARENT);

	this->BottomGradientVertex[0] = sf::Vertex(sf::Vector2f(0, GameWindow->getSize().y - VerticalPadding), TRANSPARENT);
	this->BottomGradientVertex[1] = sf::Vertex(sf::Vector2f(ListWidth, GameWindow->getSize().y - VerticalPadding), TRANSPARENT);
	this->BottomGradientVertex[2] = sf::Vertex(sf::Vector2f(ListWidth, GameWindow->getSize().y - VerticalPadding / 2.0), BACKGROUND);
	this->BottomGradientVertex[3] = sf::Vertex(sf::Vector2f(0, GameWindow->getSize().y - VerticalPadding / 2.0), BACKGROUND);

	/* Rectangles Above And Under gradients */

	this->TopRectangle = sf::RectangleShape(sf::Vector2f(ListWidth, VerticalPadding / 2.0));
	this->TopRectangle.setPosition(0, 0);
	this->TopRectangle.setFillColor(BACKGROUND);

	this->BottomRectangle = sf::RectangleShape(sf::Vector2f(ListWidth, VerticalPadding / 2.0));
	this->BottomRectangle.setPosition(0, GameWindow->getSize().y - VerticalPadding / 2.0);
	this->BottomRectangle.setFillColor(BACKGROUND);

	/* Items */

	this->ItemsReferenceOrigin = Point(0, VerticalPadding);
	this->CurrentItemsOrigin = this->ItemsReferenceOrigin;

	std::vector<std::string> Data = File::Read(this->DataKeyPath);

	this->Items.push_back(ControlItem(this->CurrentItemsOrigin, Dimension(ListWidth, ListWidth / 2.0), 0, "Move", AllKeys[MT::Split(Data[0], ';')[0]], std::stoi(MT::Split(Data[0], ';')[1])));
	this->Items.push_back(ControlItem(this->CurrentItemsOrigin, Dimension(ListWidth, ListWidth / 2.0), 1, "Positive Shift", AllKeys[MT::Split(Data[1], ';')[0]], std::stoi(MT::Split(Data[1], ';')[1])));
	this->Items.push_back(ControlItem(this->CurrentItemsOrigin, Dimension(ListWidth, ListWidth / 2.0), 2, "Negative Shift", AllKeys[MT::Split(Data[2], ';')[0]], std::stoi(MT::Split(Data[2], ';')[1])));
	this->Items.push_back(ControlItem(this->CurrentItemsOrigin, Dimension(ListWidth, ListWidth / 2.0), 3, "Updgrade", AllKeys[MT::Split(Data[3], ';')[0]], std::stoi(MT::Split(Data[3], ';')[1])));
	this->Items.push_back(ControlItem(this->CurrentItemsOrigin, Dimension(ListWidth, ListWidth / 2.0), 4, "Move Selection Up", AllKeys[MT::Split(Data[4], ';')[0]], std::stoi(MT::Split(Data[4], ';')[1])));
	this->Items.push_back(ControlItem(this->CurrentItemsOrigin, Dimension(ListWidth, ListWidth / 2.0), 5, "Move Selection Down", AllKeys[MT::Split(Data[5], ';')[0]], std::stoi(MT::Split(Data[5], ';')[1])));
	
	ControlItem::SelectedItem = &this->Items[0];
	ControlItem::SelectedItem->SelectedKey->Select(ControlItem::SelectedItem->SelectedKeyIndex);

	this->TopLimit = VerticalPadding;
	this->BottomLimit = GameWindow->getSize().y - VerticalPadding;
}


//------------------------------------- Destructor ------------------------------------//

ControlsFrame::~ControlsFrame() {
	std::vector<std::string> DataKey;
	std::vector<std::string> DataValue;
	for (int i = 0; i < this->Items.size(); i++) {
		DataKey.push_back(this->Items[i].SelectedKey->GetID() + ";" + std::to_string(this->Items[i].SelectedKeyIndex));
		DataValue.push_back(this->Items[i].GetValue());
	}
	File::Write(this->DataKeyPath, DataKey);
	File::Write(this->DataValuePath, DataValue);

	for (int i = 0; i < this->Keys.size(); i++) {
		for (int j = 0; j < this->Keys[i].size(); j++)delete this->Keys[i][j];
	}
	if (this->Timer != NULL)delete this->Timer;
}

//-------------------------------------- DrawFrame ------------------------------------//

void ControlsFrame::DrawFrame() {
	GameWindow->clear();

	GameWindow->draw(this->TitleLabel);

	for (int i = 0; i < this->Keys.size(); i++) {
		for (int j = 0; j < this->Keys[i].size(); j++) {
			this->Keys[i][j]->Draw();
		}
	}

	for (int i = 0; i < this->Items.size(); i++)this->Items[i].Draw();

	GameWindow->draw(this->TopGradientVertex, 4, sf::Quads);
	GameWindow->draw(this->BottomGradientVertex, 4, sf::Quads);
	GameWindow->draw(this->TopRectangle);
	GameWindow->draw(this->BottomRectangle);
	GameWindow->draw(this->ErrorMessage);

	this->Back.Draw();

	GameWindow->draw(this->BlockRectangle);

	GameWindow->display();
}

//---------------------------------------- Scroll -------------------------------------//

void ControlsFrame::Scroll() {
	if (this->ShiftDifference >= -0.5 && this->ShiftDifference <= 0.5)this->ShiftDifference = 0;
	else if (this->ShiftDifference > 0)this->ShiftDifference -= 0.5;
	else if (this->ShiftDifference < 0)this->ShiftDifference += 0.5;
	this->Shift += this->ShiftDifference / 8.0;

	if (this->CurrentItemsOrigin.GetY() > this->TopLimit) {
		this->ShiftDifference = this->ShiftDifference / 1.1;
		this->Shift = this->Shift / 1.04;
	}
	else {
		if ((this->CurrentItemsOrigin.GetY() + this->Items.size() * KeyboardKey::Origin.GetX() * 0.4) < this->BottomLimit) {
			this->ShiftDifference = this->ShiftDifference / 1.1;
			double ShiftLimt = -((this->Items.size() * KeyboardKey::Origin.GetX() * 0.4) - (GameWindow->getSize().y - KeyboardKey::Origin.GetY() * 2));
			this->Shift = (this->Shift + ShiftLimt * 0.04) / 1.04;
		}
	}
}

//--------------------------------------- Do Events ------------------------------------//

void ControlsFrame::DoEvents() {
	Frame::BackgroundSound.setVolume(MT::Shift(Frame::BackgroundSound.getVolume(), LOW, 15));
	if (this->FrameState == Activating)this->FadeIn();
	if (this->FrameState == Deactivating)this->FadeOut();
	if (this->FrameState == Active) {
		this->Scroll();

		this->CurrentItemsOrigin = Point(this->CurrentItemsOrigin.GetX(), this->ItemsReferenceOrigin.GetY() + this->Shift);

		bool HandCursor = false;

		for (int i = 0; i < this->Keys.size(); i++) {
			for (int j = 0; j < this->Keys[i].size(); j++) {
				Point TopLeftCorner(this->Keys[i][j]->GetX(), this->Keys[i][j]->GetY());
				Point BottomRightCorner(this->Keys[i][j]->GetX() + this->Keys[i][j]->GetWidth(), this->Keys[i][j]->GetY() + this->Keys[i][j]->GetHeight());
				Shape* KeyboardBoundaries = new Rectangle(TopLeftCorner, BottomRightCorner);

				Point CursorPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
				if (KeyboardBoundaries->ContainsPoint(CursorPosition)) {
					HandCursor = true;
					goto ExitLoop;
				}

				delete KeyboardBoundaries;
			}
		}

		for (int i = 0; i < this->Items.size(); i++) {
			Point TopLeftCorner(this->Items[i].GetX(), this->Items[i].GetY());
			Point BottomRightCorner(this->Items[i].GetX() + this->Items[i].GetWidth(), this->Items[i].GetY() + this->Items[i].GetHeight());
			Shape* ItemBoundaries = new Rectangle(TopLeftCorner, BottomRightCorner);

			Point CursorPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
			if (ItemBoundaries->ContainsPoint(CursorPosition)) {
				HandCursor = true;
				goto ExitLoop;
			}

			delete ItemBoundaries;
		}

		if(this->Back.MouseOver())HandCursor = true;

		ExitLoop:

		if(HandCursor)GameWindow->setMouseCursor(HAND);
		else GameWindow->setMouseCursor(ARROW);
		for (int i = 0; i < this->Keys.size(); i++) {
			for (int j = 0; j < this->Keys[i].size(); j++) {
				this->Keys[i][j]->Refresh();
			}
		}
		for (int i = 0; i < this->Items.size(); i++)this->Items[i].Refresh();

		this->Back.Refresh();

		if (this->Timer != NULL && this->Timer->getElapsedTime().asMilliseconds() >= this->TimerDuration) {
			delete this->Timer;
			this->Timer = NULL;
		}

		if (this->Timer == NULL) {
			this->ErrorMessage.setFillColor(MT::Shift(this->ErrorMessage.getFillColor(), TRANSPARENT, SLOW));
		}
		else {
			this->ErrorMessage.setFillColor(MT::Shift(this->ErrorMessage.getFillColor(), ERROR_COLOR, FAST));
		}
	}
}

//--------------------------------------- Do Action ------------------------------------//

void ControlsFrame::DoAction(sf::Event& CurrentEvent) {
	if (this->FrameState == Active) {
		bool MouseDown = false;

		if (CurrentEvent.type == sf::Event::MouseWheelScrolled) {
			this->ShiftDifference += (CurrentEvent.mouseWheelScroll.delta) * 10;
		}
		else if (CurrentEvent.type == sf::Event::Closed) {
			this->FrameState = Deactivating;
			this->FadeOut();
			this->NavigateTo = MAIN_FRAME;
		}
		else if ((CurrentEvent.type == sf::Event::KeyReleased) && CurrentEvent.key.code == sf::Keyboard::Escape) {
			this->FrameState = Deactivating;
			this->FadeOut();
			this->NavigateTo = MAIN_FRAME;
		}
		else if (CurrentEvent.type == sf::Event::MouseButtonReleased && this->Back.MouseOver() && CurrentEvent.key.code == sf::Mouse::Left) {
			this->FrameState = Deactivating;
			this->FadeOut();
			this->NavigateTo = MAIN_FRAME;
		}
		else if (CurrentEvent.type == sf::Event::KeyPressed) {
			std::string KeyID = "";

			KeyID += std::to_string(CurrentEvent.type);
			KeyID += ":";
			KeyID += std::to_string(CurrentEvent.key.code);

			for (int i = 0; i < this->Keys.size(); i++) {
				for (int j = 0; j < this->Keys[i].size(); j++) {
					if (this->Keys[i][j]->GetID() == KeyID) {
						this->Keys[i][j]->Select(-1);
						goto ExitSearhcLoop;
					}
				}
			}
			// This Code Will Be Executed Only If We Did Not Get Out Of The Loop
			if (CurrentEvent.key.code != sf::Keyboard::Escape) {
				if (this->Timer != NULL)delete this->Timer;
				this->Timer = new sf::Clock();
			}
			ExitSearhcLoop:;
		}
	}
}

//---------------------------------------- FadeIn -------------------------------------//

void ControlsFrame::FadeIn() {
	this->BlockRectangle.setFillColor(MT::Shift(this->BlockRectangle.getFillColor(), TRANSPARENT, NORMAL));
	if (this->BlockRectangle.getFillColor() == TRANSPARENT) {
		this->FrameState = Active;
	}
}

//---------------------------------------- FadeOut -------------------------------------//

void ControlsFrame::FadeOut() {
	this->BlockRectangle.setFillColor(MT::Shift(this->BlockRectangle.getFillColor(), BACKGROUND, NORMAL));
	if (this->BlockRectangle.getFillColor() == BACKGROUND) {
		this->FrameState = Inactive;
	}
}

//---------------------------------------- Unselect -------------------------------------//

void ControlsFrame::ClearSelection() {
	for (int i = 0; i < this->Keys.size(); i++) {
		for (int j = 0; j < this->Keys[i].size(); j++) {
			this->Keys[i][j]->UnSelect();
		}
	}
}
	
