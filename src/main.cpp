#include "motion.h"
#include "Object.h"
#include <set>
#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 800), "Test Window");
	window.setFramerateLimit(30);

	sf::CircleShape player(100.f);
	Object playerObject({ 0.f, 0.f }, 2.f, Object::Type::PLAYER);
	player.setFillColor(sf::Color::Green);

	sf::RectangleShape enemy({ 100.f, 100.f });
	Object enemyObject({ 200.f, 0.f }, 2.f, Object::Type::ENEMY);
	enemy.setFillColor(sf::Color::Red);


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

		move(playerObject, keyBuf);
		player.setPosition(playerObject.getPos());

		// move(enemyObject);
		// // temporarily keeping the enemy in bounds till collision handling
		// if (enemyObject.getPos().x > 700 ||
		// 	enemyObject.getPos().x < -700 ||
		// 	enemyObject.getPos().y > 700 ||
		// 	enemyObject.getPos().y < -700) {
		// 	do {
		// 		move(enemyObject);
		// 	} while (enemyObject.getPos().x > 700 ||
		// 			 enemyObject.getPos().x < -700 ||
		// 			 enemyObject.getPos().y > 700 ||
		// 			 enemyObject.getPos().y < -700);
		// }
		// enemy.setPosition(enemyObject.getPos());

		window.clear();
		// window.draw(enemy);
		window.draw(player);
		window.display();
	}

	return 0;
}