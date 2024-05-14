#pragma once

#include <SFML/Audio.hpp> 

class soundSys
{
public:

    static bool isMenuMusicPlaying;
    static bool isIGMplaying;
    static bool isWakaWaka;
    static sf::SoundBuffer clickBuffer; 
    static sf::SoundBuffer B_deathSound;
    static sf::SoundBuffer B_wakaWAKA;
    
    static sf::Sound clickSound;
    static sf::Sound deathSound;
    static sf::Sound wakaWAKA;

    static sf::Music menuMusic;
    static sf::Music inGameMusic;

    static void setup();
    static void playMusic(int y);
    static void playsound(int z);
    static void stopMusic(int x);
    static void stopSound(int w);
};

