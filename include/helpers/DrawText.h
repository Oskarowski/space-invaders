#ifndef DRAW_TEXT_H
#define DRAW_TEXT_H

#include <SFML/Graphics.hpp>

class DrawText
{
public:
    DrawText() = default;
    ~DrawText() = default;

    void static drawText(sf::RenderWindow &window, std::string text, float x, float y, sf::Color color);
};

#endif // DRAW_TEXT_H