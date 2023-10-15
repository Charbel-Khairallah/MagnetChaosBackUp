#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "MainFrame.h"
#include "ControlsFrame.h"
#include "TutorialFrame.h"
#include "StartFrame.h"

int main() {

    std::cout << "Test" << std::endl;

    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    Frame::InitializeFrame();
    Frame * WindowFrame = new MainFrame();
    while (GameWindow->isOpen())
    {
        sf::Event CurrentEvent;
        while (GameWindow->pollEvent(CurrentEvent))
        {
            WindowFrame->DoAction(CurrentEvent);
        }

        WindowFrame->DoEvents();
        WindowFrame->DrawFrame();

        if (WindowFrame->GetState() == Inactive) {
            Navigation NavigateTo = WindowFrame->GetNavigation();
            delete WindowFrame;
            WindowFrame = Frame::CreateNewFrame(NavigateTo);
        }
    }

	return 0;
}