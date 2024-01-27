#include "../../include/helpers/EndGameMenu.h"

EndGameMenu::EndGameMenu()
{
    if (!font.loadFromFile("assets/DejaVuSans-Bold.ttf"))
    {
        std::filesystem::path currentPath = std::filesystem::current_path();
        std::cout << "Current working directory: " << currentPath << std::endl;
        std::cerr << "Failed to load font\n";
    }

    if (!backgroundTexture.loadFromFile("assets/background_menu.png"))
    {
        std::cerr << "Failed to load background texture\n";
    }

    // Set up background sprite
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0, 0);

    setupText(playAgainText, "New Game", TEXT_SPACING);
    setupText(exitGameText, "Exit", 2 * TEXT_SPACING);
}

void EndGameMenu::setupText(sf::Text &text, const std::string &content, float yOffset)
{
    text.setString(content);
    text.setFont(font);
    text.setCharacterSize(Constants::MENU_FONT_SIZE);

    // "Calculate" the center position for the text
    float textX = (Constants::WINDOW_WIDTH - text.getLocalBounds().width) / 2.0f;
    float textY = Constants::WINDOW_HEIGHT / 6 + yOffset;

    text.setPosition(textX, textY);
}

void EndGameMenu::handleMenuEvents()
{
    // Set text color based on selected option
    switch (selectedOption)
    {
    case PLAY_AGAIN_OPTION_SELECTED:
        playAgainText.setFillColor(sf::Color::Red);
        exitGameText.setFillColor(sf::Color::White);
        break;

    case EXIT_OPTION_SELECTED:
        playAgainText.setFillColor(sf::Color::White);
        exitGameText.setFillColor(sf::Color::Red);
        break;

    default:
        break;
    }
}

void EndGameMenu::draw(sf::RenderWindow &window)
{
    window.clear();

    window.draw(backgroundSprite);

    window.draw(playAgainText);
    window.draw(exitGameText);

    window.display();
}

int EndGameMenu::run(sf::RenderWindow &window)
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Check for arrow key presses
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    selectedOption = (selectedOption - 1 + 2) % 2;
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    selectedOption = (selectedOption + 1) % 2;
                }
                else if (event.key.code == sf::Keyboard::Enter)
                {
                    switch (selectedOption)
                    {
                    case PLAY_AGAIN_OPTION_SELECTED:
                        // std::cout << "Play again!" << std::endl;
                        return Constants::START_GAME;

                    case EXIT_OPTION_SELECTED:
                        return Constants::EXIT;

                    default:
                        window.close();
                        break;
                    }
                }
            }
            // std::cout << "Selected option: " << selectedOption << std::endl;
        }

        handleMenuEvents();
        this->draw(window);
    }

    // to make the compiler happy :) that we return something
    return Constants::START_GAME;
}