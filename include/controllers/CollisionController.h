#ifndef COLLISION_CONTROLLER_H
#define COLLISION_CONTROLLER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>

#include "../abstracts/RenderableEntity.h"
#include "../models/Player.h"
#include "../models/Enemy.h"
#include "../models/Projectile.h"
#include "../models/Barrier.h"

class CollisionController
{
private:
    static bool isColliding(RenderableEntity &entity1, RenderableEntity &entity2);

public:
    CollisionController() = default;
    ~CollisionController() = default;

    void checkCollisions(std::vector<std::shared_ptr<Enemy>> &enemies, std::vector<std::shared_ptr<Projectile>> &projectiles);
    void checkCollisions(std::shared_ptr<Player> &player, std::vector<std::shared_ptr<Projectile>> &projectiles);
    void checkCollisions(std::vector<std::shared_ptr<Barrier>> &barriers, std::vector<std::shared_ptr<Projectile>> &projectiles);
};

#endif // COLLISION_CONTROLLER_H