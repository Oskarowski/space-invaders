#ifndef ENEMY_CONTROLLER_H
#define ENEMY_CONTROLLER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "../models/Enemy.h"
#include "../Constants.h"

class EnemyController
{
private:
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Projectile>> projectiles;

    short enemiesCount = 0;
    int enemiesDestroyed = 0;

    void removeMarkedEnemies();
    void removeMarkedProjectiles(std::vector<std::shared_ptr<Projectile>> &projectiles);

public:
    EnemyController();

    void createEnemies(int level);
    void loadEnemies(const nlohmann::json &enemiesJson);

    std::vector<std::shared_ptr<Enemy>> &getEnemies();
    std::vector<std::shared_ptr<Projectile>> &getProjectiles();

    void update();

    void render(sf::RenderWindow &window);

    short getEnemiesCount();
    int getCountEnemiesDestroyed();

    // Method to serialize all enemies and combine them into a JSON array
    nlohmann::json serialize() const;

    void nextLevel(int level);
};

#endif // ENEMY_CONTROLLER_H
