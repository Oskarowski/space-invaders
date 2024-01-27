#include "../../include/helpers/DrawText.h"

void DrawText::drawText(sf::RenderWindow &window, std::string text, float x, float y, sf::Color color)
{
    sf::Font font;
    font.loadFromFile("assets/DejaVuSans-Bold.ttf");

    sf::Text textToDraw;
    textToDraw.setFont(font);
    textToDraw.setString(text);
    textToDraw.setCharacterSize(24);
    textToDraw.setFillColor(color);
    textToDraw.setPosition(x, y);

    window.draw(textToDraw);
}