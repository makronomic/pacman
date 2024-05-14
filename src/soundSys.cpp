#include "soundSys.h"
#include <iostream>
#include <SFML/Audio.hpp> 

using namespace std;

bool soundSys::isMenuMusicPlaying = true;
bool soundSys::isIGMplaying = false;

sf::SoundBuffer soundSys::clickBuffer;
sf::SoundBuffer soundSys::B_deathSound;
sf::SoundBuffer soundSys::B_wakaWAKA;

sf::Sound soundSys::clickSound;
sf::Sound soundSys::deathSound;
sf::Sound soundSys::wakaWAKA;

sf::Music soundSys::menuMusic;
sf::Music soundSys::inGameMusic;

void soundSys::setup() {
	inGameMusic.openFromFile("resources/audio/IGM.ogg");
	menuMusic.openFromFile("resources/audio/theme.ogg");

	B_deathSound.loadFromFile("resources/audio/GameOver.ogg");
	B_wakaWAKA.loadFromFile("resources/audio/WakaWaka.ogg");
	clickBuffer.loadFromFile("resources/audio/select.ogg");

	deathSound.setBuffer(B_deathSound);
	wakaWAKA.setBuffer(B_wakaWAKA);
	clickSound.setBuffer(clickBuffer);
}

void soundSys::stopMusic(int x) {
	if (x == 1) {
		menuMusic.stop();
		isMenuMusicPlaying = false;
	}
	else {
		inGameMusic.stop();
		isIGMplaying = false;
	}
}

void soundSys::playMusic(int y) {
	if (y == 1) {
		menuMusic.setVolume(50);
		menuMusic.play();
		menuMusic.setLoop(true);
		isMenuMusicPlaying = true;
	}
	else {
		inGameMusic.setVolume(50);
		inGameMusic.play();
		inGameMusic.setLoop(true);
		isIGMplaying = true;
	}
}

void soundSys::playsound(int z) {
	if (z == 1) {
		clickSound.play();
	}
	else if (z == 2) {
		menuMusic.setVolume(50);
		wakaWAKA.play();
		wakaWAKA.setLoop(true);
	}
	else {
		deathSound.play();
	}
}
void soundSys::stopSound(int w) {
	if (w == 1) {
		clickSound.stop();
	}
	else if (w == 2) {
		wakaWAKA.stop();
	}
	else {
		deathSound.stop();
	}
}