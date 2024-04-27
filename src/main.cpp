#include <SFML/Graphics.hpp>
#include "../MainMenu.h"
#include <iostream>


//helper function during development, returns mouse position in the window when you click anywhere 
void mousePos(sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		std::cout << "X: " << mousePosition.x << " Y: " << mousePosition.y << std::endl;
	}
}

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Pac-Man!");
	MainMenu mainMenu(window.getSize().x, window.getSize().y);

	int chosenLevel = -1;
	int chosenDifficulty = -1;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			mousePos(window);

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		
		if (mainMenu.getChosenDifficulty() != 0 && mainMenu.getChosenLevel() != 0)
		{
			
			std::cout << "LEVEL: " << mainMenu.getChosenLevel() << " DIFFICULTY: " << mainMenu.getChosenDifficulty() << std::endl;
			//run game with parameters chosen level and chosen difficulty
			//gamelogic(level,difficulty)
			mainMenu.stopMusic();
			currentMenuState = GameLogicState;
		}
		else if(currentMenuState != GameLogicState)
		{
			mainMenu.drawMenu(window);
		}

		window.display();
	}

	return 0;
}