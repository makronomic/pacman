#pragma once

#include "Object.h"
#include "Random.h"
#include <set>
#include <SFML/Graphics.hpp>

bool checkCollision(Object&, Object&);
void move(Object&, const std::set<sf::Keyboard::Key>& buf = std::set<sf::Keyboard::Key>());