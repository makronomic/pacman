#include "Animation.h"
#include "Frames.h"
#include "motion.h"
#include "object.h"
#include "soundSys.h"
#include <iostream>
using namespace std;

//int counter = Frames::framecounter();
// enemydirection enter frame number multiple of 2
// ghostcolor enter 0 or multiples of 1 to change colors

void Animation::enemyState(Object& x, int enemyDirection, int ghostColor, int& counter) {
	if (counter % x.framechange == 0) {
		x.getSprite().setTextureRect(
			sf::IntRect(16 * x.Object::currentframe, ghostColor * 16, 16, 16)
		);
		x.Object::currentframe++;
		x.Object::currentframe = (x.Object::currentframe % 2) + enemyDirection;
	}
}
int counter;
int y=0;
void Animation::motionPicture(Object& x) {

	if (x.getType() == Object::Type::PLAYER) {

		if (x.Object::alive)
		{
			soundSys::playMusic(2);           //play in game music  (NOT WORKING)
			soundSys::playsound(2);			  //play waka waka		(NOT WORKING)

			if (counter % x.Object::framechange == 0)
			{
				x.Object::currentframe++;
				x.currentframe %= x.Object::maxframe;
				//cout << x.currentframe << "\n";
				x.getSprite().setTextureRect(
					sf::IntRect(32 * x.currentframe, 0, 32, 32));
			}
			counter++;
			counter %= 60;
			cout << counter<<"\n";
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

	// next part is enemy animation try

	else if (x.getType() == Object::Type::ENEMY) {
		if (x.alive) {
			if (x.state == 'u') {
				enemyState(x, 4, x.getId(), counter);
			} else if (x.state == 'l') {
				enemyState(x, 2, x.getId(), counter);
			} else if (x.state == 'd') {
				enemyState(x, 6, x.getId(), counter);
			} else if (x.state == 'r') {
				enemyState(x, 0, x.getId(), counter);
			}
		} else {
			if (x.state == 'u') {
				enemyState(x, 4, x.getId(), counter);
			} else if (x.state == 'l') {
				enemyState(x, 2, x.getId(), counter);
			} else if (x.state == 'd') {
				enemyState(x, 6, x.getId(), counter);
			} else if (x.state == 'r') {
				enemyState(x, 0, x.getId(), counter);
			}
		}
	}
}