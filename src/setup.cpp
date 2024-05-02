#include "setup.h"

// definitions 
int Assets::res = 800;
int Assets::resY = 720;

sf::RenderWindow Assets::window(sf::VideoMode(Assets::res, Assets::res), "Test Window");

std::set<sf::Keyboard::Key> Assets::keyBuf;

Object Assets::player(
	{ 200.f, 300.f },
	2.f,
	Object::Type::PLAYER
);

Object Assets::enemy(
	{ 400.f, 300.f },
	2.f,
	Object::Type::ENEMY
);

std::vector<Object*> Assets::objects;
std::map<Object*, sf::Vector2f> Assets::prevPos;

void setup() {
	Assets::window.setFramerateLimit(60);

	Assets::player.setSpriteSheet("resources/pacman.png");
	Assets::player.getSprite().setTexture(Assets::player.getSpriteSheet());
	Assets::player.getSprite().setTextureRect(sf::IntRect(
		0,
		0,
		32,
		32
	));

	Assets::player.getSprite().setPosition(Assets::player.getPos());

	Assets::enemy.setSpriteSheet("resources/ghost.png");
	Assets::enemy.getSprite().setTexture(Assets::enemy.getSpriteSheet());
	Assets::enemy.getSprite().setTextureRect(sf::IntRect(
		0,
		0,
		32,
		32
	));

	Assets::enemy.getSprite().setPosition(Assets::enemy.getPos());

	Assets::objects.push_back(&Assets::player);
	Assets::objects.push_back(&Assets::enemy);
}