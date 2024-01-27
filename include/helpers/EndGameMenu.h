#ifndef END_GAME_MENU_H
#define END_GAME_MENU_H

#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>

#include "../Constants.h"

class EndGameMenu
{
private:
    const int TEXT_SPACING = 200;
    static constexpr int PLAY_AGAIN_OPTION_SELECTED = 0;
    static constexpr int EXIT_OPTION_SELECTED = 1;

    sf::Font font;
    sf::Text playAgainText;
    sf::Text exitGameText;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    int selectedOption;

    void setupText(sf::Text &text, const std::string &content, float yOffset);

    void handleMenuEvents();
    void draw(sf::RenderWindow &window);

public:
    EndGameMenu();
    ~EndGameMenu() = default;

    int run(sf::RenderWindow &window);
};

#endif // END_GAME_MENU_H