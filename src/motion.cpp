#include "../include/motion.h"

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
	case Object::Type::ENEMY:

		break;
	}
}