#pragma once

#include "SFML/Graphics.hpp"

class Object {
public:
	enum class Type {
		PLAYER,
		ENEMY,

		TYPE_MAX,
	};

private:
	sf::Vector2f pos;
	const float spd;
	Type type;

public:
	Object(const sf::Vector2f& v = { 0.f, 0.f }, float s = 1.f, const Type& t = Type::TYPE_MAX);

	void setPos(float, float);

	float getSpeed() const;

	Type getType() const;

	sf::Vector2f getPos() const;
};