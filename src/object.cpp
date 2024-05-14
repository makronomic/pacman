#include "Object.h"

// to create only one ghost of each color
//std::map<Object::ID, bool> Object::existingGhosts = {
//		std::make_pair(ID::GHOST_R, false),
//		std::make_pair(ID::GHOST_P, false),
//		std::make_pair(ID::GHOST_B, false),
//		std::make_pair(ID::GHOST_O, false)
//};
//
//std::map<Object::ID, bool> Object::loadedGhosts = {
//		std::make_pair(ID::GHOST_R, false),
//		std::make_pair(ID::GHOST_P, false),
//		std::make_pair(ID::GHOST_B, false),
//		std::make_pair(ID::GHOST_O, false)
//};

int Object::framechange = 1;
int Object::maxframe = 6;

Object::Object(const sf::Vector2f& pPos, float pSpd, const Type& pType) : pos { pPos }, spd { pSpd }, type { pType }, spr {}, ss {} {
	int freeIndex = 1;
	switch (pType) {
	case Type::PLAYER:
		/*id = ID::PACMAN;*/
		break;
	//case Type::ENEMY:
	//	for (auto& pair : Object::existingGhosts) {
	//		if (!pair.second) {
	//			pair.second = true;
	//			// insert the ID as a parameter and check for equality here
	//			id = static_cast<Object::ID>(freeIndex);
	//		}

	//		freeIndex++;
	//	}
	//	break;
	default:
		break;
	}
}



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

void Object::setId(int i) {
	id = i;
}

int Object::getId() const {
	return id;
}

/*int Object::maxframe() {
	return 6;
}*/



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