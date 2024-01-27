#include "../../include/controllers/GameController.h"

GameController::GameController()
{
    createAndSetUpGameWindow();
    storeGameStateController = std::make_unique<StoreGameStateController>();

    // soundSystemController = std::make_unique<SoundSystemController>();
}

GameController &GameController::getInstance()
{
    static GameController instance;
    return instance;
}

nlohmann::json GameController::serialize() const
{
    nlohmann::json gameControllerJson;

    gameControllerJson["level"] = level;
    gameControllerJson["past_score"] = totalScore;

    return gameControllerJson;
}

void GameController::deserialize(const nlohmann::json &json)
{
    try
    {
        level = json.at("level");
        pastScore = json.at("past_score");
    }
    catch (const std::exception &e)
    {
        std::cerr << "GameController::deserialize e.what() " << e.what() << '\n';
    }
}

void GameController::createAndSetUpGameWindow()
{
    gameWindow.create(sf::VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT), "Space Invaders", sf::Style::Titlebar);

    // Set the window as non-resizable
    gameWindow.setView(sf::View(sf::FloatRect(0, 0, Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT)));

    gameWindow.setFramerateLimit(60);

    // Get the desktop resolution
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    int centerX = (desktopMode.width - Constants::WINDOW_WIDTH) / 2;
    int centerY = (desktopMode.height - Constants::WINDOW_HEIGHT) / 2;
    gameWindow.setPosition(sf::Vector2i(centerX, centerY));
}

sf::RenderWindow &GameController::getWindow()
{
    return gameWindow;
}

sf::Vector2u GameController::getWindowSize()
{
    return gameWindow.getSize();
}

void GameController::startEndGameLoop()
{
    currentGameState = Constants::END_GAME;

    endGameMenu = std::make_unique<EndGameMenu>();

    int optionFromMenu = endGameMenu->run(getWindow());

    switch (optionFromMenu)
    {
    case Constants::START_GAME:
        currentGameState = Constants::INIT_GAME;
        storeGameStateController->resetLoadedStatesToNulls();

        this->startGameLoop();
        break;

    case Constants::EXIT:
        currentGameState = Constants::EXIT;
        gameWindow.close();
        break;
    default:
        EXIT_FAILURE;
    }
}

void GameController::drawGameSessionInfo()
{
    std::string levelText = "Level: " + std::to_string(level);

    // TODO if added more enemies types, add calculating score based on destroyed enemies
    totalScore = static_cast<int>(pastScore + enemyController->getCountEnemiesDestroyed() * (Constants::BASE_ENEMY_SCORE_MULTIPLIER + level * Constants::ADDITIONAL_ENEMY_SCORE_MULTIPLIER_PER_LEVEL));
    std::string scoreText = "Score: " + std::to_string(totalScore);
    std::string lifeText = "Life: " + std::to_string(player->getHealthPoints());

    float screenWidth = static_cast<float>(getWindow().getSize().x);
    float horizontalSpacing = screenWidth * 0.3;

    float xPosition = 80.0;
    float yPosition = 25.0;

    DrawText::drawText(getWindow(), lifeText, xPosition, yPosition, sf::Color::Red);
    DrawText::drawText(getWindow(), levelText, xPosition + horizontalSpacing, yPosition, sf::Color::Blue);
    DrawText::drawText(getWindow(), scoreText, xPosition + 2 * horizontalSpacing, yPosition, sf::Color::Green);
}

void GameController::startMenuLoop()
{
    currentGameState = Constants::MAIN_MENU;

    mainMenu = std::make_unique<MainMenu>();

    int optionFromMenu = mainMenu->run(getWindow());

    switch (optionFromMenu)
    {
    case Constants::START_GAME:
        currentGameState = Constants::INIT_GAME;
        this->startGameLoop();
        break;

    case Constants::LOAD_LAST_GAME:
        currentGameState = Constants::TRY_TO_LOAD_SAVE;

        if (StoreGameStateController::hasSavedStateFiles())
        {
            // std::cout << "Loading last game\n";
            try
            {
                nlohmann::json storedPlayer = StoreGameStateController::loadState("saved_player.json");
                nlohmann::json storedBarriers = StoreGameStateController::loadState("saved_barriers.json");
                nlohmann::json storedEnemies = StoreGameStateController::loadState(Constants::SAVED_ENEMIES_FILE_NAME);
                nlohmann::json storedGameController = StoreGameStateController::loadState("saved_game_controller.json");
                storeGameStateController->setLoadedPlayerState(storedPlayer);
                storeGameStateController->setLoadedBarriersState(storedBarriers);
                storeGameStateController->setLoadedGameControllerState(storedGameController);
                storeGameStateController->setLoadedEnemiesState(storedEnemies);
            }
            catch (const std::exception &e)
            {
                // we want to continue the game even if we can't load the last game
                // std::cerr << "Error loading game state: " << e.what() << std::endl;
            }
        }

        this->startGameLoop();
        break;

    default:
        EXIT_FAILURE;
    }
}

void GameController::renderGame()
{
    gameWindow.clear();

    for (auto &projectile : playerProjectiles)
    {
        projectile->render(gameWindow);
    }

    enemyController->render(gameWindow);

    barrierController->render(gameWindow);

    player->render(gameWindow);

    drawGameSessionInfo();

    gameWindow.display();
}

void GameController::moveToNextLevel()
{
    ++level;

    enemyController->createEnemies(level);
    enemyController->nextLevel(level);

    barrierController->heal(Constants::BARRIER_BASE_HEAL_MULTIPLAYER + level * Constants::BARRIER_ADDITIONAL_HEAL_MULTIPLAYER_PER_LEVEL);

    player->heal(Constants::PLAYER_BASE_HEAL_MULTIPLAYER + level * Constants::PLAYER_ADDITIONAL_HEAL_MULTIPLAYER_PER_LEVEL);
}

void GameController::evaluateEndGameConditions()
{
    if (player->getHealthPoints() <= 0)
    {
        currentGameState = Constants::END_GAME_PLAYER_LOST_HEALTH;
        startEndGameLoop();
    }

    if (enemyController->getEnemiesCount() <= 0)
    {
        currentGameState = Constants::ALL_ENEMIES_DESTROYED;
        moveToNextLevel();
    }
}

void GameController::removeMarkedProjectiles(std::vector<std::shared_ptr<Projectile>> &projectiles)
{
    auto it = projectiles.begin();
    while (it != projectiles.end())
    {
        if ((*it)->isMarkedForDeletion())
        {
            it = projectiles.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void GameController::updateGame()
{
    for (auto &projectile : playerProjectiles)
    {
        projectile->update(getWindow());
    }

    enemyController->update();
    barrierController->update();

    collisionController->checkCollisions(enemyController->getEnemies(), playerProjectiles);
    collisionController->checkCollisions(player, enemyController->getProjectiles());
    collisionController->checkCollisions(barrierController->getBarriers(), enemyController->getProjectiles());
    collisionController->checkCollisions(barrierController->getBarriers(), playerProjectiles);

    removeMarkedProjectiles(playerProjectiles);

    evaluateEndGameConditions();
}

void GameController::handleWindowEvents()
{
    sf::Event event;
    while (gameWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            gameWindow.close();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player->moveLeft(getInstance());
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player->moveRight(getInstance());
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        player->shoot(playerProjectiles);
    }

    // when pressed save game state
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        StoreGameStateController::saveState(player->serialize(), "saved_player.json");
        StoreGameStateController::saveState(barrierController->serialize(), "saved_barriers.json");
        StoreGameStateController::saveState(this->serialize(), "saved_game_controller.json");
        StoreGameStateController::saveState(enemyController->serialize(), Constants::SAVED_ENEMIES_FILE_NAME);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
    {
        std::cout << "Amount of player projectiles: " << playerProjectiles.size() << "\n";
        std::cout << "Amount of enemies projectiles: " << enemyController->getProjectiles().size() << "\n";
    }
}

void GameController::createBarriers()
{
    if (storeGameStateController->getLoadedBarriersState() != NULL)
    {
        barrierController->loadBarriers(storeGameStateController->getLoadedBarriersState());
    }
    else
    {
        barrierController->createBarriers();
    }
}

void GameController::createEnemies()
{
    if (storeGameStateController->getLoadedEnemiesState() != NULL)
    {
        enemyController->loadEnemies(storeGameStateController->getLoadedEnemiesState());
    }
    else
    {
        enemyController->createEnemies(level);
    }
}

void GameController::runGameLoop()
{
    currentGameState = Constants::GAME_RUNNING;
    // std::cout << "Game loop started\n";

    while (gameWindow.isOpen())
    {
        handleWindowEvents();

        updateGame();

        renderGame();
    }
}

std::shared_ptr<Player> GameController::createPlayer()
{
    if (storeGameStateController->getLoadedPlayerState() != NULL)
    {
        // std::cout << storeGameStateController->getLoadedPlayerState().dump(4) << std::endl;

        const int playerXPos = storeGameStateController->getLoadedPlayerState().at("x_pos");
        const int playerYPos = storeGameStateController->getLoadedPlayerState().at("y_pos");
        const int playerHealth = storeGameStateController->getLoadedPlayerState().at("health_points");

        return std::make_shared<Player>(playerXPos, playerYPos, Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT, playerHealth);
    }

    const int playerXPos = Constants::WINDOW_WIDTH / 2 - Constants::PLAYER_WIDTH / 2;
    const int playerYPos = Constants::WINDOW_HEIGHT - 100;
    return std::make_shared<Player>(playerXPos, playerYPos, Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT, Constants::PLAYER_BASE_HEALTH);
}

void GameController::startGameLoop()
{
    gameWindow.clear();

    // soundSystemController->loadBackgroundMusic();

    currentGameState = Constants::START_GAME;

    if (storeGameStateController->getLoadedGameControllerState() != NULL)
    {
        deserialize(storeGameStateController->getLoadedGameControllerState());
    }
    else
    {
        level = 1;
        pastScore = 0;
        totalScore = 0;
    }

    player = createPlayer();

    enemyController = std::make_unique<EnemyController>();

    collisionController = std::make_unique<CollisionController>();

    barrierController = std::make_unique<BarrierController>();

    createBarriers();

    createEnemies();

    runGameLoop();
}