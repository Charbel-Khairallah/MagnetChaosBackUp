#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "State.h"
#include "Navigation.h"
#include "Config.h"
#include "Video.h"

#define GameWindow Frame::RenderWindow

class Frame {
private:
	static sf::SoundBuffer BackgroundSoundBuffer;
	static sf::SoundBuffer RobotDamageSoundBuffer;
	static sf::SoundBuffer SelectionSoundBuffer;
	static sf::SoundBuffer StunnSoundBuffer;
	static sf::SoundBuffer BlockCollisionSoundBuffer;

protected:
	State FrameState;
	Navigation NavigateTo;
	static bool Configured;

public:
	static sf::RenderWindow * RenderWindow;
	static void InitializeFrame();
	static Frame * CreateNewFrame(Navigation NavigateTo);

	static sf::Sound BackgroundSound;
	static sf::Sound RobotDamageSound;
	static sf::Sound SelectionSound;
	static sf::Sound StunnSound;
	static sf::Sound BlockCollisionSound;

	virtual ~Frame();
	Frame();
	void Activate();
	void Deactivate();
	State GetState();
	Navigation GetNavigation();

	void ResetConfiguration();
	virtual void DrawFrame() = NULL;
	virtual void DoAction(sf::Event& CurrentEvent) = NULL;
	virtual void DoEvents() = NULL;
	virtual void FadeIn() = NULL;
	virtual void FadeOut() = NULL;
};

