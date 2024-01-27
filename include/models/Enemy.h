#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#include "../Constants.h"
#include "../abstracts/Serializeable.h"
#include "../abstracts/ShooterableEntity.h"
#include "../abstracts/RenderableEntity.h"
#include "../abstracts/Serializeable.h"
#include "../abstracts/DamageableEntity.h"

class Enemy : public RenderableEntity, public DamageableEntity, public ShooterableEntity, public Serializable
{
private:
    float speed = 4.0;
    short direction = 1;
    float shootProbability = 0.010;

public:
    Enemy(int xPos, int yPos, int width, int height, int healthPoints, float speed, float shootProbability);
    ~Enemy();

    void update(std::vector<std::shared_ptr<Projectile>> &projectileStorage);

    void move(float offsetX, float offsetY);
    void render(sf::RenderWindow &window) override;

    bool canSustainDamage(const int &damagePoints) override;
    void takeDamage(int damagePoints) override;

    void shoot(std::vector<std::shared_ptr<Projectile>> &projectileStorage) override;

    nlohmann::json serialize() const override;
    void deserialize(const nlohmann::json &json) override;

    float getShootProbability();
    void setShootProbability(float newShootProbability);
};

#endif // ENEMY_H