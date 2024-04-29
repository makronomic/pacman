#include "Object.h"

Object::Object(const sf::Vector2f& pPos, float pSpd, const Type& pType) : pos { pPos }, spd { pSpd }, type { pType }, spr {}, ss {} {

}

int currentframe = 0;

char state = 'r';

void Object::setPos(float x, float y) {
	pos.x = x;
	pos.y = y;
}

void Object::setSpd(float s) {
	spd = s;
}

void Object::setSpriteSheet(std::string_view path) {
	ss.loadFromFile(path.data());
}

float Object::getSpeed() const {
	return spd;
}

int Object::maxframe() {
	return 7;
}

int Object::framechange() {
	return 5;
}

Object::Type Object::getType() const {
	return type;
}

sf::Vector2f& Object::getPos() {
	return pos;
}

sf::Sprite& Object::getSprite() {
	return spr;
}

sf::Texture& Object::getSpriteSheet() {
	return ss;
}