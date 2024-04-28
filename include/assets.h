#pragma once

#include "motion.h"
#include "Object.h"
#include <iostream>
#include <set>
#include <SFML/Graphics.hpp>

namespace Assets {
extern sf::RenderWindow window;
extern std::set<sf::Keyboard::Key> keyBuf;
extern Object player;
extern Object enemy;
}