#pragma once

#include <map>
#include <SFML/Graphics.hpp>

class Object {
public:
	enum class Type {
		PLAYER,
		ENEMY,

		TYPE_MAX,
	};
private:
	sf::Vector2f pos;
	float spd;
	Type type;

	sf::Sprite spr;
	sf::Texture ss;

	int id;
public:
	// to create only one ghost of each color
	//static std::map<ID, bool> existingGhosts;
	//static std::map<ID, bool> loadedGhosts;

	Object(const sf::Vector2f& pPos = { 0.f, 0.f }, float pSpd = 1.f, const Type& pType = Type::TYPE_MAX);

	int currentframe = 0;

	bool alive = true;

	char state = 'r';

	int framechange = 5;

	void setPos(float, float);

	void setSpd(float);

	void setSpriteSheet(std::string_view);

	float getSpeed() const;

	void setId(int);

	int getId() const;

	int maxframe();



	Type getType() const;

	sf::Vector2f& getPos();

	sf::Sprite& getSprite();

	sf::Texture& getSpriteSheet();
};