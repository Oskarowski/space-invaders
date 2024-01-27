#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <iostream>

#include "../Constants.h"
#include "../abstracts/Serializeable.h"
#include "../abstracts/ShooterableEntity.h"
#include "../abstracts/RenderableEntity.h"
#include "../abstracts/DamageableEntity.h"

class GameController;

class Player : public RenderableEntity, public DamageableEntity, public Serializable, public ShooterableEntity
{
private:
    int speed = 5.0;

public:
    Player(int xPos, int yPos, int width, int height, int healthPoints);
    ~Player() = default;

    void render(sf::RenderWindow &window) override;

    int getSpeed() const;
    void setSpeed(int newSpeed);

    void moveLeft(GameController &gc);
    void moveRight(GameController &gc);

    bool canSustainDamage(const int &damagePoints) override;
    void takeDamage(int damagePoints) override;

    nlohmann::json serialize() const override;
    void deserialize(const nlohmann::json &json) override;

    void shoot(std::vector<std::shared_ptr<Projectile>> &projectileStorage) override;

    void heal(float healMultiplier);
};

#endif // PLAYER_H
