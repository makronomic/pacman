#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 

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
    DifficultySelectionMenuState,
    LeaderboardMenuState,
    SettingsMenuState,
    GameLogicState,
};

static MenuState currentMenuState;

class MainMenu
{

private:
    int chosenLevel = 0;
    int chosenDifficulty = 0;
    int selectedButton = 0;
    bool menuFinished = chosenDifficulty != 0 && chosenLevel != 0;

    sf::Texture menuBackgroundTexture;
    sf::Sprite menuBackground;
    sf::Text menuButton[NUM_OF_BUTTONS_MAINMENU];
    sf::Font menuFont;

    int getSelectedButton(sf::RenderWindow& window, const sf::Text& button, int index);
    bool checkIfPressed(sf::RenderWindow& window, const sf::Text& menuButton);

    void handleMainMenuEvent(sf::RenderWindow& window, int index);

    void handleLevelMenuEvent(sf::RenderWindow& window, int index, std::vector<sf::Text> levelButton);
    void drawLevelSelectionMenu(sf::RenderWindow& window, int width, int height);

    void drawDifficultySelectionMenu(sf::RenderWindow& window, int width, int height);
    void handleDifficultyMenuEvent(sf::RenderWindow& window, int index, sf::Text difficultyOption);

    void showHighScores(sf::RenderWindow& window);

    void showSettings(sf::RenderWindow& window);

    

public:

    bool isMenuFinished();
    void returnToMenu();
    int getChosenLevel();
    void setChosenLevel(int value);
    int getChosenDifficulty();
    void drawMenu(sf::RenderWindow& window);
    MainMenu(int numOfButtons);
    MainMenu(int width, int height);
    ~MainMenu();

};


