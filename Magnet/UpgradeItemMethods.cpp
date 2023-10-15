#pragma Once
#include "UpgradeItem.h"
#include "Rectangle.h"

int UpgradeItem::SelectedIndex = 4;

//------------------------------------ Constructor ------------------------------------//

UpgradeItem::UpgradeItem(UserInput Upgrade, int Index, Magnet * Player, std::string LabelText, Point Origin, Dimension Size) : MenuItem(LabelText, Origin, Size) {
	this->MaxLevel = 5;
	this->Index = Index;
	this->Player = Player;
	this->LevelValue = 1;

	this->Origin = Origin;
	this->Size = Size;

	this->UpgradeInput = Upgrade;

	this->Pressed = false;

	double X, Y, HorizontalShift, VerticalShift;

	this->LevelBackground = sf::CircleShape(14);
	this->LevelBackground.setFillColor(COLOR);

	X = Origin.GetX() + Size.GetWidth() - Size.GetHeight() / 2.0;
	Y = Origin.GetY() + (Size.GetHeight() - this->LevelBackground.getGlobalBounds().height) / 2.0;
	this->LevelBackground.setPosition(X, Y);

	this->Level = sf::Text(MT::ShortRoman(this->LevelValue), FONT, H3);
	this->Level.setFillColor(BACKGROUND);
	HorizontalShift = (this->LevelBackground.getRadius() * 2 - this->Level.getGlobalBounds().width) / 2.0;
	VerticalShift = (this->LevelBackground.getRadius() - this->Level.getGlobalBounds().height) / 2.0;
	this->Level.setPosition(X + HorizontalShift, Y + VerticalShift);

	/* Borders */
	int Thickness = 2;

	this->TopBorder = sf::RectangleShape(sf::Vector2f(Size.GetWidth(), Thickness));
	this->TopBorder.setFillColor(TRANSPARENT);
	this->TopBorder.setPosition(Origin.GetX(), Origin.GetY());

	this->BottomBorder = sf::RectangleShape(sf::Vector2f(Size.GetWidth(), Thickness));
	this->BottomBorder.setFillColor(TRANSPARENT);
	this->BottomBorder.setPosition(Origin.GetX(), Origin.GetY() + Size.GetHeight() - Thickness);

	this->LeftBorder = sf::RectangleShape(sf::Vector2f(Thickness, Size.GetHeight()));
	this->LeftBorder.setFillColor(TRANSPARENT);
	this->LeftBorder.setPosition(Origin.GetX(), Origin.GetY());

	this->RightBorder = sf::RectangleShape(sf::Vector2f(Thickness, Size.GetHeight()));
	this->RightBorder.setFillColor(TRANSPARENT);
	this->RightBorder.setPosition(Origin.GetX() + Size.GetWidth() - Thickness, Origin.GetY());
}

//------------------------------------ Destructor ------------------------------------//

UpgradeItem::~UpgradeItem() {
	
}

//--------------------------------------- Draw ---------------------------------------//

void UpgradeItem::Draw() {
	this->DrawBase();

	GameWindow->draw(this->LevelBackground);
	GameWindow->draw(this->Level);

	GameWindow->draw(this->TopBorder);
	GameWindow->draw(this->BottomBorder);
	GameWindow->draw(this->LeftBorder);
	GameWindow->draw(this->RightBorder);
}

//-------------------------------------- Refresh --------------------------------------//

void UpgradeItem::Refresh() {
	/* Upgrade Circle Background */
	if (this->LevelValue < this->MaxLevel && this->Player->GetAvailableUpgrades() > 0) {
		this->LevelBackground.setFillColor(MT::Shift(this->LevelBackground.getFillColor(), HOVER_COLOR, SLOW));
		this->Label.setFillColor(MT::Shift(this->Label.getFillColor(), HOVER_COLOR, SLOW));
	}
	else {
		this->LevelBackground.setFillColor(MT::Shift(this->LevelBackground.getFillColor(), DISABLED_COLOR, SLOW));
		this->Label.setFillColor(MT::Shift(this->Label.getFillColor(), DISABLED_COLOR, SLOW));
	}

	/* Check For User Upgrade */
	this->UpgradeInput.CheckState();
	if (this->UpgradeInput.IsActive() && UpgradeItem::SelectedIndex == this->Index)this->Upgrade();

	/* Check For Mouse Over */
	Shape * Boundaries = new Rectangle(this->Origin, this->Origin + this->Size);
	Point MousePosition = Point(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

	sf::Color NewColor = TRANSPARENT;
	if (Boundaries->ContainsPoint(MousePosition)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			NewColor = PRESSED_COLOR;
			this->Pressed = true;
		}
		else {
			NewColor = HOVER_COLOR;
			if (this->Pressed) {
				UpgradeItem::SelectedIndex = this->Index;
			}
			this->Pressed = false;
		}
	}
	else {
		if (UpgradeItem::SelectedIndex == this->Index) {
			NewColor = PRESSED_COLOR;
		}
		this->Pressed = false;
	}

	this->TopBorder.setFillColor(MT::Shift(this->TopBorder.getFillColor(), NewColor, SLOW));
	this->BottomBorder.setFillColor(MT::Shift(this->BottomBorder.getFillColor(), NewColor, SLOW));
	this->LeftBorder.setFillColor(MT::Shift(this->LeftBorder.getFillColor(), NewColor, SLOW));
	this->RightBorder.setFillColor(MT::Shift(this->RightBorder.getFillColor(), NewColor, SLOW));

	delete Boundaries;
}

//-------------------------------------- Upgrade --------------------------------------//

void UpgradeItem::Upgrade() {
	if (this->LevelValue < this->MaxLevel && this->Player->GetAvailableUpgrades() > 0) {
		this->LevelValue++;
		this->Level.setString(MT::ShortRoman(this->LevelValue));

		double X = this->LevelBackground.getGlobalBounds().left;
		double Y = this->LevelBackground.getGlobalBounds().top;
		double HorizontalShift = (this->LevelBackground.getRadius() * 2 - this->Level.getGlobalBounds().width) / 2.0;
		double VerticalShift = (this->LevelBackground.getRadius() - this->Level.getGlobalBounds().height) / 2.0;
		this->Level.setPosition(X + HorizontalShift, Y + VerticalShift);
	
		switch (this->Index)
		{
			case 0: {
				this->Player->UpgradeArmour();
				break;
			}
			case 1: {
				this->Player->UpgradeRegenerationSpeed();
				break;
			}
			case 2: {
				this->Player->UpgradePower();
				break;
			}
			case 3: {
				this->Player->UpgradeShiftSpeed();
				break;
			}
			case 4: {
				this->Player->UpgradeStunnDuration();
				break;
			}
		}
	}
}
