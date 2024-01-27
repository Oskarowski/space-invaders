#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <memory>
#include <iostream>
#include "../Constants.h"
#include "../abstracts/RenderableEntity.h"

enum class ProjectileType
{
    PLAYER_PROJECTILE,
    ENEMY_PROJECTILE
};

class Projectile : public RenderableEntity
{
private:
    float speed;
    ProjectileType type;

public:
    Projectile(int xPos, int yPos, int width, int height, float speed, ProjectileType type);
    ~Projectile() = default;

    float getSpeed() const;
    void setSpeed(float newSpeed);

    void move();
    bool isOutOfBounds();
    void update(sf::RenderWindow &gw);

    void render(sf::RenderWindow &window) override;

    ProjectileType getType() const;
};

#endif // PROJECTILE_H