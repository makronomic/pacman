#include "../include/motion.h"
#include "../include/Random.h"

void move(Object& o) {
	switch (o.getType()) {
	case Object::Type::PLAYER:
		switch (getKey()) {
		case sf::Keyboard::Up:
			o.setPos(o.getPos().x, o.getPos().y - o.getSpeed());
			break;

		case sf::Keyboard::Down:
			o.setPos(o.getPos().x, o.getPos().y + o.getSpeed());
			break;

		case sf::Keyboard::Left:
			o.setPos(o.getPos().x - o.getSpeed(), o.getPos().y);
			break;

		case sf::Keyboard::Right:
			o.setPos(o.getPos().x + o.getSpeed(), o.getPos().y);
			break;
		}
		break;

	// to implement BFS when adding difficulties later
	case Object::Type::ENEMY:
		// if false move horizontally, true move vertically
		if (Random::get(0, 1)) {
			// if false the magnitude is negative, true the magnitude is positive
			if (Random::get(0, 1)) {
				o.setPos(o.getPos().x, o.getPos().y + o.getSpeed());
			} else {
				o.setPos(o.getPos().x, o.getPos().y - o.getSpeed());
			}
		} else {
			// if false the magnitude is negative, true the magnitude is positive
			if (Random::get(0, 1)) {
				o.setPos(o.getPos().x + o.getSpeed(), o.getPos().y);
			} else {
				o.setPos(o.getPos().x - o.getSpeed(), o.getPos().y);
			}
		}
	}
}