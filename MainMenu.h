#pragma once
#include <SFML/Graphics.hpp>

/*
* CHOOSE LEVEL
* SHOW LEADERBOARD
* SETTINGS
* EXIT
*/

const int NUM_OF_BUTTONS = 4;
class MainMenu
{

protected:
    int selectedButton = 0;
    sf::Image menuBackground;
    sf::Text menuButton[NUM_OF_BUTTONS];
    sf::Font menuFont;


public:

    int getSelectedButton(sf::RenderWindow& window);
    bool checkIfPressed(sf::RenderWindow& window, int index);
    void drawMenu(sf::RenderWindow& window);
    MainMenu(int width, int height);
    ~MainMenu();

};

