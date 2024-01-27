#include "../../include/abstracts/ShooterableEntity.h"

ShooterableEntity::ShooterableEntity(sf::Time baseFireRateCooldown)
    : fireRateCooldown(baseFireRateCooldown)
{
}

void ShooterableEntity::setFireRateCooldown(float newFireRateCooldown)
{
    this->fireRateCooldown = sf::microseconds(static_cast<sf::Int64>(newFireRateCooldown));
}