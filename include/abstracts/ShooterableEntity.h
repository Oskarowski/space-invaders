// ShooterableEntity.h

#ifndef SHOOTERABLEENTITY_H
#define SHOOTERABLEENTITY_H

#include "../models/Projectile.h"
#include <memory>
#include <SFML/Graphics.hpp>

class ShooterableEntity
{
public:
    sf::Clock shotClock;
    sf::Time lastShotTime;
    sf::Time fireRateCooldown;

    ShooterableEntity(sf::Time baseFireRateCooldown);
    virtual ~ShooterableEntity() = default;

    void setFireRateCooldown(float newFireRateCooldown);

    virtual void shoot(std::vector<std::shared_ptr<Projectile>> &projectileStorage) = 0;
};

#endif // SHOOTERABLEENTITY_H
