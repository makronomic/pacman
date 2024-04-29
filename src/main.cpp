#include "assets.h"
#include "check_bound.h"
#include "motion.h"
#include "setup.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
	setup();

	while (Assets::window.isOpen()) {
	// set of input keys in the last frame

		sf::Event event;
		while (Assets::window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				Assets::window.close();
			else if (event.type == sf::Event::KeyPressed)
				Assets::keyBuf.insert(event.key.code);
			else if (event.type == sf::Event::KeyReleased)
				Assets::keyBuf.erase(event.key.code);
		}

		move(Assets::player, Assets::keyBuf);

		move(Assets::enemy);

		Assets::window.clear();
		Assets::window.draw(Assets::enemy.getSprite());
		Assets::window.draw(Assets::player.getSprite());
		Assets::window.display();

		// clear the input buffer for the next frame
		Assets::keyBuf.clear();
	}

	return 0;
}