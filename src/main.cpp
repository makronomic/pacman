#include "Animation.h"
#include "assets.h"
#include "check_bound.h"
#include "Enemies_Movement.h"
#include "Frames.h"
#include "MainMenu.h"
#include "motion.h"
#include "Object.h"
#include "setup.h"
#include "soundSys.h"
#include <iostream>
#include <set>
#include <SFML/Graphics.hpp>


// helper function during development, returns mouse position in the window when
// you click anywhere
void mousePos(sf::RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		std::cout << "X: " << mousePosition.x << " Y: " << mousePosition.y
			<< std::endl;
	}
}

int main() {
  // Perform initial setup
	setup();
	srand(static_cast<unsigned>(time(nullptr)));

	// Create the main menu
	MainMenu mainMenu(Assets::window.getSize().x, Assets::window.getSize().y);
	std::string fileName; // for loading level

	// Main game loop
	while (Assets::window.isOpen()) {
	  // Handle events
		sf::Event event;
		mousePos(Assets::window);
		while (Assets::window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
			  // Close the window if the close button is pressed
				Assets::window.close();
				break;
			case sf::Event::KeyPressed:
			  // Store pressed keys
				Assets::keyBuf.insert(event.key.code);
				break;
			case sf::Event::KeyReleased:
			  // Remove released keys
				Assets::keyBuf.erase(event.key.code);
				break;
			default:
				break;
			}
		}

		int chosenLevel = mainMenu.getChosenLevel();
		int chosenDifficulty = mainMenu.getChosenDifficulty();

		// Clear the window
		Assets::window.clear();

		// If the main menu is still active
		if (!mainMenu.isMenuFinished()) {
		  // Draw the main menu and handle level selection
			mainMenu.drawMenu(Assets::window);
			fileName = "resources/world" + std::to_string(chosenLevel) + ".txt";
			Assets::level = Assets::level.createMapFromFile(fileName);

		}
		// If the game is running
		else {
			if (!Assets::level.isGameOver()) {
			  // Stop the main menu music and switch to game logic state
				soundSys::stopMusic(1);
				soundSys::playMusic(2);
				currentMenuState = GameLogicState;

				// Update game logic

				Motion::move(Assets::player, Assets::keyBuf);
				updateGhost(chosenDifficulty); // ENEMY MOVEMENT
				Animation::motionPicture(Assets::player);
				// use for loop on Assets::objectss
				Animation::motionPicture(Assets::enemyRed);
				Animation::motionPicture(Assets::enemyPink);
				Animation::motionPicture(Assets::enemyBlue);
				Animation::motionPicture(Assets::enemyOrange);

				Assets::level.drawLevel();
				// DEBUGGING
				if (Assets::keyBuf.count(
					sf::Keyboard::G)) // simulate game over during development just
									  // for testing
				{
					Assets::level.gameOver = true;
				}

				if (Assets::keyBuf.count(
					sf::Keyboard::W)) // simulate winning during development just
									  // for testing
				{
					Assets::level.foodCount = 0;
					Assets::level.gameOver = true;
				}
				// DEBUGGING

				// DEBUGGING
				if (Assets::keyBuf.count(
					sf::Keyboard::G)) // simulate game over during development just
									  // for testing
				{
					Assets::level.gameOver = true;
				}

				if (Assets::keyBuf.count(
					sf::Keyboard::W)) // simulate winning during development just
									  // for testing
				{
					Assets::level.foodCount = 0;
					Assets::level.gameOver = true;
				}
				// DEBUGGING

			} else if (Assets::level.isGameOver() &&
					   Assets::level.getFoodCount() > 0) // LOSING CASE
				
			{
				
				mainMenu.postGame(Assets::window,false,event);
			  // Game over, check for replay or return to main menu
				if (Assets::keyBuf.count(sf::Keyboard::R)) // RESTART
				{
					Assets::player.state = 'i'; // to stop player from moving immediately
												// after the game restarts
					fileName = "resources/world" + std::to_string(chosenLevel) + ".txt";
					Assets::level = Assets::level.createMapFromFile(fileName);
				} else if (Assets::keyBuf.count(sf::Keyboard::E)) {
					Assets::player.state = 'i';
					mainMenu.returnToMenu();
				}
				else if (Assets::keyBuf.count(sf::Keyboard::V)) {
					Assets::player.state = 'i';
				
				}
			} else if (Assets::level.getFoodCount() == 0 &&
					   Assets::level.isGameOver()) // WINNING CASE
			{
				//testing saving options
				//x=mainMenu.enterName( event,Assets::window);
			//	mainMenu.saveTextToFile(Assets::window);
			} else if (Assets::level.isGameOver() &&
					   Assets::level.getFoodCount() > 0) // LOSING CASE
			{
				mainMenu.postGame(Assets::window, true, event);
				soundSys::stopMusic(2);
				soundSys::stopSound(2);
				soundSys::playsound(3);
			  // Game over, check for replay or return to main menu
				if (Assets::keyBuf.count(sf::Keyboard::R)) // RESTART
				{
					Assets::player.state = 'i'; // to stop player from moving immediately
												// after the game restarts
					fileName = "resources/world" + std::to_string(chosenLevel) + ".txt";
					Assets::level = Assets::level.createMapFromFile(fileName);
				} else if (Assets::keyBuf.count(sf::Keyboard::E)) {
					Assets::player.state = 'i';
					mainMenu.returnToMenu();
				}
			} else if (Assets::level.getFoodCount() == 0 &&
					   Assets::level.isGameOver()) // WINNING CASE
			{
				soundSys::stopMusic(2);
				soundSys::playMusic(1);
				std::cout << "YOU WON!";

				//	window after wining or losing the game
				mainMenu.postGame(Assets::window, true, event);
					std::cout << "YOU WON!";

					if (Assets::keyBuf.count(
						sf::Keyboard::N)) // NEXT LEVEL, still needs to save in file
						// before going to next level
					{
						Assets::player.state = 'i'; // to stop player from moving immediately
						// after the game restarts
						mainMenu.setChosenLevel(mainMenu.getChosenLevel() + 1);
						chosenLevel = mainMenu.getChosenLevel();
						fileName = "resources/world" + std::to_string(chosenLevel) + ".txt";
						Assets::level = Assets::level.createMapFromFile(fileName);
					}

				if (Assets::keyBuf.count(
					sf::Keyboard::E)) // return to main menu, should add save in
									  // file function
				{
					Assets::player.state = 'i';
					mainMenu.returnToMenu();

				}
			}
		}

		// Display the window
		Assets::window.display();

		// Clear the input buffer for the next frame
		Assets::keyBuf.clear();
	}

	return 0;
}
