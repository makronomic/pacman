#pragma once

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

public:
	Object(const sf::Vector2f& pPos = { 0.f, 0.f }, float pSpd = 1.f, const Type& pType = Type::TYPE_MAX);

	void setPos(float, float);

	void setSpd(float);

	void setSpriteSheet(std::string_view);

	float getSpeed() const;

	Type getType() const;

	sf::Vector2f& getPos();

	sf::Sprite& getSprite();

	sf::Texture& getSpriteSheet();
};