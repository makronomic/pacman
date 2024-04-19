#include "../include/object.h"

Object::Object(const sf::Vector2f& v, const Type& t) : pos { v }, type { t } {

}

void Object::setPosX(float x) {
	pos.x = x;
}

void Object::setPosY(float y) {
	pos.y = y;
}

void Object::setPos(float x, float y) {
	setPosX(x);
	setPosY(y);
}

Object::Type Object::getType() const {
	return type;
}

float Object::getPosX() const {
	return getPos().x;
}

float Object::getPosY() const {
	return getPos().y;
}

sf::Vector2f Object::getPos() const {
	return pos;
}
