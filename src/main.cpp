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
	MainMenu mainMenu(1280, 720);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{

			mousePos(window);
			mainMenu.getSelectedButton(window);

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		mainMenu.drawMenu(window);
		window.display();
	}

	return 0;
}