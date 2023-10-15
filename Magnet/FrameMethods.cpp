#pragma once
#include "Frame.h"
#include <iostream>
#include "ControlsFrame.h"
#include "TutorialFrame.h"
#include "StartFrame.h"
#include "MainFrame.h"

bool Frame::Configured = false;

sf::SoundBuffer Frame::BackgroundSoundBuffer;
sf::SoundBuffer Frame::RobotDamageSoundBuffer;
sf::SoundBuffer Frame::SelectionSoundBuffer;
sf::SoundBuffer Frame::StunnSoundBuffer;
sf::SoundBuffer Frame::BlockCollisionSoundBuffer;

sf::Sound Frame::BackgroundSound;
sf::Sound Frame::RobotDamageSound;
sf::Sound Frame::SelectionSound;
sf::Sound Frame::StunnSound;
sf::Sound Frame::BlockCollisionSound;

sf::RenderWindow * Frame::RenderWindow = NULL;

//---------------------------------- InitializeFrame ----------------------------------//

void Frame::InitializeFrame() {
    /* Random */
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    /* Sounds */
    if (!Frame::BackgroundSoundBuffer.loadFromFile("../GameData/Sounds/BackgroundAudio.wav")) {
        std::cout << "Could Not Load Background Sound." << std::endl;
    }
    else {
        Frame::BackgroundSound.setBuffer(BackgroundSoundBuffer);
        Frame::BackgroundSound.setLoop(true);
        Frame::BackgroundSound.setVolume(MUTE);
        Frame::BackgroundSound.play();
    }

    if (!Frame::SelectionSoundBuffer.loadFromFile("../GameData/Sounds/Selection.wav")) {
        std::cout<<"Could Not Load Selection Sound."<<std::endl;
    }
    else {
        Frame::SelectionSound.setBuffer(SelectionSoundBuffer);
        Frame::SelectionSound.setLoop(false);
        Frame::SelectionSound.setVolume(MID);
    }

    if (!Frame::RobotDamageSoundBuffer.loadFromFile("../GameData/Sounds/RobotDamage.wav")) {
        std::cout << "Could Not Load Selection Sound." << std::endl;
    }
    else {
        Frame::RobotDamageSound.setBuffer(RobotDamageSoundBuffer);
        Frame::RobotDamageSound.setLoop(false);
        Frame::RobotDamageSound.setVolume(MID);
    }

    if (!Frame::StunnSoundBuffer.loadFromFile("../GameData/Sounds/Stunn.wav")) {
        std::cout << "Could Not Load Stunn Sound." << std::endl;
    }
    else {
        Frame::StunnSound.setBuffer(StunnSoundBuffer);
        Frame::StunnSound.setLoop(false);
        Frame::StunnSound.setVolume(LOUD);
    }

    if (!Frame::BlockCollisionSoundBuffer.loadFromFile("../GameData/Sounds/BlockCollision.wav")) {
        std::cout << "Could Not Load Block Collision Sound." << std::endl;
    }
    else {
        Frame::BlockCollisionSound.setBuffer(BlockCollisionSoundBuffer);
        Frame::BlockCollisionSound.setLoop(false);
        Frame::BlockCollisionSound.setVolume(HIGH);
    }


    /* Actual Frame */
    sf::ContextSettings Settings;
    Settings.antialiasingLevel = 8;
    GameWindow = new sf::RenderWindow(sf::VideoMode(1000, 700), "", sf::Style::Fullscreen, Settings);

    GameWindow->setFramerateLimit(90);
}

//------------------------------------ Constructor ------------------------------------//

Frame::Frame() {
	this->FrameState = State::Activating;
	this->NavigateTo = NONE;
    GameWindow->setMouseCursor(ARROW);
	
	if (!Frame::Configured) {
		Frame::Configured = true;
		this->ResetConfiguration();
	}
}

//------------------------------------- Destructor -------------------------------------//

Frame::~Frame() {

}

//--------------------------------------- Activate --------------------------------------//

void Frame::Activate() {
	this->FrameState = State::Activating;
	this->FrameState = State::Active;
}

//-------------------------------------- Deactivate ------------------------------------//

void Frame::Deactivate() {
	this->FrameState = State::Deactivating;
	this->FrameState = State::Inactive;
}

//--------------------------------------- GetState -------------------------------------//

State Frame::GetState() {
	return this->FrameState;
}

//------------------------------------- GetNavigation ----------------------------------//

Navigation Frame::GetNavigation() {
	return this->NavigateTo;
}

//---------------------------------- ResetConfiguration --------------------------------//

void Frame::ResetConfiguration() {
	Config::Instance().Init();
}

//----------------------------------- Create New Window --------------------------------//

Frame* Frame::CreateNewFrame(Navigation NavigateTo) {
    switch (NavigateTo) {
        case NONE: {
            GameWindow->close();
            return NULL;
        }
        case MAIN_FRAME: {
            return new MainFrame();
        }
        case CONTROLS_FRAME: {
            return new ControlsFrame();
        }
        case TUTORIAL_FRAME: {
            return new TutorialFrame();
        }
        case START_FRAME: {
            return new StartFrame();
        }
        default: {
            GameWindow->close();
            return NULL;
        }
    }
}