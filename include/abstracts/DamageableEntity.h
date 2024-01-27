#ifndef DAMAGEABLE_ENTITY_H
#define DAMAGEABLE_ENTITY_H

class DamageableEntity
{
protected:
    int healthPoints;

public:
    DamageableEntity(int healthPoints);
    virtual ~DamageableEntity() = default;

    int getHealthPoints() const;

    void setHealthPoints(int newHealthPoints);

    virtual bool canSustainDamage(const int &damagePoints) = 0;

    virtual void takeDamage(int damagePoints) = 0;
};

#endif // DAMAGEABLE_ENTITY_H