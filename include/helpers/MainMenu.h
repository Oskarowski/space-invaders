#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>

#include "../Constants.h"

class MainMenu
{
private:
    const int TEXT_SPACING = 200;
    static constexpr int PLAY_OPTION_SELECTED = 0;
    static constexpr int LOAD_FROM_SAVE_OPTION_SELECTED = 1;
    static constexpr int EXIT_OPTION_SELECTED = 2;

    sf::Font font;
    sf::Text playText;
    sf::Text exitText;
    sf::Text loadFromSaveText;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    int selectedOption;

    void setupText(sf::Text &text, const std::string &content, float yOffset);

    void handleMenuEvents();
    void draw(sf::RenderWindow &window);

public:
    MainMenu();
    ~MainMenu() = default;

    int run(sf::RenderWindow &window);
};

#endif // MAINMENU_H