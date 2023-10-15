#pragma once
#include <thread>

#include "StartFrame.h"
#include "Methods.h"
#include "Rectangle.h"

int StartFrame::DifficultyTimerDuration = 15; // 15 Seconds

//------------------------------------ Constructor ------------------------------------//

StartFrame::StartFrame() : Frame() {

	/* Block Rectangle */
	this->BlockRectangle.setPosition(0, 0);
	this->BlockRectangle.setSize(sf::Vector2f(GameWindow->getSize().x, GameWindow->getSize().y));
	this->BlockRectangle.setFillColor(BACKGROUND);

	/* Data */
	std::vector<std::string> Data = File::Read("../GameData/Settings/Controls.txt");
	
	this->Move = UserInput(Data[0], true);
	this->PositiveShift = UserInput(Data[1], true);
	this->NegativeShift = UserInput(Data[2], true);
	this->Upgrade = UserInput(Data[3], false);
	this->MoveSelectionUp = UserInput(Data[4], false);
	this->MoveSelectionDown = UserInput(Data[5], false);


	/* Menu */
	this->MenuBackground.setSize(sf::Vector2f(280, GameWindow->getSize().y));
	this->MenuBackground.setPosition(GameWindow->getSize().x - this->MenuBackground.getGlobalBounds().width, 0);
	this->MenuBackground.setFillColor(SECONDARY_BACKGROUND);

	/* Score */
	this->CurrentScore = this->ActualScore = 0;
	this->ScoreLabel = sf::Text("Score: 00000000", FONT, (H2 + H3) / 2);
	this->ScoreLabel.setFillColor(COLOR);
	this->ScoreLabel.setPosition(this->MenuBackground.getGlobalBounds().left + (this->MenuBackground.getGlobalBounds().width - this->ScoreLabel.getGlobalBounds().width) / 2.0, 0);

	/* Fixed Items */
	this->ItemHeight = 80;
	sf::Color BackgroundColor = this->MenuBackground.getFillColor();

	HealthItem * Health = new HealthItem(Dimension(this->MenuBackground.getGlobalBounds().width * 0.6, 18), "Health", Point(this->MenuBackground.getGlobalBounds().left, this->ScoreLabel.getGlobalBounds().height * 3), Dimension(this->MenuBackground.getGlobalBounds().width, ItemHeight), BackgroundColor);
	ShiftItem * Shift = new ShiftItem(Dimension(this->MenuBackground.getGlobalBounds().width * 0.6, 18), "Shift", Point(this->MenuBackground.getGlobalBounds().left, this->ScoreLabel.getGlobalBounds().height * 3 + ItemHeight), Dimension(this->MenuBackground.getGlobalBounds().width, ItemHeight), BackgroundColor);

	this->MenuItems.push_back(Health);
	this->MenuItems.push_back(Shift);

	/* Player */

	this->Player = new Magnet(this->MenuBackground.getGlobalBounds().width, Health->GetBar(), Shift->GetBar(), Move, PositiveShift, NegativeShift, this->ActualScore);

	/* Upgradable Items */

	UpgradeItem * HealthUpgrade = new UpgradeItem(Upgrade, 0, this->Player, "Armour", Point(this->MenuBackground.getGlobalBounds().left, this->MenuBackground.getGlobalBounds().height - ItemHeight), Dimension(this->MenuBackground.getGlobalBounds().width, ItemHeight));
	UpgradeItem * RegerenationUpgrade = new UpgradeItem(Upgrade, 1, this->Player, "Regen Speed", Point(this->MenuBackground.getGlobalBounds().left, this->MenuBackground.getGlobalBounds().height - 2 * ItemHeight), Dimension(this->MenuBackground.getGlobalBounds().width, ItemHeight));
	UpgradeItem * ShiftUpgrade = new UpgradeItem(Upgrade, 2, this->Player, "Magnet Power", Point(this->MenuBackground.getGlobalBounds().left, this->MenuBackground.getGlobalBounds().height - 3 * ItemHeight), Dimension(this->MenuBackground.getGlobalBounds().width, ItemHeight));
	UpgradeItem * ShiftSpeed = new UpgradeItem(Upgrade, 3, this->Player, "Shift Speed", Point(this->MenuBackground.getGlobalBounds().left, this->MenuBackground.getGlobalBounds().height - 4 * ItemHeight), Dimension(this->MenuBackground.getGlobalBounds().width, ItemHeight));
	UpgradeItem * StunnUpgrade = new UpgradeItem(Upgrade, 4, this->Player, "Stunn Duration", Point(this->MenuBackground.getGlobalBounds().left, this->MenuBackground.getGlobalBounds().height - 5 * ItemHeight), Dimension(this->MenuBackground.getGlobalBounds().width, ItemHeight));
	
	this->MenuItems.push_back(HealthUpgrade);
	this->MenuItems.push_back(RegerenationUpgrade);
	this->MenuItems.push_back(ShiftUpgrade);
	this->MenuItems.push_back(ShiftSpeed);
	this->MenuItems.push_back(StunnUpgrade);

	/* Game Over Objects */

	this->GameOverBackground = sf::RectangleShape(sf::Vector2f(GameWindow->getSize().x, GameWindow->getSize().y));
	this->GameOverBackground.setFillColor(TRANSPARENT);
	this->GameOverBackground.setPosition(0, 0);
	
	double X, Y;
	this->GameOverText = sf::Text("Game Over", FONT, H1);
	this->GameOverText.setFillColor(TRANSPARENT);

	this->FinalScoreText = sf::Text(MT::Text(this->ActualScore, 8), FONT, H2);
	this->FinalScoreText.setFillColor(TRANSPARENT);

	X = (GameWindow->getSize().x - this->GameOverText.getGlobalBounds().width) / 2.0;
	Y = (GameWindow->getSize().y - this->GameOverText.getGlobalBounds().height - this->FinalScoreText.getGlobalBounds().height) / 2.0 - 15;

	this->GameOverText.setPosition(X, Y);

	X = (GameWindow->getSize().x - this->FinalScoreText.getGlobalBounds().width) / 2.0;
	Y += 30 + this->GameOverText.getGlobalBounds().height;

	this->FinalScoreText.setPosition(X, Y);

	/* Bots */
	Bot::Reset();
}

//------------------------------------- Destructor ------------------------------------//

StartFrame::~StartFrame() {
	delete this->Player;
	for (int i = 0; i < this->Blocks.size(); i++) {
		delete this->Blocks[i];
	}
	for (int i = 0; i < this->Bots.size(); i++) {
		delete this->Bots[i];
	}
}

//-------------------------------------- DrawFrame ------------------------------------//

void StartFrame::DrawFrame() {
	GameWindow->clear();
	this->Player->Draw();

	for (int i = 0; i < this->Blocks.size(); i++) {
		this->Blocks[i]->Draw();
	}

	GameWindow->draw(this->MenuBackground);
	GameWindow->draw(this->ScoreLabel);

	for (int i = 0; i < this->MenuItems.size(); i++) {
		this->MenuItems[i]->Draw();
	}

	for (int i = 0; i < this->Bots.size(); i++) {
		this->Bots[i]->Draw();
	}

	GameWindow->draw(this->GameOverBackground);
	GameWindow->draw(this->GameOverText);
	GameWindow->draw(this->FinalScoreText);

	GameWindow->draw(this->BlockRectangle);

	GameWindow->display();
}

//--------------------------------------- Do Events ------------------------------------//

void StartFrame::DoEvents() {
	Frame::BackgroundSound.setVolume(MT::Shift(Frame::BackgroundSound.getVolume(), HIGH, 15));
	if (this->FrameState == Activating)this->FadeIn();
	if (this->FrameState == Deactivating)this->FadeOut();
	if (this->FrameState == Active) {
		/* Bots */

		if (this->DifficultyTimer.getElapsedTime().asSeconds() >= StartFrame::DifficultyTimerDuration) {
			this->DifficultyTimer.restart();
			Bot::MakeBotWiser();
		}

		if (!Bot::InCooldown()) {
			Bot* NewBot = new Bot(this->Player, this->Blocks, this->ActualScore );
			this->Bots.push_back(NewBot);
		}

		for (int i = this->Bots.size() - 1; i >= 0; i--) {
			if (this->Bots[i]->IsOutOfBounds() || !this->Bots[i]->IsAlive()) {
				delete this->Bots[i];
				this->Bots.erase(this->Bots.begin() + i);
			}
			else this->Bots[i]->Refresh();
		}

		/* Blocks */

		if (!Block::InCooldown()) {
			Block* NewBlock = new Block(Iron);
			this->Blocks.push_back(NewBlock);
		}

		std::vector<int> Index;
		for (int i = 0; i < this->Blocks.size(); i++) {
			if (this->Blocks[i]->IsOutOfBounds() || this->Blocks[i]->GetState() == Disabled) {
				Index.push_back(i);
			}
			if (this->Blocks[i]->GetType() == Iron && (this->Blocks[i]->GetState() == FadingOut || this->Blocks[i]->GetState() == Disabled)) {
				if (!this->Blocks[i]->IsAlternativeBlockCreated()) {
					this->Blocks[i]->CreateAlternativeBlock();
					this->Blocks[i]->GetMergeBlock()->CreateAlternativeBlock();
					this->Blocks.push_back(new Block(Copper, this->Blocks[i]->GetPosition(), this->Blocks[i]->GetRotation(), this->Player));
				}
			}
			else {
					if (this->Blocks[i]->GetState() == CopperDestruction && !this->Blocks[i]->IsAlternativeBlockCreated()) {
						this->Blocks[i]->CreateAlternativeBlock();
						this->Blocks.push_back(new Block(Iron, this->Blocks[i]->GetPosition(), this->Blocks[i]->GetRotation(), NULL));
					}
			}
		}
		for (int i = Index.size() - 1; i >= 0; i--) {
			if (this->Blocks[Index[i]]->GetMergeBlock() != NULL)this->Blocks[Index[i]]->GetMergeBlock()->SetMergeBlock(NULL);
			delete this->Blocks[Index[i]];
			this->Blocks.erase(this->Blocks.begin() + Index[i]);
		}

		/* Selection */
		
		this->MoveSelectionDown.CheckState();
		this->MoveSelectionUp.CheckState();

		if (this->MoveSelectionDown.IsActive()) {
			this->MoveItemSelectionDown();
		}
		if (this->MoveSelectionUp.IsActive()) {
			this->MoveItemSelectionUp();
		}

		this->Player->Refresh();

		for (int i = 0; i < this->MenuItems.size(); i++) {
			this->MenuItems[i]->Refresh();
		}

		/* Collisions */

		std::vector<bool> Collisions(this->Blocks.size(), false);
		for (int i = 0; i < this->Blocks.size(); i++) {
			for (int j = i + 1; j < this->Blocks.size(); j++) {
				if (this->Blocks[i]->GetType() == Iron && this->Blocks[j]->GetType() == Iron && this->Blocks[i]->GetState() == Default && this->Blocks[j]->GetState() == Default && this->Blocks[i]->IntersectsWith(this->Blocks[j])) {

					this->Blocks[i]->AddCollisionBlock(this->Blocks[j]);
					this->Blocks[j]->AddCollisionBlock(this->Blocks[i]);

					if (!this->Blocks[i]->InCollisionWith(this->Blocks[j])) {
						this->Blocks[i]->BounceOff(this->Blocks[j]);
						Collisions[i] = Collisions[j] = true;
					}
					else {
						this->Blocks[i]->MoveAwayFrom(this->Blocks[j]);
					}
				}
			}
		}
		for (int i = 0; i < Collisions.size(); i++)if (!Collisions[i])this->Blocks[i]->ResetCollisionBlock();

		/* Player Intersection */

		Circle PlayerBoundaries = this->Player->GetBoundaries();
		for (int i = 0; i < this->Blocks.size(); i++) {
			if (this->Blocks[i]->GetType() == Copper)continue;
			RotatedRectangle BlockBoundaires = this->Blocks[i]->GetBoundaries();
			std::vector<Point> Points;
			Points.push_back(BlockBoundaires.GetCorner(0));
			Points.push_back(BlockBoundaires.GetCorner(1));
			Points.push_back(BlockBoundaires.GetCorner(2));
			Points.push_back(BlockBoundaires.GetCorner(3));
			Points.push_back(MT::MidPoint(Points[0], Points[1]));
			Points.push_back(MT::MidPoint(Points[0], Points[2]));
			Points.push_back(MT::MidPoint(Points[0], Points[3]));
			Points.push_back(MT::MidPoint(Points[1], Points[2]));
			Points.push_back(MT::MidPoint(Points[1], Points[3]));
			Points.push_back(MT::MidPoint(Points[2], Points[3]));
			
			for (int i = 0; i < Points.size(); i++) {
				if (PlayerBoundaries.ContainsPoint(Points[i])) {
					this->Player->StartHidingTimer();
					goto SkipTimerReset;
				}
			}

		}
		this->Player->ResetHidingTimer();
		SkipTimerReset:;

		for (Block* CurrentBlock : this->Blocks) {
			Point MagnetPosition(this->Player->GetX(), this->Player->GetY());
			double CurrentFieldStrength = this->Player->GetFieldStrength();
			CurrentBlock->InteractWithMagnet(MagnetPosition, CurrentFieldStrength);
			CurrentBlock->Refresh();
		}

		Point TopLeftCorner(this->MenuBackground.getGlobalBounds().left, this->MenuBackground.getGlobalBounds().height - 5 * this->ItemHeight);
		Point BottomRightCorner(this->MenuBackground.getGlobalBounds().left + this->MenuBackground.getGlobalBounds().width, this->MenuBackground.getGlobalBounds().height);
		Point MousePosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
		
		Shape* Boundaries = new Rectangle(TopLeftCorner, BottomRightCorner);

		if (Boundaries->ContainsPoint(MousePosition)) {
			GameWindow->setMouseCursor(HAND);
		}
		else {
			GameWindow->setMouseCursor(ARROW);
		}

		delete Boundaries;

		if (this->Player->IsDead()) {
			this->EndGame();
		}

	}
	if (this->FrameState == Paused) {
		this->GameOverBackground.setFillColor(MT::Shift(this->GameOverBackground.getFillColor(), sf::Color(0, 0, 0, 150), SLOW));
		this->GameOverText.setFillColor(MT::Shift(this->GameOverText.getFillColor(), ERROR_COLOR, SLOW));
		this->FinalScoreText.setFillColor(MT::Shift(this->FinalScoreText.getFillColor(), ERROR_COLOR, SLOW));
	}

	this->CurrentScore = MT::Shift(this->CurrentScore, this->ActualScore, 8);
	if(this->CurrentScore < this->ActualScore)this->ScoreLabel.setString("Score: " + MT::Text(MT::RoundUp(this->CurrentScore), 8));
	else this->ScoreLabel.setString("Score: " + MT::Text(MT::RoundDown(this->CurrentScore), 8));
}

//--------------------------------------- Do Action ------------------------------------//

void StartFrame::DoAction(sf::Event& CurrentEvent) {
	if (this->FrameState == Active || this->FrameState == Paused) {
		bool MouseDown = false;
		if (CurrentEvent.type == sf::Event::Closed) {
			this->FrameState = Deactivating;
			this->FadeOut();
			this->NavigateTo = MAIN_FRAME;
		}
		if ((CurrentEvent.type == sf::Event::KeyReleased) && (CurrentEvent.key.code == sf::Keyboard::Escape)) {
			this->FrameState = Deactivating;
			this->FadeOut();
			this->NavigateTo = MAIN_FRAME;
		}

		if (this->FrameState == Active && CurrentEvent.type == sf::Event::MouseWheelScrolled) {
			int Scroll = (CurrentEvent.mouseWheelScroll.delta);
			while (Scroll != 0) {
				if(Scroll > 0)this->MoveItemSelectionUp();
				else this->MoveItemSelectionDown();
				Scroll /= 10;
			}
		}
	}
}

//---------------------------------------- FadeIn -------------------------------------//

void StartFrame::FadeIn() {
	this->BlockRectangle.setFillColor(MT::Shift(this->BlockRectangle.getFillColor(), TRANSPARENT, NORMAL));
	if (this->BlockRectangle.getFillColor() == TRANSPARENT) {
		this->FrameState = Active;
		this->DifficultyTimer.restart();
	}
}

//---------------------------------------- FadeOut -------------------------------------//

void StartFrame::FadeOut() {
	this->BlockRectangle.setFillColor(MT::Shift(this->BlockRectangle.getFillColor(), BACKGROUND, NORMAL));
	if (this->BlockRectangle.getFillColor() == BACKGROUND) {
		this->FrameState = Inactive;
	}

}

//-------------------------------- Move Item Selection Up -----------------------------//

void StartFrame::MoveItemSelectionUp() {
	UpgradeItem::SelectedIndex++;
	if (UpgradeItem::SelectedIndex > (this->MenuItems.size() - 3))UpgradeItem::SelectedIndex = 0;
}

//------------------------------- Move Item Selection Down ----------------------------//

void StartFrame::MoveItemSelectionDown() {
	UpgradeItem::SelectedIndex--;
	if (UpgradeItem::SelectedIndex < 0)UpgradeItem::SelectedIndex = (this->MenuItems.size() - 3);
}

//--------------------------------------- End Game ------------------------------------//

void StartFrame::EndGame() {
	this->FinalScoreText.setString(MT::Text(this->ActualScore, 8));
	this->FrameState = Paused;
}