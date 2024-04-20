#pragma once
#include "MainMenu.h"

class ChooseLevelMenu : public MainMenu
{
    int selectedButton = 0;

public:
    ChooseLevelMenu(int width, int height);
    void drawSubMenu(sf::RenderWindow& window);
    int getSelectedButton(sf::RenderWindow& window) override;
};

