#include "SubMenus.h"
#include <iostream>
#include <thread>
#include <chrono>
ChooseLevelMenu::ChooseLevelMenu(int width, int height) : MainMenu(3)
{
    currentMenuState = LevelSelectionMenuState;

    //CHOOSE LEVEL BUTTON
    menuButton[0].setFillColor(sf::Color::Blue);
    menuButton[0].setString("Level 1");
    menuButton[0].setPosition(sf::Vector2f((width / 1.6), (height / 2)));
    menuButton[0].setScale(1.5, 1.5);

    //SHOW LEADERBOARD BUTTON
    menuButton[1].setFillColor(sf::Color::Yellow);
    menuButton[1].setString("Level 2");
    menuButton[1].setPosition(sf::Vector2f((width / 1.6), (height / 1.7)));
    menuButton[1].setScale(1.5, 1.5);

    //SETTINGS BUTTON
    menuButton[2].setFillColor(sf::Color::Blue);
    menuButton[2].setString("Level 3");
    menuButton[2].setPosition(sf::Vector2f((width / 1.6), (height / 1.48)));
    menuButton[2].setScale(1.5, 1.5);

}

void ChooseLevelMenu::drawSubMenu(sf::RenderWindow& window)
{
    for (int i = 0; i < 3; i++)
    {
        window.draw(menuButton[i]);
    }
}
int ChooseLevelMenu::getSelectedButton(sf::RenderWindow& window) 
{
    // Introduce a delay (e.g., 100 milliseconds) while clicking to avoid errors
    std::this_thread::sleep_for(std::chrono::milliseconds(100));


    if (currentMenuState != LevelSelectionMenuState)
    {
        return -1; //menu not active anymore
    }

    //loop over all the menu buttons in the menu and check if they are pressed
    for (int i = 0; i < 3; i++)
    {
        if (checkIfPressed(window, menuButton[i]))
        {
            selectedButton = i;

            
            switch (selectedButton)
            {
            case 0:
              //  window.close(); //just testing if it works till further implementation
                break;
            case 1:
                break;
            case 2:
                break;
                
            }
            std::cout << "YOUR SELECTED BUTTON IS OF INDEX: " << selectedButton << std::endl;

        }
    }
    return selectedButton;
}