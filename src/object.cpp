#include "Object.h"

Object::Object(const sf::Vector2f& v, float s, const Type& t) : pos { v }, spd { s }, type { t } {

}

void Object::setPos(float x, float y) {
	pos.x = x;
	pos.y = y;
}

void Object::setSpd(float s) {
	spd = s;
}

float Object::getSpeed() const {
	return spd;
}

Object::Type Object::getType() const {
	return type;
}

sf::Vector2f Object::getPos() const {
	return pos;
}
