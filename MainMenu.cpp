#include "MainMenu.h"
#include "SubMenus.h"
#include <iostream>

//base constructor that initializes fonts and music and background.
//can be called from inherited submenus for easier initialization.
MainMenu::MainMenu(int numOfButtons)
{
    //load font
    if (!menuFont.loadFromFile("fonts/Crackman_Front.OTF"))
    {
        std::cout << "UNABLE TO LOAD FONT!";
    }

    //set all buttons to same font
    for (int i = 0; i < numOfButtons; i++)
    {
        menuButton[i].setFont(menuFont);
    }

}

MainMenu::MainMenu(int width, int height) : MainMenu(NUM_OF_BUTTONS_MAINMENU)
{
    currentMenuState = MainMenuState;

    //CHOOSE LEVEL BUTTON
    menuButton[0].setFillColor(sf::Color::Blue);
    menuButton[0].setString("CHOOSE LEVEL");
    menuButton[0].setPosition(sf::Vector2f( (width/1.6) , (height/2) ));
    menuButton[0].setScale(1.3, 1.3);

    //SHOW LEADERBOARD BUTTON
    menuButton[1].setFillColor(sf::Color::Yellow);
    menuButton[1].setString("SHOW LEADERBOARD");
    menuButton[1].setPosition(sf::Vector2f((width / 1.6), (height / 1.7)));
    menuButton[1].setScale(1.3, 1.3);

    //SETTINGS BUTTON
    menuButton[2].setFillColor(sf::Color::Blue);
    menuButton[2].setString("SETTINGS");
    menuButton[2].setPosition(sf::Vector2f((width / 1.6), (height / 1.48)));
    menuButton[2].setScale(1.3, 1.3);

    //EXIT BUTTON
    menuButton[3].setFillColor(sf::Color::Yellow);
    menuButton[3].setString("EXIT");
    menuButton[3].setPosition(sf::Vector2f((width / 1.6), (height / 1.3)));
    menuButton[3].setScale(1.3, 1.3);
}


void MainMenu::drawMenu(sf::RenderWindow& window)
{
    ChooseLevelMenu clm(1280,720);
    switch (currentMenuState) 
    {
    case MainMenuState:
        for (int i = 0; i < NUM_OF_BUTTONS_MAINMENU; i++) {
            window.draw(menuButton[i]);
        }
        break;
    case LevelSelectionMenuState:
        clm.drawSubMenu(window);
        clm.getSelectedButton(window);
        break;
    case LeaderboardMenuState:
        break;
    case SettingsMenuState:
        break;
        
    }
}


int MainMenu::getSelectedButton(sf::RenderWindow& window)
{
    
    if (currentMenuState != MainMenuState)
    {
        return -1; //main menu not active anymore
    }

    //loop over all the menu buttons in the menu and check if they are pressed
    for (int i = 0; i < NUM_OF_BUTTONS_MAINMENU; i++) 
    {
        if (checkIfPressed(window, menuButton[i]))
        {
            selectedButton = i;

            //Change state depending on which button the user clicked
            switch (selectedButton) 
            {
            case 0: 
                currentMenuState = LevelSelectionMenuState;
                break;
            case 1: 
                currentMenuState = LeaderboardMenuState;
                break;
            case 2: 
                currentMenuState = SettingsMenuState;
                break;
            case 3: 
                window.close();
                break;
            }
            std::cout << "YOUR SELECTED BUTTON IS OF INDEX: " << selectedButton << std::endl;
        }
    }
    return selectedButton;
}

bool MainMenu::checkIfPressed(sf::RenderWindow& window, sf::Text menuButton)
{

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    sf::FloatRect buttonBounds = menuButton.getGlobalBounds();

    //Checks if the mouse position is within the button bounds and the left mouse button is pressed
    bool isMouseInBounds = buttonBounds.contains(static_cast<sf::Vector2f>(mousePosition));
    bool isMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);


    return isMouseInBounds && isMouseButtonPressed;
}

MainMenu::~MainMenu()
{

}