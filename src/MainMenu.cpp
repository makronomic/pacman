#include "MainMenu.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <thread>
#include <vector>



//HELPER FUNCTIONS SECTION
int MainMenu::getSelectedButton(sf::RenderWindow& window, const sf::Text& button, int index) {

	if (checkIfPressed(window, button)) {
		selectedButton = index;
		return selectedButton;
	}

	return -1;
}

bool MainMenu::checkIfPressed(sf::RenderWindow& window, const sf::Text& button) {
	static bool isSoundPlaying = false;

	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::FloatRect buttonBounds = button.getGlobalBounds();

	//Checks if the mouse position is within the button bounds and the left mouse button is pressed
	bool isMouseInBounds = buttonBounds.contains(static_cast<sf::Vector2f> (mousePosition));
	bool isMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	bool pressed = isMouseInBounds && isMouseButtonPressed;
	if (pressed && !isSoundPlaying) {
		clickSound.play();
		isSoundPlaying = true;
	} else if (!isMouseButtonPressed) {
		isSoundPlaying = false; // Reset isSoundPlaying only when the button is not pressed
	}

	return pressed;
}

int MainMenu::getChosenDifficulty() {
	return chosenDifficulty;
}

int MainMenu::getChosenLevel() {
	return chosenLevel;
}

bool MainMenu::isMenuFinished()
{
	
	return menuFinished; //once level and difficulty isnt equal to 0, run the game

}

void MainMenu::returnToMenu()
{
	menuFinished = false;
	chosenDifficulty = 0;
	chosenLevel = 0;
	std::cout << chosenLevel << " "<< chosenDifficulty;
	playMusic();
	currentMenuState = MainMenuState;
}

void MainMenu::stopMusic() {
	menuMusic.stop();
	isMenuMusicPlaying = false;
}

void MainMenu::playMusic() {
	menuMusic.setVolume(50);
	menuMusic.play();
	menuMusic.setLoop(true);
	isMenuMusicPlaying = true;
}

//MAIN MENU SECTION
MainMenu::MainMenu(int numOfButtons) {
	//load font
	if (!menuFont.loadFromFile("resources/fonts/Crackman_Front.OTF")) {
		std::cout << "UNABLE TO LOAD FONT!";
	}

	if (!menuBackgroundTexture.loadFromFile("resources/background.png")) {
		std::cout << "UNABLE TO LOAD BACKGROUND";

	}

	menuBackground.setTexture(menuBackgroundTexture);


	if (!clickBuffer.loadFromFile("resources/audio/select.ogg")) {
		std::cout << "UNABLE TO LOAD CLICK SOUND";
	}
	clickSound.setBuffer(clickBuffer);

	menuMusic.openFromFile("resources/audio/theme.ogg");
	playMusic();

	//set all buttons to same font
	for (int i = 0; i < numOfButtons; i++) {
		menuButton[i].setFont(menuFont);
	}
}

MainMenu::MainMenu(int width, int height) : MainMenu(NUM_OF_BUTTONS_MAINMENU) {
	currentMenuState = MainMenuState;
	chosenLevel = 0;
	chosenDifficulty = 0;

	//CHOOSE LEVEL BUTTON
	menuButton[0].setFillColor(sf::Color::Blue);
	menuButton[0].setString("CHOOSE LEVEL");
	menuButton[0].setPosition(sf::Vector2f((width / 3.3), (height / 3)));
	menuButton[0].setScale(1.3, 1.3);

	//SHOW LEADERBOARD BUTTON
	menuButton[1].setFillColor(sf::Color::Yellow);
	menuButton[1].setString("SHOW LEADERBOARD");
	menuButton[1].setPosition(sf::Vector2f((width / 3.3), (height / 2.3)));
	menuButton[1].setScale(1.3, 1.3);

	//SETTINGS BUTTON
	menuButton[2].setFillColor(sf::Color::Blue);
	menuButton[2].setString("SETTINGS");
	menuButton[2].setPosition(sf::Vector2f((width / 3.3), (height / 1.85)));
	menuButton[2].setScale(1.3, 1.3);

	//EXIT BUTTON
	menuButton[3].setFillColor(sf::Color::Yellow);
	menuButton[3].setString("EXIT");
	menuButton[3].setPosition(sf::Vector2f((width / 3.3), (height / 1.5)));
	menuButton[3].setScale(1.3, 1.3);
}

void MainMenu::handleMainMenuEvent(sf::RenderWindow& window, int index) {
	// Introduce a delay (e.g., 100 milliseconds) while clicking to avoid errors
	//std::this_thread::sleep_for(std::chrono::milliseconds(100));

	if (currentMenuState != MainMenuState) {
		return; //main menu not active anymore
	}

	selectedButton = getSelectedButton(window, menuButton[index], index);

	//Change state depending on which button the user clicked
	switch (selectedButton) {
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
void MainMenu::drawLevelSelectionMenu(sf::RenderWindow& window, int width, int height) {
	currentMenuState = LevelSelectionMenuState;

	//SELECT A LEVEL TEXT
	sf::Text levelText;
	levelText.setFont(menuFont);
	levelText.setFillColor(sf::Color::White);
	levelText.setScale(1.5, 1.5);
	levelText.setString("Select a level:");
	levelText.setPosition(width / 3.3, height / 4);

	//RETURN TEXT
	sf::Text returnText;
	returnText.setFont(menuFont);
	returnText.setFillColor(sf::Color::White);
	returnText.setScale(1.5, 1.5);
	returnText.setString("Return");
	returnText.setPosition(width / 3.3, height - height / 3);

	window.draw(levelText);
	window.draw(returnText);

	int numOfLevels = 3; //initial number of levels
	std::vector<sf::Text> levelButton(numOfLevels);

	for (int i = 0; i < levelButton.size(); i++) {
		levelButton[i].setFont(menuFont);
		levelButton[i].setScale(1.5, 1.5);
		levelButton[i].setString("Level " + std::to_string(i + 1));
		levelButton[i].setPosition(sf::Vector2f(width / 2.8, height / 2.8 + i * 70));

		//alternating colour (just for taste)
		if (i % 2 == 0)
			levelButton[i].setFillColor(sf::Color::Blue);
		else
			levelButton[i].setFillColor(sf::Color::Yellow);

		window.draw(levelButton[i]);

		if (checkIfPressed(window, levelButton[i])) {
			handleLevelMenuEvent(window, i, levelButton);
		}
	}


	//return to main menu button check
	if (checkIfPressed(window, returnText)) {

		std::cout << "PRESSED ON RETURN IN LEVEL SELECTION";
		currentMenuState = MainMenuState;
	}



}

void MainMenu::handleLevelMenuEvent(sf::RenderWindow& window, int index, std::vector<sf::Text> levelButton) {

	if (currentMenuState != LevelSelectionMenuState) {
		return; //menu not active anymore
	}


	selectedButton = getSelectedButton(window, levelButton[index], index);
	chosenLevel = selectedButton + 1;

	std::cout << "YOUR SELECTED LEVEL IS: " << chosenLevel << std::endl;

	if (chosenLevel != 0) {
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		currentMenuState = DifficultySelectionMenuState;
	}

}


//DIFFICULTY MENU SECTION
void MainMenu::drawDifficultySelectionMenu(sf::RenderWindow& window, int width, int height) {
	currentMenuState = DifficultySelectionMenuState;

	//SELECT DIFFICULTY TEXT
	sf::Text difficultyText;
	difficultyText.setFont(menuFont);
	difficultyText.setFillColor(sf::Color::White);
	difficultyText.setScale(1.5, 1.5);
	difficultyText.setString("Select Difficulty: ");
	difficultyText.setPosition(width / 3.3, height / 4);

	//RETURN TEXT
	sf::Text returnText;
	returnText.setFont(menuFont);
	returnText.setFillColor(sf::Color::White);
	returnText.setScale(1.5, 1.5);
	returnText.setString("Return");
	returnText.setPosition(width / 3.3, height - height / 3);

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


	for (int i = 0; i < numOfDifficulties; i++) {
		difficultyOption[i].setFont(menuFont);
		difficultyOption[i].setScale(1.5, 1.5);

		difficultyOption[i].setPosition(sf::Vector2f(width / 2.8, height / 2.8 + i * 70));


		window.draw(difficultyOption[i]);

		if (checkIfPressed(window, difficultyOption[i])) {
			handleDifficultyMenuEvent(window, i, difficultyOption[i]);
		}
	}


	//return back to level menu
	if (checkIfPressed(window, returnText)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(300)); //to avoid pressing return in level menu too

		std::cout << "PRESSED ON DIFFICULTY RETURN OPTION";
		currentMenuState = LevelSelectionMenuState;
	}



}

void MainMenu::handleDifficultyMenuEvent(sf::RenderWindow& window, int index, sf::Text difficultyOption) {
	if (currentMenuState != DifficultySelectionMenuState) {
		return; //menu not active anymore
	}


	selectedButton = getSelectedButton(window, difficultyOption, index);
	chosenDifficulty = selectedButton + 1; //1 = EASY, 2 = NORMAL, 3 = HARD

	std::cout << "YOUR SELECTED DIFFICULTY IS: " << chosenDifficulty << std::endl;

	if (chosenDifficulty != 0) {
		std::cout << "READY TO PLAY! LEVEL: " << chosenLevel << " DIFFICULTY: " <<
			chosenDifficulty << std::endl;
		menuFinished = true;

	}

}


//high score section
void MainMenu::showHighScores(sf::RenderWindow& window) {
	std::map<int, std::string> scores;

	int width = window.getSize().x;
	int height = window.getSize().y;

	std::ifstream scoresFile("resources/scores.txt");
	std::string name;
	int scoreInFile; //our key

	if (!scoresFile.is_open()) {
		std::cout << "Error opening file!\n";
		return;
	}

	while (scoresFile >> name >> scoreInFile) {
		scores[scoreInFile] = name;
	}

	scoresFile.close();

	//TITLE
	sf::Text highScoresText;
	highScoresText.setFont(menuFont);
	highScoresText.setScale(1.8, 1.8);
	highScoresText.setString("TOP 3 SCORES:");
	highScoresText.setFillColor(sf::Color::White);
	highScoresText.setPosition(width/5, 170);
	window.draw(highScoresText);

	//RETURN TEXT
	sf::Text returnText;
	returnText.setFont(menuFont);
	returnText.setFillColor(sf::Color::White);
	returnText.setScale(1.5, 1.5);
	returnText.setString("Return");
	returnText.setPosition(width / 5, 480);
	window.draw(returnText);

	//SCORES (DESCENDING)
	sf::Text scoreText;
	scoreText.setFont(menuFont);
	scoreText.setScale(1.5, 1.5);
	scoreText.setFillColor(sf::Color::Yellow);

	int yPos = 250;
	int count = 0; //only 3 highscores

	for (auto it = scores.rbegin(); it != scores.rend() && count < 3; ++it) {

		scoreText.setString(std::to_string(count + 1) + ". " + it->second + " - " + std::to_string(it->first));
		scoreText.setPosition(width / 4, yPos);
		window.draw(scoreText);
		yPos += 70;
		count++;
	}


	//return back to main menu
	if (checkIfPressed(window, returnText)) {
		currentMenuState = MainMenuState;
	}

}


//settings section
void MainMenu::showSettings(sf::RenderWindow& window) {
	currentMenuState = SettingsMenuState;
	sf::Text settingsText;
	settingsText.setFont(menuFont);
	settingsText.setFillColor(sf::Color::White);
	settingsText.setScale(1.5, 1.5);
	settingsText.setString("SETTINGS:");
	settingsText.setPosition(250, 200);

	sf::Text musicText;
	musicText.setFont(menuFont);
	musicText.setFillColor(isMenuMusicPlaying ? sf::Color::Green : sf::Color::Red);
	musicText.setScale(1.5, 1.5);
	musicText.setString(isMenuMusicPlaying ? "MUSIC ON" : "MUSIC OFF");
	musicText.setPosition(300, 300);

	// Check if music text is pressed
	if (checkIfPressed(window, musicText)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(300));

		if (isMenuMusicPlaying) //disable music
		{
			stopMusic();
			isMenuMusicPlaying = false;
		} else //enable music
		{
			playMusic();
			isMenuMusicPlaying = true;
		}
	}


	//RETURN TEXT
	sf::Text returnText;
	returnText.setFont(menuFont);
	returnText.setFillColor(sf::Color::White);
	returnText.setScale(1.5, 1.5);
	returnText.setString("Return");
	returnText.setPosition(250, 400);

	//return to main menu button check
	if (checkIfPressed(window, returnText)) {

		std::cout << "PRESSED ON RETURN IN LEVEL SELECTION";
		currentMenuState = MainMenuState;
	}



	window.draw(returnText);
	window.draw(musicText);
	window.draw(settingsText);
}




//FUNCTION THAT HANDLES DRAWING OF MENUS ACCORDING TO WHAT THE USER PRESSED
void MainMenu::drawMenu(sf::RenderWindow& window) {
	if (currentMenuState != GameLogicState)
	{

		switch (currentMenuState) {
		case MainMenuState:
			window.draw(menuBackground);

			for (int i = 0; i < NUM_OF_BUTTONS_MAINMENU; i++) {
				if (checkIfPressed(window, menuButton[i])) {
					handleMainMenuEvent(window, i);
				}
				window.draw(menuButton[i]);
			}
			break;
		case LevelSelectionMenuState:
			window.draw(menuBackground);
			drawLevelSelectionMenu(window, window.getSize().x, window.getSize().y);

			break;
		case DifficultySelectionMenuState:
			window.draw(menuBackground);
			drawDifficultySelectionMenu(window, window.getSize().x, window.getSize().y);
			break;
		case LeaderboardMenuState:
			window.draw(menuBackground);
			showHighScores(window);

			break;
		case SettingsMenuState:
			window.draw(menuBackground);
			showSettings(window);

			break;

		}
	}
}


MainMenu::~MainMenu() 
{
	//std::cout << "MAIN MENU DESTROYED!";
}
