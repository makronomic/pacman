#include "Animation.h"
#include "Frames.h"
#include "motion.h"
#include "object.h"
#include <iostream>
using namespace std;

void Animation::motionPicture(Object& x) {
	int counter = Frames::framecounter();

	if (x.getType() == Object::Type::PLAYER) {
		if (counter % x.Object::framechange() == 0) {
			x.getSprite().setTextureRect(sf::IntRect(
				32 * x.Object::currentframe,
				0,
				32,
				32
			));
			x.Object::currentframe++;
			x.Object::currentframe %= x.maxframe();
			// std::cout << "f: " << x.Object::currentframe << "\n";
			// std::cout << "c: " << counter << "\n";
		}
		if (x.state == 'u') {
			x.getSprite().setOrigin(x.getSprite().getLocalBounds().height, 0);
			x.getSprite().setScale(1, 1);
			x.getSprite().setRotation(270);
		} else if (x.state == 'l') {
			x.getSprite().setRotation(0);
			x.getSprite().setOrigin(x.getSprite().getLocalBounds().width, 0);
			x.getSprite().setScale(-1, 1);
		} else if (x.state == 'd') {
			x.getSprite().setOrigin(0, 0);
			x.getSprite().setScale(1, -1);
			x.getSprite().setRotation(90);
		} else {
			x.getSprite().setRotation(0);
			x.getSprite().setOrigin(0, 0);
			x.getSprite().setScale(1, 1);
		}
	}
}