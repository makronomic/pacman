#pragma once

#include "Object.h"
#include <SFML\Graphics.hpp>

struct Pair {
	Object* obj = nullptr;
	sf::Sprite* spr = nullptr;

	Pair(Object& o, sf::Sprite& s) : obj(&o), spr(&s) {
	}
};