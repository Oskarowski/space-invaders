#include "../../include/models/Enemy.h"

Enemy::Enemy(int xPos, int yPos, int width, int height, int healthPoints, float speed, float shootProbability) : speed(speed), shootProbability(shootProbability), RenderableEntity("./assets/enemy.png", xPos, yPos, width, height), DamageableEntity(healthPoints), ShooterableEntity(sf::seconds(Constants::ENEMY_BASE_FIRE_RATE_COOLDOWN))
{
}

Enemy::~Enemy()
{
    // std::cout << "Enemy destroyed\n";
}

void Enemy::render(sf::RenderWindow &window)
{
    window.draw(getSprite());
}

bool Enemy::canSustainDamage(const int &damageAmount)
{
    if (getHealthPoints() - damageAmount <= 0)
    {
        return false;
    }

    return true;
}

void Enemy::takeDamage(int damageAmount)
{
    if (!canSustainDamage(damageAmount))
    {
        setHealthPoints(0);
        this->markForDeletion();
        return;
    }

    setHealthPoints(getHealthPoints() - damageAmount);
}

void Enemy::shoot(std::vector<std::shared_ptr<Projectile>> &projectileStorage)
{

    //  Roll a dice to decide whether to shoot or not
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    double diceRoll = dis(gen);

    if (diceRoll < getShootProbability())
    {
        sf::Time currentTime = shotClock.getElapsedTime();

        // Check if enough time has passed since the last shot to allow another shot
        if (currentTime - lastShotTime >= fireRateCooldown)
        {
            projectileStorage.push_back(std::make_shared<Projectile>(sprite.getPosition().x, sprite.getPosition().y, 10, 10, 10.0f, ProjectileType::ENEMY_PROJECTILE));

            lastShotTime = currentTime;
        }
    }
}

void Enemy::move(float offsetX, float offsetY)
{
    sprite.move(offsetX, offsetY);
}

void Enemy::update(std::vector<std::shared_ptr<Projectile>> &projectileStorage)
{
    move(2.0f * direction, 0.0f);

    // Change direction when reaching screen edges
    float enemyWidth = sprite.getGlobalBounds().width;
    float spritePosX = sprite.getPosition().x;

    if (spritePosX <= enemyWidth / 2 || spritePosX + enemyWidth / 2 >= Constants::WINDOW_WIDTH)
    {
        direction = -direction;
        move(0.0f, 35.0f); // Move downward when changing direction
    }

    shoot(projectileStorage);
}

nlohmann::json Enemy::serialize() const
{
    nlohmann::json json;

    json["x_pos"] = sprite.getPosition().x;
    json["y_pos"] = sprite.getPosition().y;
    json["health_points"] = getHealthPoints();
    json["shoot_probability"] = shootProbability;

    return json;
}

void Enemy::deserialize(const nlohmann::json &json)
{
    sprite.setPosition(json["x_pos"], json["y_pos"]);
    setHealthPoints(json["health_points"]);
}

void Enemy::setShootProbability(float newShootProbability)
{
    shootProbability = newShootProbability;
}

float Enemy::getShootProbability()
{
    return shootProbability;
}