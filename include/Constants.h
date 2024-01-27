// Constants.h
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

class Constants
{
public:
    static constexpr int WINDOW_WIDTH = 900;
    static constexpr int WINDOW_HEIGHT = 1200;

    static constexpr int MAIN_MENU = 1;
    static constexpr int LOAD_LAST_GAME = 2;
    static constexpr int INIT_GAME = 3;
    static constexpr int TRY_TO_LOAD_SAVE = 4;
    static constexpr int START_GAME = 5;
    static constexpr int GAME_RUNNING = 6;
    static constexpr int IN_GAME = 7;
    static constexpr int END_GAME = 8;
    static constexpr int END_GAME_PLAYER_LOST_HEALTH = 9;
    static constexpr int ALL_ENEMIES_DESTROYED = 10;
    static constexpr int EXIT = 125;

    static constexpr int MENU_FONT_SIZE = 75;

    static constexpr int PLAYER_WIDTH = 50;
    static constexpr int PLAYER_HEIGHT = 50;
    static constexpr int PLAYER_BASE_HEALTH = 150;
    static constexpr int PLAYER_BASE_DAMAGE = 35;
    static constexpr float PLAYER_BASE_FIRE_RATE_COOLDOWN = 0.4f;
    static constexpr int PLAYER_BASE_HEAL = 50;
    static constexpr float PLAYER_BASE_HEAL_MULTIPLAYER = 0.5;
    static constexpr float PLAYER_ADDITIONAL_HEAL_MULTIPLAYER_PER_LEVEL = 0.05;

    static constexpr int BASE_PROJECTILE_WIDTH = 3;
    static constexpr int BASE_PROJECTILE_HEIGHT = 5;

    static constexpr int BASE_COUNT_OF_BARRIERS = 3;
    static constexpr int BASE_BARRIER_HEALTH_POINTS = 250;
    static constexpr int BASE_BARRIER_WIDTH = 75;
    static constexpr int BASE_BARRIER_HEIGHT = 30;
    static constexpr int ENEMY_TO_BARRIER_BASE_DAMAGE = 15;
    static constexpr int PLAYER_TO_BARRIER_BASE_DAMAGE = 10;
    static constexpr int BARRIER_TAKE_BASE_DAMAGE = 20;
    static constexpr int BARRIER_BASE_HEAL = 50;
    static constexpr int BARRIER_BASE_HEAL_MULTIPLAYER = 0.5;
    static constexpr float BARRIER_ADDITIONAL_HEAL_MULTIPLAYER_PER_LEVEL = 0.05;

    static constexpr int ENEMY_WIDTH = 50;
    static constexpr int ENEMY_HEIGHT = 50;
    static constexpr int MAX_ENEMIES_ROWS_COUNT = 5;
    static constexpr int BASE_ENEMY_SCORE_MULTIPLIER = 2;
    static constexpr float ENEMY_BASE_FIRE_RATE_COOLDOWN = 0.45f;

    static constexpr int ADDITIONAL_ENEMY_SCORE_MULTIPLIER_PER_LEVEL = 0.5;
    static constexpr int ENEMY_BASE_DAMAGE = 15;
    static constexpr float ENEMY_BASE_SHOOT_PROBABILITY = 0.010;
    static constexpr float ENEMY_SHOOT_PROBABILITY_INCREMENT_PER_LEVEL = 0.005;

    static constexpr const char *SAVED_ENEMIES_FILE_NAME = "saved_enemies.json";
};

#endif // CONSTANTS_H
