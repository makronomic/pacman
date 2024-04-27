#pragma once

#include "Object.h"
#include "Random.h"
#include <set>
#include <SFML/Graphics.hpp>

void move(Object&, const std::set<sf::Keyboard::Key>& buf = std::set<sf::Keyboard::Key>());