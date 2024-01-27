#include "../../include/controllers/EnemyContoller.h"

EnemyController::EnemyController()
{
}

std::vector<std::shared_ptr<Enemy>> &EnemyController::getEnemies()
{
    return enemies;
}

std::vector<std::shared_ptr<Projectile>> &EnemyController::getProjectiles()
{
    return projectiles;
}

short EnemyController::getEnemiesCount()
{
    return enemiesCount;
}

int EnemyController::getCountEnemiesDestroyed()
{
    return enemiesDestroyed;
}

void EnemyController::removeMarkedEnemies()
{
    for (auto it = enemies.begin(); it != enemies.end();)
    {
        if ((*it)->isMarkedForDeletion())
        {
            it = enemies.erase(it);
            --enemiesCount;
            ++enemiesDestroyed;
        }
        else
        {
            ++it;
        }
    }
}

void EnemyController::removeMarkedProjectiles(std::vector<std::shared_ptr<Projectile>> &projectiles)
{

    for (auto it = projectiles.begin(); it != projectiles.end();)
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

void EnemyController::createEnemies(int level)
{

    // const int rows = std::min(level, Constants::MAX_ENEMIES_ROWS_COUNT);
    const int rows = 5;
    const int cols = 5;
    const float spacingX = 100.0f;
    const float spacingY = 80.0f;
    const int enemyWidth = Constants::ENEMY_WIDTH;
    const int enemyHeight = Constants::ENEMY_HEIGHT;
    const int initialYPos = 150;

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            float xPos = static_cast<float>(col * spacingX + enemyWidth / 2);
            float yPos = static_cast<float>(row * spacingY + initialYPos);

            enemies.push_back(std::make_shared<Enemy>(xPos, yPos, enemyWidth, enemyHeight, 100, 4.0f, Constants::ENEMY_BASE_SHOOT_PROBABILITY));
        }
    }

    enemiesCount = enemies.size();
}

void EnemyController::render(sf::RenderWindow &window)
{
    for (auto &enemy : enemies)
    {
        enemy->render(window);
    }

    for (auto &projectile : projectiles)
    {
        projectile->move();

        if (projectile->isOutOfBounds())
        {
            projectile->markForDeletion();
        }

        projectile->render(window);
    }
}

void EnemyController::update()
{
    for (auto &enemy : enemies)
    {
        enemy->update(getProjectiles());
    }

    removeMarkedEnemies();

    removeMarkedProjectiles(getProjectiles());
}

nlohmann::json EnemyController::serialize() const
{
    nlohmann::json enemiesArray;

    for (const auto &enemy : enemies)
    {
        enemiesArray.push_back(enemy->serialize());
    }

    return enemiesArray;
}

void EnemyController::loadEnemies(const nlohmann::json &enemiesJson)
{
    for (const auto &enemyJson : enemiesJson)
    {
        const int xPos = enemyJson.at("x_pos");
        const int yPos = enemyJson.at("y_pos");
        const int healthPoints = enemyJson.at("health_points");
        const float shootProbability = enemyJson.at("shoot_probability");

        enemies.push_back(std::make_shared<Enemy>(xPos, yPos, Constants::ENEMY_WIDTH, Constants::ENEMY_HEIGHT, healthPoints, 4.0f, shootProbability));
    }

    enemiesCount = enemies.size();
}

void EnemyController::nextLevel(int level)
{
    int numberOfEnemiesToAdjust = std::min(level * 2, static_cast<int>(enemies.size()));

    std::random_shuffle(enemies.begin(), enemies.end());

    for (int i = 0; i < numberOfEnemiesToAdjust; ++i)
    {
        auto &enemy = enemies[i];
        enemy->setShootProbability(enemy->getShootProbability() + level * Constants::ENEMY_SHOOT_PROBABILITY_INCREMENT_PER_LEVEL);
    }
}
