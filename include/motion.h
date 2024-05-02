#pragma once

#include "check_bound.h"
#include "Object.h"
#include "Random.h"
#include <set>
#include <SFML/Graphics.hpp>

class Motion {
public:
	static bool checkCollision(Object&, Object&);
	static bool checkCollision(Object&);
	static void handleCollision(Object&);
	static void changeState(Object&, const std::set<sf::Keyboard::Key>& buf = std::set<sf::Keyboard::Key>());
	static void move(Object&, const std::set<sf::Keyboard::Key>& buf = std::set<sf::Keyboard::Key>());
};