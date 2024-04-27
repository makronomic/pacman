#include "motion.h"
#include "Object.h"
#include <iostream>
#include <set>
#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 800), "Test Window");
	window.setFramerateLimit(60);

	Object player({ 0.f, 0.f }, 2.f, Object::Type::PLAYER);
	player.setSpriteSheet("resources/pacman.png");
	player.getSprite().setTexture(player.getSpriteSheet());
	player.getSprite().setTextureRect(sf::IntRect(
		0,
		0,
		32,
		32
	));

	Object enemy({ 200.f, 0.f }, 2.f, Object::Type::ENEMY);
	enemy.setSpriteSheet("resources/ghost.png");
	enemy.getSprite().setTexture(enemy.getSpriteSheet());
	enemy.getSprite().setTextureRect(sf::IntRect(
		0,
		0,
		32,
		32
	));


	while (window.isOpen()) {
	// set of input keys in the last frame
		std::set<sf::Keyboard::Key> keyBuf;
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
				keyBuf.insert(event.key.code);
			else if (event.type == sf::Event::KeyReleased)
				keyBuf.erase(event.key.code);
		}

		move(player, keyBuf);

		move(enemy);
		// temporarily keeping the enemy in bounds till collision handling
		if (enemy.getPos().x > 700 ||
			enemy.getPos().x < -700 ||
			enemy.getPos().y > 700 ||
			enemy.getPos().y < -700) {
			do {
				move(enemy);
			} while (enemy.getPos().x > 700 ||
					 enemy.getPos().x < -700 ||
					 enemy.getPos().y > 700 ||
					 enemy.getPos().y < -700);
		}

		if (checkCollision(player, enemy)) {
			std::cout << "COLLISION\n";
		} else {
			std::cout << "NO COLLISION\n";
		}

		window.clear();
		window.draw(enemy.getSprite());
		window.draw(player.getSprite());
		window.display();
	}

	return 0;
}