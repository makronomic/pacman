#pragma once
#include <SFML/Graphics.hpp>
//#include "SubMenus.h"

/*
* CHOOSE LEVEL
* SHOW LEADERBOARD
* SETTINGS
* EXIT
*/
const int NUM_OF_BUTTONS_MAINMENU = 4;


enum MenuState {
    MainMenuState,
    LevelSelectionMenuState,
    LeaderboardMenuState,
    SettingsMenuState,
};

static MenuState currentMenuState;

class MainMenu
{

protected:
    int selectedButton = 0;
    sf::Image menuBackground;
    sf::Text menuButton[NUM_OF_BUTTONS_MAINMENU];
    sf::Font menuFont;
public:

    virtual int getSelectedButton(sf::RenderWindow& window);
    bool checkIfPressed(sf::RenderWindow& window, sf::Text menuButton);
    void drawMenu(sf::RenderWindow& window);
    MainMenu(int numOfButtons);
    MainMenu(int width, int height);
    ~MainMenu();

};


