#include "setup.h"

// definitions 
sf::RenderWindow Assets::window(sf::VideoMode(800, 800), "Test Window");

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

	Assets::enemy.setSpriteSheet("resources/ghost.png");
	Assets::enemy.getSprite().setTexture(Assets::enemy.getSpriteSheet());
	Assets::enemy.getSprite().setTextureRect(sf::IntRect(
		0,
		0,
		32,
		32
	));


}