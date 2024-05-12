#include "setup.h"

// definitions
int Assets::res = 800;

sf::RenderWindow Assets::window(sf::VideoMode(Assets::res, Assets::res),
								"Test Window");

std::set<sf::Keyboard::Key> Assets::keyBuf;

Object Assets::player({ 200.f, 300.f }, 2.f, Object::Type::PLAYER);

// add id as a parameter
Object Assets::enemyRed({ 400.f, 300.f }, 2.f, Object::Type::ENEMY);
Object Assets::enemyPink({ 450.f, 300.f }, 2.f, Object::Type::ENEMY);
Object Assets::enemyBlue({ 500.f, 300.f }, 2.f, Object::Type::ENEMY);
Object Assets::enemyOrange({ 550.f, 300.f }, 2.f, Object::Type::ENEMY);

std::vector<Object*> Assets::objects;
std::map<Object*, sf::Vector2f> Assets::prevPos;

void setup() {
	Assets::window.setFramerateLimit(60);

	Assets::player.setSpriteSheet("resources/pacman.png");
	Assets::player.getSprite().setTexture(Assets::player.getSpriteSheet());
	Assets::player.getSprite().setTextureRect(sf::IntRect(0, 0, 32, 32));

	Assets::player.getSprite().setPosition(Assets::player.getPos());
	Assets::player.framechange = 5;

	Assets::enemyRed.setSpriteSheet("resources/ghosts.png");
	Assets::enemyRed.getSprite().setTexture(Assets::enemyRed.getSpriteSheet());
	Assets::enemyRed.getSprite().setTextureRect(sf::IntRect(0, 0, 16, 16));
	Assets::enemyRed.framechange = 8;
	Assets::enemyRed.getSprite().setPosition(Assets::enemyRed.getPos());
	Assets::enemyRed.getSprite().setScale(5, 5);


	Assets::enemyPink.setSpriteSheet("resources/ghosts.png");
	Assets::enemyPink.getSprite().setTexture(Assets::enemyPink.getSpriteSheet());
	Assets::enemyPink.getSprite().setTextureRect(sf::IntRect(0, 0, 16, 16));
	Assets::enemyPink.framechange = 8;
	Assets::enemyPink.getSprite().setPosition(Assets::enemyPink.getPos());
	Assets::enemyPink.getSprite().setScale(5, 5);


	Assets::enemyBlue.setSpriteSheet("resources/ghosts.png");
	Assets::enemyBlue.getSprite().setTexture(Assets::enemyBlue.getSpriteSheet());
	Assets::enemyBlue.getSprite().setTextureRect(sf::IntRect(0, 0, 16, 16));
	Assets::enemyBlue.framechange = 8;
	Assets::enemyBlue.getSprite().setPosition(Assets::enemyBlue.getPos());
	Assets::enemyBlue.getSprite().setScale(5, 5);


	Assets::enemyOrange.setSpriteSheet("resources/ghosts.png");
	Assets::enemyOrange.getSprite().setTexture(Assets::enemyOrange.getSpriteSheet());
	Assets::enemyOrange.getSprite().setTextureRect(sf::IntRect(0, 0, 16, 16));
	Assets::enemyOrange.framechange = 8;
	Assets::enemyOrange.getSprite().setPosition(Assets::enemyOrange.getPos());
	Assets::enemyOrange.getSprite().setScale(5, 5);

	Assets::objects.push_back(&Assets::player);
	Assets::objects.push_back(&Assets::enemyRed);
	Assets::objects.push_back(&Assets::enemyPink);
	Assets::objects.push_back(&Assets::enemyBlue);
	Assets::objects.push_back(&Assets::enemyOrange);
}

LevelMap Assets::level;