
#include "Animation.h"
#include "assets.h"
#include "check_bound.h"
#include "Frames.h"
#include "MainMenu.h"
#include "motion.h"
#include "Object.h"
#include "setup.h"
#include <iostream>
#include <set>
#include <SFML/Graphics.hpp>


//helper function during development, returns mouse position in the window when you click anywhere 
void mousePos(sf::RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		std::cout << "X: " << mousePosition.x << " Y: " << mousePosition.y << std::endl;
	}
}

int main() {
	setup();

	//MainMenu mainMenu(Assets::window.getSize().x, Assets::window.getSize().y);
	//int chosenLevel = -1;
	//int chosenDifficulty = -1;

	Assets::level = Assets::level.createMapFromFile("world1.txt");
	//Assets::level.printAdjList();


	while (Assets::window.isOpen()) {
		// set of input keys in the last frame
		sf::Event event;
		mousePos(Assets::window);
		while (Assets::window.pollEvent(event)) 
		{

			if (event.type == sf::Event::Closed)
				Assets::window.close();
			else if (event.type == sf::Event::KeyPressed)
				Assets::keyBuf.insert(event.key.code);
			else if (event.type == sf::Event::KeyReleased)
				Assets::keyBuf.erase(event.key.code);
		}

		Animation::motionPicture(Assets::player);

		/*for (auto it = Assets::objects.begin(); it != Assets::objects.end(); it++) {
			Motion::handleCollision(**it);
		}*/

		if (Frames::framecounter() % 60 == 0) {
			std::cout << "Last frame pos: (" << Assets::prevPos[&Assets::player].x << ", " << Assets::prevPos[&Assets::player].y << ")\n";
		}

		Motion::move(Assets::player, Assets::keyBuf);

		Motion::move(Assets::enemy);

		Assets::window.clear();
		Assets::level.drawLevel(Assets::window);
		Assets::window.draw(Assets::enemy.getSprite());
		Assets::window.display();

		// clear the input buffer for the next frame
		Assets::keyBuf.clear();
	}

	return 0;
}

