#include <boost/test/unit_test.hpp>

#include "Constants.h"
#include "./models/Player.h"

BOOST_AUTO_TEST_SUITE(PlayerTestSuite, *boost::unit_test::label("TestPlayer"))

BOOST_AUTO_TEST_CASE(PlayerInitialization)
{
    Player player(0, 0, 50, 50, 100);

    BOOST_CHECK_EQUAL(player.getSpeed(), 5);
    BOOST_CHECK_EQUAL(player.getHealthPoints(), 100);
}

BOOST_AUTO_TEST_CASE(PlayerTakeDamage)
{
    int playerHealthPoints = Constants::PLAYER_BASE_HEALTH;
    int damagePoints = 60;
    int expectedHealthPoints = playerHealthPoints - damagePoints;

    Player player(0, 0, 50, 50, playerHealthPoints);

    BOOST_REQUIRE_EQUAL(player.getHealthPoints(), playerHealthPoints);

    player.takeDamage(damagePoints);

    BOOST_CHECK_EQUAL(player.getHealthPoints(), expectedHealthPoints);
}

BOOST_AUTO_TEST_CASE(PlayerSerialization)
{
    Player player(10, 20, 30, 40, 50);

    nlohmann::json playerJson = player.serialize();

    BOOST_CHECK_EQUAL(playerJson["x_pos"], 10);
    BOOST_CHECK_EQUAL(playerJson["y_pos"], 20);
    BOOST_CHECK_EQUAL(playerJson["health_points"], 50);
}

BOOST_AUTO_TEST_CASE(PlayerDamageAndHealing)
{
    int playerHealthPoints = Constants::PLAYER_BASE_HEAL;
    int damagePoints = 50;
    int expectedHealthPoints = playerHealthPoints - damagePoints;

    Player player(0, 0, 0, 0, playerHealthPoints);

    // Inflict damage
    player.takeDamage(damagePoints);
    BOOST_REQUIRE_EQUAL(player.getHealthPoints(), expectedHealthPoints);

    float healMultiplier = 0.5;
    expectedHealthPoints = expectedHealthPoints + playerHealthPoints * healMultiplier;

    // Heal
    player.heal(healMultiplier);
    BOOST_REQUIRE_EQUAL(player.getHealthPoints(), expectedHealthPoints);
}

BOOST_AUTO_TEST_SUITE_END()