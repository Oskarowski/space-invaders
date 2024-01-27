#ifndef STORE_GAME_STATE_CONTROLLER_H
#define STORE_GAME_STATE_CONTROLLER_H

#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>

class StoreGameStateController
{
private:
    nlohmann::json loadedPlayerState = NULL;
    nlohmann::json loadedBarriersState = NULL;
    nlohmann::json loadedGameControllerState = NULL;
    nlohmann::json loadedEnemiesState = NULL;

public:
    void resetLoadedStatesToNulls();

    static void saveState(const nlohmann::json &state, const std::string &filename);
    static nlohmann::json loadState(const std::string &filename);

    static std::string getProjectDirectoryPath();
    // static std::string getSaveStateDirectoryPath();
    static bool hasSavedStateFiles();

    void setLoadedPlayerState(const nlohmann::json &state);
    nlohmann::json getLoadedPlayerState();

    void setLoadedBarriersState(const nlohmann::json &state);
    nlohmann::json getLoadedBarriersState();

    void setLoadedEnemiesState(const nlohmann::json &state);
    nlohmann::json getLoadedEnemiesState();

    void setLoadedGameControllerState(const nlohmann::json &state);
    nlohmann::json getLoadedGameControllerState();
};

#endif // STORE_GAME_STATE_CONTROLLER_H
