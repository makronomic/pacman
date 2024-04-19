#include "../include/get_key.h"

sf::Keyboard::Key getKey() {
	for (int offset = 0; offset < 4; offset++) {
		// check if any key from up, down, left or right are pressed and return it;
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(sf::Keyboard::Left + offset))) {
			return static_cast<sf::Keyboard::Key>(sf::Keyboard::Left + offset);
		}
	}
}