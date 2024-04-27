#include "motion.h"

void move(Object& o, const std::set<sf::Keyboard::Key>& buf) {
	switch (o.getType()) {
	case Object::Type::PLAYER:
		// modify the speed if the a pellet was eaten in the last 10 frames
		if (!buf.empty())
			for (auto it = buf.begin(); it != buf.end(); it++) {
				switch (*it) {
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
			}
		break;

	// to implement BFS when adding difficulties later
	case Object::Type::ENEMY:
		// difficulty 1
		int xMag = Random::get(0, 1) ? -1 : (Random::get(0, 1) ? 0 : 1);
		int yMag = Random::get(0, 1) ? -1 : (Random::get(0, 1) ? 0 : 1);

		o.setPos(o.getPos().x + xMag * o.getSpeed(), o.getPos().y + yMag * o.getSpeed());
	}
}