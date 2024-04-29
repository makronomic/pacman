#include "motion.h"

bool checkCollision(Object& x, Object& y) {
	// make sure both positions are synced
	if (x.getPos() != x.getSprite().getPosition()) {
		x.getSprite().setPosition(x.getPos());
	}

	if (y.getPos() != y.getSprite().getPosition()) {
		y.getSprite().setPosition(y.getPos());
	}

	sf::FloatRect rectX = x.getSprite().getGlobalBounds();
	sf::FloatRect rectY = y.getSprite().getGlobalBounds();

	// exit if there's no overlap
	if (!rectX.intersects(rectY)) {
		return false;
	}

	// get pixel data
	const sf::Texture* xTx = x.getSprite().getTexture();
	const sf::Texture* yTx = y.getSprite().getTexture();

	sf::Image imgX = xTx->copyToImage();
	sf::Image imgY = yTx->copyToImage();

	// create the overlap rectangle
	sf::IntRect overlap {
		static_cast<int>(std::floor(std::max(rectX.left, rectY.left))), // left
		static_cast<int>(std::floor(std::max(rectX.top, rectY.top))), // top
		static_cast<int>(std::floor(std::min(rectX.left + rectX.width, rectY.left + rectY.width) - std::floor(std::max(rectX.left, rectY.left)))), // width
		static_cast<int>(std::floor(std::min(rectX.top + rectX.height, rectY.top + rectY.height) - std::floor(std::max(rectX.top, rectY.top)))) // height
	};

	// loop through the pixels
	for (int yPx = overlap.top; yPx < overlap.top + overlap.height; ++yPx) { // top to bottom
		for (int xPx = overlap.left; xPx < overlap.left + overlap.width; ++xPx) { // left to right
			// Calculate relative pixel positions, limiting the relative positions to the texture size
			sf::Vector2u posRelX = {
			static_cast<unsigned>(std::min(
				static_cast<unsigned>(xPx - rectX.left + xTx->getSize().x - overlap.width), xTx->getSize().x - 1
			)),
			static_cast<unsigned>(std::min(
				static_cast<unsigned>(yPx - rectX.top), xTx->getSize().y - 1
			)) };

			sf::Vector2u posRelY = {
			static_cast<unsigned>(std::min(
				static_cast<unsigned>(xPx - rectY.left + yTx->getSize().x - overlap.width), yTx->getSize().x - 1
			)),
			static_cast<unsigned>(std::min(
				static_cast<unsigned>(yPx - rectY.top), yTx->getSize().y - 1
			)) };

			/*std::cout << "X Relative Position: (" << posRelX.x << ", " << posRelX.y << ")\n";
			std::cout << "Y Relative Position: (" << posRelY.x << ", " << posRelY.y << ")\n";*/

			// Get current pixel color
			sf::Color colorX = imgX.getPixel(posRelX.x, posRelX.y);
			sf::Color colorY = imgY.getPixel(posRelY.x, posRelY.y);

			// check for a certain alpha value
			if (colorX.a > 128 && colorY.a > 128) {
				return true;
			}
		}
	}

	return false;
}

void move(Object& o, const std::set<sf::Keyboard::Key>& buf) {
	// check if in game bounds
	if (!bound_check(o)) {
		return;
	}

	switch (o.getType()) {
	case Object::Type::PLAYER:
		// modify the speed if the a pellet was eaten in the last 10 frames
		if (!buf.empty())
			for (auto it = buf.begin(); it != buf.end(); it++) {
				switch (*it) {
				case sf::Keyboard::Up:
					o.setPos(o.getPos().x, o.getPos().y - o.getSpeed());
					o.getSprite().setPosition(o.getPos());
					// std::cout << "Object's position: " << o.getPos().x << ", " << o.getPos().y << "\nSprite's Position: " << o.getSprite().getPosition().x << ", " << o.getSprite().getPosition().y << "\n";
					break;

				case sf::Keyboard::Down:
					o.setPos(o.getPos().x, o.getPos().y + o.getSpeed());
					o.getSprite().setPosition(o.getPos());
					// std::cout << "Object's position: " << o.getPos().x << ", " << o.getPos().y << "\nSprite's Position: " << o.getSprite().getPosition().x << ", " << o.getSprite().getPosition().y << "\n";
					break;

				case sf::Keyboard::Left:
					o.setPos(o.getPos().x - o.getSpeed(), o.getPos().y);
					o.getSprite().setPosition(o.getPos());
					// std::cout << "Object's position: " << o.getPos().x << ", " << o.getPos().y << "\nSprite's Position: " << o.getSprite().getPosition().x << ", " << o.getSprite().getPosition().y << "\n";
					break;

				case sf::Keyboard::Right:
					o.setPos(o.getPos().x + o.getSpeed(), o.getPos().y);
					o.getSprite().setPosition(o.getPos());
					// std::cout << "Object's position: " << o.getPos().x << ", " << o.getPos().y << "\nSprite's Position: " << o.getSprite().getPosition().x << ", " << o.getSprite().getPosition().y << "\n";
					break;
				}
			}
		break;

	// to implement BFS when adding difficulties later
	case Object::Type::ENEMY:
		// // difficulty 1
		// int xFactor = Random::get(0, 1) ? -1 : (Random::get(0, 1) ? 0 : 1);
		// int yFactor = Random::get(0, 1) ? -1 : (Random::get(0, 1) ? 0 : 1);
		// 
		// o.setPos(o.getPos().x + xFactor * o.getSpeed(), o.getPos().y + yFactor * o.getSpeed());
		break;
	}
}