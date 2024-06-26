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
    int chosenLevel;
    int chosenDifficulty;
    int selectedButton = 0;
    bool isMenuMusicPlaying;

    sf::Texture menuBackgroundTexture;
    sf::Sprite menuBackground;
    sf::Text menuButton[NUM_OF_BUTTONS_MAINMENU];
    sf::Font menuFont;

    sf::SoundBuffer clickBuffer; 
    sf::Sound clickSound;

    sf::Music menuMusic;

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

    int getChosenLevel();
    int getChosenDifficulty();
    void drawMenu(sf::RenderWindow& window);
    void stopMusic();
    void playMusic();
    MainMenu(int numOfButtons);
    MainMenu(int width, int height);
    ~MainMenu();

};


