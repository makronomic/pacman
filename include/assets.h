#pragma once


#include "Object.h"
#include <set>
#include <SFML/Graphics.hpp>

namespace Assets {
extern int res;
extern sf::RenderWindow window;
extern std::set<sf::Keyboard::Key> keyBuf;
extern Object player;
extern Object enemy;
}