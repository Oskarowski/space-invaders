#ifndef BARRIER_H
#define BARRIER_H

#include <SFML/Graphics.hpp>

#include "../Constants.h"
#include "../abstracts/Serializeable.h"
#include "../abstracts/RenderableEntity.h"
#include "../abstracts/DamageableEntity.h"

class Barrier : public RenderableEntity, public DamageableEntity, public Serializable
{
private:
public:
    Barrier(int xPos, int yPos, int healthPoints);
    ~Barrier() = default;

    void render(sf::RenderWindow &window) override;

    bool canSustainDamage(const int &damagePoints) override;
    void takeDamage(int damagePoints) override;

    nlohmann::json serialize() const override;
    void deserialize(const nlohmann::json &json) override;

    void heal(float healMultiplier);
};

#endif // BARRIER_H