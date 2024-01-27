#include "../../include/abstracts/DamageableEntity.h"

DamageableEntity::DamageableEntity(int healthPoints)
    : healthPoints(healthPoints)
{
}

int DamageableEntity::getHealthPoints() const
{
    return healthPoints;
}

void DamageableEntity::setHealthPoints(int newHealthPoints)
{
    this->healthPoints = newHealthPoints;
}
