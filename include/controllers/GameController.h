#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <filesystem>
#include <iostream>
#include <vector>

#include "../Constants.h"
#include "../helpers/DrawText.h"
#include "../models/Projectile.h"
#include "../models/Player.h"
#include "../helpers/EndGameMenu.h"
#include "../helpers/MainMenu.h"
// #include "../controllers/SoundSystemController.h"
#include "../controllers/BarrierController.h"
#include "../controllers/EnemyContoller.h"
#include "../controllers/CollisionController.h"
#include "./StoreGameStateController.h"
#include "./abstracts/Serializeable.h"

class GameController : public Serializable
{
private:
    GameController();

    sf::RenderWindow gameWindow;
    std::unique_ptr<CollisionController> collisionController;
    std::unique_ptr<BarrierController> barrierController;
    std::unique_ptr<EnemyController> enemyController;

    std::unique_ptr<MainMenu> mainMenu;
    std::unique_ptr<EndGameMenu> endGameMenu;
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Projectile>> playerProjectiles;

    std::shared_ptr<Player> createPlayer();

    int level = 1;
    int pastScore = 0;
    int totalScore = 0;

    void createAndSetUpGameWindow();
    void evaluateEndGameConditions();
    void startEndGameLoop();
    void moveToNextLevel();
    void drawGameSessionInfo();
    void createBarriers(); // perse this method is not creating barriers but abstracts this process
    void createEnemies();  // perse this method is not creating enemies but abstracts this process

    nlohmann::json serialize() const override;
    void deserialize(const nlohmann::json &json) override;

public:
    // --Singleton pattern implementation--
    static GameController &getInstance();
    GameController(GameController const &) = delete;
    void operator=(GameController const &) = delete;

    int currentGameState;
    std::unique_ptr<StoreGameStateController> storeGameStateController;

    sf::RenderWindow &getWindow();
    sf::Vector2u getWindowSize();

    void startMenuLoop();
    void startGameLoop();

    void runGameLoop();
    void updateGame();
    void renderGame();

    void handleWindowEvents();
    void removeMarkedProjectiles(std::vector<std::shared_ptr<Projectile>> &projectiles);
};

#endif // GAMECONTROLLER_H