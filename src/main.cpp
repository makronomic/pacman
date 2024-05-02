#include "MainMenu.h"
#include "motion.h"
#include "Object.h"
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

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Pac-Man!");

	sf::CircleShape player(100.f);
	Object playerObject({ 0.f, 0.f }, 2.f, Object::Type::PLAYER);
	player.setFillColor(sf::Color::Green);

	sf::RectangleShape enemy({ 100.f, 100.f });
	Object enemyObject({ 200.f, 0.f }, 2.f, Object::Type::ENEMY);
	enemy.setFillColor(sf::Color::Red);


	MainMenu mainMenu(window.getSize().x, window.getSize().y);

	int chosenLevel = -1;
	int chosenDifficulty = -1;

	while (window.isOpen()) {
	// set of input keys in the last frame
		std::set<sf::Keyboard::Key> keyBuf;
		sf::Event event;
		while (window.pollEvent(event)) {
			mousePos(window);

			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
				keyBuf.insert(event.key.code);
			else if (event.type == sf::Event::KeyReleased)
				keyBuf.erase(event.key.code);
		}

		move(playerObject, keyBuf);
		player.setPosition(playerObject.getPos());

		window.clear();
		// window.draw(enemy);
		window.draw(player);

		window.display();
	}

	return 0;
}