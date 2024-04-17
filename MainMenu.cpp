#include "MainMenu.h"
#include <iostream>
#include <algorithm>

MainMenu::MainMenu(int width, int height)
{
    //load font
    if (!menuFont.loadFromFile("fonts/PAC-FONT.TTF"))
    {
        std::cout << "UNABLE TO LOAD FONT!";
    }

    //set all buttons to same font
    for (int i = 0; i < NUM_OF_BUTTONS; i++)
    {
        menuButton[i].setFont(menuFont);
    }


    //CHOOSE LEVEL BUTTON
    menuButton[0].setFillColor(sf::Color::Blue);
    menuButton[0].setString("CHOOSE LEVEL");
    menuButton[0].setPosition(sf::Vector2f(800, 350));

    //SHOW LEADERBOARD BUTTON
    menuButton[1].setFillColor(sf::Color::Yellow);
    menuButton[1].setString("SHOW LEADERBOARD");
    menuButton[1].setPosition(sf::Vector2f(800, 450));

    //SETTINGS BUTTON
    menuButton[2].setFillColor(sf::Color::Blue);
    menuButton[2].setString("SETTINGS");
    menuButton[2].setPosition(sf::Vector2f(800, 550));

    //EXIT BUTTON
    menuButton[3].setFillColor(sf::Color::Yellow);
    menuButton[3].setString("EXIT");
    menuButton[3].setPosition(sf::Vector2f(800, 650));
}


void MainMenu::drawMenu(sf::RenderWindow& window)
{
    for (int i = 0; i < NUM_OF_BUTTONS; i++)
    {
        window.draw(menuButton[i]);
    }
}


int MainMenu::getSelectedButton(sf::RenderWindow& window)
{
    for (int i = 0; i < NUM_OF_BUTTONS; i++)
    {
        if (checkIfPressed(window, i))
        {
            selectedButton = i;
            std::cout << "YOUR SELECTED BUTTON IS OF INDEX: " << selectedButton << std::endl;
        }
    }
    return selectedButton;
}

bool MainMenu::checkIfPressed(sf::RenderWindow& window, int index)
{

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    sf::FloatRect buttonBounds = menuButton[index].getGlobalBounds();

    //Checks if the mouse position is within the button bounds and the left mouse button is pressed
    bool isMouseInBounds = buttonBounds.contains(static_cast<sf::Vector2f>(mousePosition));
    bool isMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);


    return isMouseInBounds && isMouseButtonPressed;
}

MainMenu::~MainMenu()
{

}