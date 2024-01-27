#include <boost/test/unit_test.hpp>

#include "Constants.h"
#include "./models/Enemy.h"

BOOST_AUTO_TEST_SUITE(EnemyTestSuite, *boost::unit_test::label("TestEnemy"))

BOOST_AUTO_TEST_CASE(EnemyInitialization)
{
    int xPos = 50, yPos = 50, width = 30, height = 30, healthPoints = 100;
    float speed = 2.0f, shootProbability = 0.5f;

    Enemy enemy(xPos, yPos, width, height, healthPoints, speed, shootProbability);

    BOOST_CHECK_EQUAL(enemy.getHealthPoints(), healthPoints);
    BOOST_CHECK_EQUAL(enemy.getShootProbability(), shootProbability);
}

BOOST_AUTO_TEST_CASE(EnemySerialization)
{
    int xPos = 60, yPos = 70, width = 40, height = 40, healthPoints = 80;
    float speed = 2.5f, shootProbability = 0.7f;

    Enemy enemy(xPos, yPos, width, height, healthPoints, speed, shootProbability);

    nlohmann::json enemyJson = enemy.serialize();

    BOOST_CHECK_EQUAL(enemyJson["x_pos"], xPos);
    BOOST_CHECK_EQUAL(enemyJson["y_pos"], yPos);
    BOOST_CHECK_EQUAL(enemyJson["health_points"], healthPoints);
    BOOST_CHECK_EQUAL(enemyJson["shoot_probability"], shootProbability);
}

BOOST_AUTO_TEST_CASE(EnemyMovement)
{
    int xPos = 100, yPos = 50, width = 30, height = 30, healthPoints = 100;
    float speed = 2.0f, shootProbability = 0.5f;

    Enemy enemy(xPos, yPos, width, height, healthPoints, speed, shootProbability);

    // Move and check position
    enemy.move(10.0f, 0.0f);
    BOOST_CHECK_EQUAL(enemy.getSprite().getPosition().x, xPos + 10.0f);

    BOOST_CHECK_EQUAL(enemy.getSprite().getPosition().y, yPos);
}

BOOST_AUTO_TEST_CASE(EnemyTakeDamage)
{
    int xPos = 200, yPos = 50, width = 30, height = 30, healthPoints = 100;
    float speed = 2.0f, shootProbability = 0.5f;
    int damagePoints = 30;

    Enemy enemy(xPos, yPos, width, height, healthPoints, speed, shootProbability);

    // Check initial health points
    BOOST_CHECK_EQUAL(enemy.getHealthPoints(), healthPoints);

    // Inflict damage
    enemy.takeDamage(damagePoints);

    // Check health points after taking damage
    BOOST_CHECK_EQUAL(enemy.getHealthPoints(), healthPoints - damagePoints);
}

BOOST_AUTO_TEST_SUITE_END()
