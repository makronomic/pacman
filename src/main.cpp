
#include "Animation.h"
#include "assets.h"
#include "check_bound.h"
#include "Frames.h"
#include "MainMenu.h"
#include "motion.h"
#include "Object.h"
#include "setup.h"
#include <iostream>
#include <set>
#include <SFML/Graphics.hpp>


//helper function during development, returns mouse position in the window when you click anywhere 
void mousePos(sf::RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		std::cout << "X: " << mousePosition.x << " Y: " << mousePosition.y << std::endl;
	}
}

int main() 
{
    // Perform initial setup
    setup();

    // Create the main menu
    MainMenu mainMenu(Assets::window.getSize().x, Assets::window.getSize().y);
    std::string fileName; //for loading level

    // Main game loop
    while (Assets::window.isOpen()) 
    {
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

        // Clear the window
        Assets::window.clear();

        // If the main menu is still active
        if (!mainMenu.isMenuFinished()) 
        {
            // Draw the main menu and handle level selection
            mainMenu.drawMenu(Assets::window);
            int chosenLevel = mainMenu.getChosenLevel();
            if (chosenLevel >= 1 && chosenLevel <= 3) 
            {
                fileName = "world" + std::to_string(chosenLevel) + ".txt";
                Assets::level = Assets::level.createMapFromFile(fileName);
            }
        }
        // If the game is running
        else 
        {
            if (!Assets::level.isGameOver()) 
            {
                // Stop the main menu music and switch to game logic state
                mainMenu.stopMusic();
                currentMenuState = GameLogicState;

                // Update game logic
                Motion::move(Assets::player, Assets::keyBuf);
                Animation::motionPicture(Assets::player);
                Assets::level.drawLevel(Assets::window);
            }
            else 
            {
                // Game over, check for replay or return to main menu
                if (Assets::keyBuf.count(sf::Keyboard::R))
                {
                    std::cout << "REPLAY"; //handle replay logic
                }
                else if (Assets::keyBuf.count(sf::Keyboard::E)) 
                {
                    std::cout << "MAIN MENU";
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

