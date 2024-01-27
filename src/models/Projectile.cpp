#include "../../include/models/Projectile.h"

Projectile::Projectile(int xPos, int yPos, int width, int height, float speed, ProjectileType type) : type(type), RenderableEntity("", xPos, yPos, width, height)
{
    switch (type)
    {
    case ProjectileType::PLAYER_PROJECTILE:
    {
        this->setTexture("./assets/projectile.png");
        this->speed = -speed;
        break;
    }

    case ProjectileType::ENEMY_PROJECTILE:
    {
        this->setTexture("./assets/enemy_projectile.png");
        this->speed = speed;
        break;
    }
    default:
        setTexture("./assets/null.png");
        break;
    }
}

float Projectile::getSpeed() const
{
    return speed;
}

void Projectile::setSpeed(float newSpeed)
{
    speed = newSpeed;
}

ProjectileType Projectile::getType() const
{
    return type;
}

void Projectile::move()
{
    getSprite().move(0.0f, speed);
}

bool Projectile::isOutOfBounds()
{
    return getSprite().getPosition().y < 0 || getSprite().getPosition().y > Constants::WINDOW_HEIGHT;
}

void Projectile::update(sf::RenderWindow &gw)
{
    move();

    if (isOutOfBounds())
    {
        markForDeletion();
    }

    render(gw);
}

void Projectile::render(sf::RenderWindow &window)
{
    window.draw(getSprite());
}