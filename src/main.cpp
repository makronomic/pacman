#include "../include/motion.h"
#include "../include/object.h"
#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 800), "Test Window");
	window.setFramerateLimit(30);

	sf::CircleShape shape(100.f);
	Object shapeObject({ 0.f, 0.f }, 2.f, Object::Type::PLAYER);

	shape.setFillColor(sf::Color::Green);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		move(shapeObject);
		shape.setPosition(shapeObject.getPos());

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}