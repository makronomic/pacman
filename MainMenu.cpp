#include "MainMenu.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

//HELPER FUNCTIONS SECTION
int MainMenu::getSelectedButton(sf::RenderWindow& window, const sf::Text& button, int index)
{

    if (checkIfPressed(window, button))
    {
        selectedButton = index;
        return selectedButton;
    }

    return -1;
}

bool MainMenu::checkIfPressed(sf::RenderWindow& window, const sf::Text& button)
{

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::FloatRect buttonBounds = button.getGlobalBounds();

    //Checks if the mouse position is within the button bounds and the left mouse button is pressed
    bool isMouseInBounds = buttonBounds.contains(static_cast<sf::Vector2f> (mousePosition));
    bool isMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    return isMouseInBounds && isMouseButtonPressed;
}

int MainMenu::getChosenDifficulty()
{
    return chosenDifficulty;
}

int MainMenu::getChosenLevel()
{
    return chosenLevel;
}


//MAIN MENU SECTION
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
    chosenLevel = 0;
    chosenDifficulty = 0;

    //CHOOSE LEVEL BUTTON
    menuButton[0].setFillColor(sf::Color::Blue);
    menuButton[0].setString("CHOOSE LEVEL");
    menuButton[0].setPosition(sf::Vector2f((width / 1.6), (height / 2)));
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

void MainMenu::handleMainMenuEvent(sf::RenderWindow& window, int index)
{
    // Introduce a delay (e.g., 100 milliseconds) while clicking to avoid errors
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));

       if (currentMenuState != MainMenuState)
       {
           return; //main menu not active anymore
       }

       selectedButton = getSelectedButton(window, menuButton[index], index);

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




//LEVEL MENU SECTION
void MainMenu::drawLevelSelectionMenu(sf::RenderWindow& window,int width, int height)
{
    currentMenuState = LevelSelectionMenuState;

    //SELECT A LEVEL TEXT
    sf::Text levelText;
    levelText.setFont(menuFont);
    levelText.setFillColor(sf::Color::White);
    levelText.setScale(1.5,1.5);
    levelText.setString("Select a level:");
    levelText.setPosition(width / 3, height / 4);

    //RETURN TEXT
    sf::Text returnText;
    returnText.setFont(menuFont);
    returnText.setFillColor(sf::Color::White);
    returnText.setScale(1.5, 1.5);
    returnText.setString("Return");
    returnText.setPosition(width / 3, height - height / 3);

    window.draw(levelText);
    window.draw(returnText);

    int numOfLevels = 3; //initial number of levels
    std::vector<sf::Text> levelButton(numOfLevels);

    for (int i = 0; i < levelButton.size(); i++)
    {
        levelButton[i].setFont(menuFont);
        levelButton[i].setScale(1.5, 1.5);
        levelButton[i].setString("Level " + std::to_string(i + 1));
        levelButton[i].setPosition(sf::Vector2f(width / 2.5, height / 2.8 + i * 70));

        //alternating colour (just for taste)
        if (i % 2 == 0)
            levelButton[i].setFillColor(sf::Color::Blue);
        else
            levelButton[i].setFillColor(sf::Color::Yellow);

        window.draw(levelButton[i]);

        if (checkIfPressed(window, levelButton[i]))
        {
            handleLevelMenuEvent(window, i, levelButton);
        }
    }

   
    //return to main menu button check
    if (checkIfPressed(window, returnText))
    {

        std::cout << "PRESSED ON RETURN IN LEVEL SELECTION";
        currentMenuState = MainMenuState;
    }

    

}

void MainMenu::handleLevelMenuEvent(sf::RenderWindow& window, int index, std::vector<sf::Text> levelButton)
{
    // Introduce a delay (e.g., 100 milliseconds) while clicking to avoid errors
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    if (currentMenuState != LevelSelectionMenuState)
    {
        return; //menu not active anymore
    }
    

    selectedButton = getSelectedButton(window, levelButton[index], index);
    chosenLevel = selectedButton + 1;
  
    std::cout << "YOUR SELECTED LEVEL IS: " << chosenLevel << std::endl;

    if (chosenLevel != 0)
    {
        currentMenuState = DifficultySelectionMenuState;
    }

}


//DIFFICULTY MENU SECTION
void MainMenu::drawDifficultySelectionMenu(sf::RenderWindow& window, int width, int height)
{
    currentMenuState = DifficultySelectionMenuState;

    //SELECT DIFFICULTY TEXT
    sf::Text difficultyText;
    difficultyText.setFont(menuFont);
    difficultyText.setFillColor(sf::Color::White);
    difficultyText.setScale(1.5, 1.5);
    difficultyText.setString("Select Difficulty: ");
    difficultyText.setPosition(width / 3, height / 4);

    //RETURN TEXT
    sf::Text returnText;
    returnText.setFont(menuFont);
    returnText.setFillColor(sf::Color::White);
    returnText.setScale(1.5, 1.5);
    returnText.setString("Return");
    returnText.setPosition(width / 3, height - height / 3);

    window.draw(difficultyText);
    window.draw(returnText);

    const int numOfDifficulties = 3; 
    sf::Text difficultyOption[numOfDifficulties];

    difficultyOption[0].setString("EASY");
    difficultyOption[0].setFillColor(sf::Color::Blue);

    difficultyOption[1].setString("NORMAL");
    difficultyOption[1].setFillColor(sf::Color::Yellow);

    difficultyOption[2].setString("HARD");
    difficultyOption[2].setFillColor(sf::Color::Red);


    for (int i = 0; i < numOfDifficulties; i++)
    {
        difficultyOption[i].setFont(menuFont);
        difficultyOption[i].setScale(1.5, 1.5);

        difficultyOption[i].setPosition(sf::Vector2f(width / 2.5, height / 2.8 + i * 70));


        window.draw(difficultyOption[i]);

        if (checkIfPressed(window, difficultyOption[i]))
        {
            handleDifficultyMenuEvent(window, i, difficultyOption[i]);
        }
    }


    //return back to level menu
    if (checkIfPressed(window, returnText))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); //to avoid pressing return in level menu too

        std::cout << "PRESSED ON DIFFICULTY RETURN OPTION";
        currentMenuState = LevelSelectionMenuState;
    }



}

void MainMenu::handleDifficultyMenuEvent(sf::RenderWindow& window, int index, sf::Text difficultyOption)
{
    // Introduce a delay (e.g., 100 milliseconds) while clicking to avoid errors
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    if (currentMenuState != DifficultySelectionMenuState)
    {
        return; //menu not active anymore
    }


    selectedButton = getSelectedButton(window, difficultyOption, index);
    chosenDifficulty = selectedButton + 1; //1 = EASY, 2 = NORMAL, 3 = HARD

    std::cout << "YOUR SELECTED DIFFICULTY IS: " << chosenDifficulty << std::endl;

    if (chosenDifficulty != 0)
    {
        std::cout << "READY TO PLAY! LEVEL: " << chosenLevel << " DIFFICULTY: " <<
            chosenDifficulty<< std::endl;
    }

}


//FUNCTION THAT HANDLES DRAWING OF MENUS ACCORDING TO WHAT THE USER PRESSED
void MainMenu::drawMenu(sf::RenderWindow& window)
{
    
    switch (currentMenuState)
    {
    case MainMenuState:
        for (int i = 0; i < NUM_OF_BUTTONS_MAINMENU; i++)
        {
            if (checkIfPressed(window, menuButton[i]))
            {
                handleMainMenuEvent(window, i);
            }
            window.draw(menuButton[i]);
        }
        break;
    case LevelSelectionMenuState:
        drawLevelSelectionMenu(window, window.getSize().x, window.getSize().y);
        break;
    case DifficultySelectionMenuState:
        drawDifficultySelectionMenu(window, window.getSize().x, window.getSize().y);
        break;
    case LeaderboardMenuState:
        break;
    case SettingsMenuState:
        break;
    }
}


MainMenu::~MainMenu()
{
    std::cout << "MAIN MENU EXIT!";
    currentMenuState = GameLogicState;
}
