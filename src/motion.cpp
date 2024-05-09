#include "Animation.h"
#include "motion.h"
#include "Frames.h"

bool Motion::checkCollision(Object& x, Object& y) {
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

// check if colliding with any object
bool Motion::checkCollision(Object& o) {
	// make sure both positions are synced
	if (o.getPos() != o.getSprite().getPosition()) {
		o.getSprite().setPosition(o.getPos());
	}

	for (auto it = Assets::objects.begin(); it != Assets::objects.end(); it++) {
		if (o.getType() != (*it)->getType()) {
			if (checkCollision(o, **it)) {
				return true;
			}
		}
	}

	return false;
}

void Motion::handleCollision(Object& o) {
	// make sure both positions are synced
	if (o.getPos() != o.getSprite().getPosition()) {
		o.getSprite().setPosition(o.getPos());
	}

	if (checkCollision(o)) {
		o.setPos(Assets::prevPos[&o].x, Assets::prevPos[&o].y);
	}
}

void Motion::changeState(Object& o, const std::set<sf::Keyboard::Key>& buf) {
	// check if in game bounds or in collision 
	if (!checkBound(o) || checkCollision(o)) {
		o.state = 'i';
	}

	// make sure both positions are synced
	if (o.getPos() != o.getSprite().getPosition()) {
		o.getSprite().setPosition(o.getPos());
	}

	switch (o.getType()) {
	case Object::Type::PLAYER:
		// modify the speed if the a pellet was eaten in the last 10 frames
		if (!buf.empty()) {
			for (auto it = buf.begin(); it != buf.end(); it++) {
				switch (*it) {
				case sf::Keyboard::Up:
					o.state = 'u';

					break;

				case sf::Keyboard::Down:
					o.state = 'd';

					break;

				case sf::Keyboard::Left:
					o.state = 'l';

					break;

				case sf::Keyboard::Right:
					o.state = 'r';

					break;

				default:
					o.state = 'i';

					break;
				}
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

void Motion::move(Object& o, const std::set<sf::Keyboard::Key>& buf) {
	// Calculate the time elapsed since the last frame
	static sf::Clock clock;
	static float elapsedTime = 0.0f;
	float dt = clock.restart().asSeconds(); //deltatime
	elapsedTime += dt;

	// make sure both positions are synced
	if (o.getPos() != o.getSprite().getPosition()) {
		o.getSprite().setPosition(o.getPos());
	}

	if (o.getType() == Object::Type::PLAYER) {
		Motion::changeState(o, buf);
		// Update player position with the elapsed time
		while (elapsedTime >= 0.1f) {
			Assets::level.updatePlayerPosition();
			elapsedTime -= 0.16f;  //increase to make pacman move slower
		}
	}
	else {
		Motion::changeState(o);
	}


	switch (o.state) {
	case 'u':
		Assets::prevPos[&o] = o.getPos();

		o.setPos(o.getPos().x, o.getPos().y - o.getSpeed() * dt);
		o.getSprite().setPosition(o.getPos());

		break;

	case 'd':
		Assets::prevPos[&o] = o.getPos();

		o.setPos(o.getPos().x, o.getPos().y + o.getSpeed() * dt);
		o.getSprite().setPosition(o.getPos());

		break;

	case 'l':
		Assets::prevPos[&o] = o.getPos();

		o.setPos(o.getPos().x - o.getSpeed() * dt, o.getPos().y);
		o.getSprite().setPosition(o.getPos());

		break;

	case 'r':
		Assets::prevPos[&o] = o.getPos();

		o.setPos(o.getPos().x + o.getSpeed() * dt, o.getPos().y);
		o.getSprite().setPosition(o.getPos());

		break;

	default:
		Assets::prevPos[&o] = o.getPos();
	}
}
