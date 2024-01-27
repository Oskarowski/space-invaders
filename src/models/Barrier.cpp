#include "../../include/models/Barrier.h"

Barrier::Barrier(int xPos, int yPos, int healthPoints)
    : RenderableEntity("./assets/barrier.png", xPos, yPos, Constants::BASE_BARRIER_WIDTH, Constants::BASE_BARRIER_HEIGHT), DamageableEntity(healthPoints)
{
}

void Barrier::heal(float healMultiplier)
{
    setHealthPoints(getHealthPoints() + Constants::BASE_BARRIER_HEALTH_POINTS * healMultiplier);
}

nlohmann::json Barrier::serialize() const
{
    nlohmann::json barrierJson;

    barrierJson["x_pos"] = sprite.getPosition().x;
    barrierJson["y_pos"] = sprite.getPosition().y;
    barrierJson["health_points"] = getHealthPoints();

    return barrierJson;
}

void Barrier::deserialize(const nlohmann::json &barrierJson)
{
    sprite.setPosition(barrierJson["x_pos"], barrierJson["y_pos"]);
    setHealthPoints(barrierJson["health_points"]);
}

void Barrier::render(sf::RenderWindow &window)
{
    window.draw(getSprite());
}

bool Barrier::canSustainDamage(const int &damageAmount)
{
    if (getHealthPoints() - damageAmount <= 0)
    {
        return false;
    }

    return true;
}

void Barrier::takeDamage(int damageAmount)
{
    if (!canSustainDamage(damageAmount))
    {
        setHealthPoints(0);
        markForDeletion();
        return;
    }

    setHealthPoints(getHealthPoints() - damageAmount);
}
