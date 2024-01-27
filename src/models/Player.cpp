#include "../../include/models/Player.h"
#include "../../include/controllers/GameController.h"

Player::Player(int xPos, int yPos, int width, int height, int healthPoints)
    : RenderableEntity("./assets/player.png", xPos, yPos, width, height), DamageableEntity(healthPoints), ShooterableEntity(sf::seconds(Constants::PLAYER_BASE_FIRE_RATE_COOLDOWN))
{
}

nlohmann::json Player::serialize() const
{
    nlohmann::json playerJson;

    playerJson["x_pos"] = sprite.getPosition().x;
    playerJson["y_pos"] = sprite.getPosition().y;
    playerJson["health_points"] = getHealthPoints();

    return playerJson;
}

void Player::deserialize(const nlohmann::json &playerJson)
{
    sprite.setPosition(playerJson["x_pos"], playerJson["y_pos"]);
    setHealthPoints(playerJson["health_points"]);
}

int Player::getSpeed() const
{
    return speed;
}

void Player::setSpeed(int newSpeed)
{
    speed = newSpeed;
}

void Player::render(sf::RenderWindow &window)
{
    window.draw(getSprite());
}

void Player::moveLeft(GameController &gc)
{
    sprite.move(-getSpeed(), 0);

    // Teleport to the right edge if reaching the left edge
    if (sprite.getPosition().x + getSprite().getGlobalBounds().width < 0)
    {
        sprite.setPosition(gc.getWindowSize().x, sprite.getPosition().y);
    }
}

void Player::moveRight(GameController &gc)
{
    sprite.move(getSpeed(), 0);

    // Teleport to the left edge if reaching the right edge
    if (sprite.getPosition().x > gc.getWindowSize().x)
    {
        sprite.setPosition(0 - getSprite().getGlobalBounds().width, sprite.getPosition().y);
    }
}

bool Player::canSustainDamage(const int &damageAmount)
{
    if (getHealthPoints() - damageAmount <= 0)
    {
        return false;
    }

    return true;
}

void Player::takeDamage(int damageAmount)
{
    if (!canSustainDamage(damageAmount))
    {
        setHealthPoints(0);
        return;
    }

    setHealthPoints(getHealthPoints() - damageAmount);
}

void Player::shoot(std::vector<std::shared_ptr<Projectile>> &projectileStorage)
{
    sf::Time currentTime = shotClock.getElapsedTime();

    // Check if enough time has passed since the last shot to allow another shot
    if (currentTime - lastShotTime >= fireRateCooldown)
    {
        projectileStorage.push_back(std::make_shared<Projectile>(sprite.getPosition().x, sprite.getPosition().y, 10, 10, 10.0f, ProjectileType::PLAYER_PROJECTILE));

        lastShotTime = currentTime;
    }
}

void Player::heal(float healMultiplier)
{
    setHealthPoints(getHealthPoints() + (Constants::PLAYER_BASE_HEAL * healMultiplier));
}