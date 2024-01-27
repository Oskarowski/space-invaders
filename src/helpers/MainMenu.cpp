#include "../../include/helpers/MainMenu.h"

MainMenu::MainMenu()
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

    setupText(playText, "Play New", TEXT_SPACING);
    setupText(loadFromSaveText, "Load Last", 2 * TEXT_SPACING);
    setupText(exitText, "Exit", 3 * TEXT_SPACING);
}

void MainMenu::setupText(sf::Text &text, const std::string &content, float yOffset)
{
    text.setString(content);
    text.setFont(font);
    text.setCharacterSize(Constants::MENU_FONT_SIZE);

    // "Calculate" the center position for the text
    float textX = (Constants::WINDOW_WIDTH - text.getLocalBounds().width) / 2.0f;
    float textY = Constants::WINDOW_HEIGHT / 8 + yOffset;

    text.setPosition(textX, textY);
}

void MainMenu::handleMenuEvents()
{
    // Set text color based on selected option
    switch (selectedOption)
    {
    case PLAY_OPTION_SELECTED:
        playText.setFillColor(sf::Color::Red);
        exitText.setFillColor(sf::Color::White);
        loadFromSaveText.setFillColor(sf::Color::White);
        break;

    case EXIT_OPTION_SELECTED:
        playText.setFillColor(sf::Color::White);
        exitText.setFillColor(sf::Color::Red);
        loadFromSaveText.setFillColor(sf::Color::White);
        break;

    case LOAD_FROM_SAVE_OPTION_SELECTED:
        playText.setFillColor(sf::Color::White);
        exitText.setFillColor(sf::Color::White);
        loadFromSaveText.setFillColor(sf::Color::Red);
        break;

    default:
        break;
    }
}

void MainMenu::draw(sf::RenderWindow &window)
{
    window.clear();

    window.draw(backgroundSprite);

    window.draw(playText);
    window.draw(exitText);
    window.draw(loadFromSaveText);

    window.display();
}

int MainMenu::run(sf::RenderWindow &window)
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
                    selectedOption = (selectedOption - 1 + 3) % 3;
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    selectedOption = (selectedOption + 1) % 3;
                }
                else if (event.key.code == sf::Keyboard::Enter)
                {
                    switch (selectedOption)
                    {
                    case PLAY_OPTION_SELECTED:
                        return Constants::START_GAME;

                    case LOAD_FROM_SAVE_OPTION_SELECTED:
                        return Constants::LOAD_LAST_GAME;

                    default:
                        window.close();
                        break;
                    }
                }
            }
        }

        handleMenuEvents();
        this->draw(window);
    }

    // to make the compiler happy :) that we return something
    return Constants::START_GAME;
}