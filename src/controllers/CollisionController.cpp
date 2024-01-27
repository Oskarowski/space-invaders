#include "../../include/controllers/CollisionController.h"

bool CollisionController::isColliding(RenderableEntity &entity1, RenderableEntity &entity2)
{
    // Get the global bounds of the sprites
    sf::FloatRect rect1 = entity1.getSprite().getGlobalBounds();
    sf::FloatRect rect2 = entity2.getSprite().getGlobalBounds();

    // Check for collision
    return rect1.intersects(rect2);
}

// collisions between player's projectiles and enemies
void CollisionController::checkCollisions(std::vector<std::shared_ptr<Enemy>> &enemies, std::vector<std::shared_ptr<Projectile>> &projectiles)
{
    for (auto &enemy : enemies)
    {
        for (auto &projectile : projectiles)
        {
            if (isColliding(*enemy, *projectile))
            {
                enemy->takeDamage(Constants::PLAYER_BASE_DAMAGE);
                projectile->markForDeletion();
            }
        }
    }
}

void CollisionController::checkCollisions(std::shared_ptr<Player> &player, std::vector<std::shared_ptr<Projectile>> &projectiles)
{
    for (auto &projectile : projectiles)
    {
        if (isColliding(*player, *projectile))
        {
            player->takeDamage(Constants::ENEMY_BASE_DAMAGE);
            projectile->markForDeletion();
        }
    }
}

void CollisionController::checkCollisions(std::vector<std::shared_ptr<Barrier>> &barriers, std::vector<std::shared_ptr<Projectile>> &projectiles)
{
    for (auto &barrier : barriers)
    {
        for (auto &projectile : projectiles)
        {
            if (isColliding(*barrier, *projectile))
            {
                switch (projectile->getType())
                {
                case ProjectileType::ENEMY_PROJECTILE:
                    barrier->takeDamage(Constants::ENEMY_TO_BARRIER_BASE_DAMAGE);
                    break;
                case ProjectileType::PLAYER_PROJECTILE:
                    barrier->takeDamage(Constants::PLAYER_TO_BARRIER_BASE_DAMAGE);
                    break;

                default:
                    barrier->takeDamage(Constants::BARRIER_TAKE_BASE_DAMAGE);
                    break;
                }

                projectile->markForDeletion();
            }
        }
    }
}