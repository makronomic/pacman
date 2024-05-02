#pragma once

#include "Object.h"
#include <set>
#include <SFML/Graphics.hpp>

namespace Assets {
extern int res;
extern sf::RenderWindow window;
extern std::set<sf::Keyboard::Key> keyBuf;
extern std::map<Object*, sf::Vector2f> prevPos;
extern std::vector<Object*> objects;
extern Object player;
extern Object enemy;
}