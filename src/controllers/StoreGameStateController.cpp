#include "../../include/controllers/StoreGameStateController.h"

#include <iostream>
#include <fstream>
#include <iomanip>

void StoreGameStateController::resetLoadedStatesToNulls()
{
    this->loadedPlayerState = NULL;
    this->loadedBarriersState = NULL;
    this->loadedGameControllerState = NULL;
    this->loadedEnemiesState = NULL;
}

void StoreGameStateController::saveState(const nlohmann::json &gameState, const std::string &filename)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        file << std::setw(4) << gameState;
        file.close();
        // std::cout << "Game state saved successfully.\n";
    }
    else
    {
        std::cerr << "Unable to save game state. Error: " << strerror(errno) << "\n";
    }
}

nlohmann::json StoreGameStateController::loadState(const std::string &filename)
{
    nlohmann::json gameState;

    std::filesystem::path fullPath = std::filesystem::path(getProjectDirectoryPath()) / filename;
    // std::cout << "Loading game state from: " << fullPath << std::endl;

    std::ifstream file(fullPath.string());
    if (file.is_open())
    {
        try
        {
            file >> gameState;
            file.close();
            // std::cout << gameState.dump(4) << std::endl;
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Error loading game state");
        }
    }
    else
    {
        throw std::runtime_error("Unable to open game state file: " + fullPath.string());
    }

    return gameState;
}

std::string StoreGameStateController::getProjectDirectoryPath()
{
    std::filesystem::path path = std::filesystem::current_path();
    return path.string();
}

bool StoreGameStateController::hasSavedStateFiles()
{
    const std::filesystem::path dirPath = StoreGameStateController::getProjectDirectoryPath();
    // std::cout << dirPath << std::endl;

    for (const auto &file : std::filesystem::directory_iterator(dirPath))
    {
        if (file.is_regular_file())
        {
            std::string filename = file.path().filename().string();
            if (filename.find("saved") == 0 && filename.rfind(".json") == filename.size() - 5)
            {
                return true;
            }
        }
    }

    return false;
}

void StoreGameStateController::setLoadedPlayerState(const nlohmann::json &state)
{
    this->loadedPlayerState = state;
}

nlohmann::json StoreGameStateController::getLoadedPlayerState()
{
    return this->loadedPlayerState;
}

void StoreGameStateController::setLoadedBarriersState(const nlohmann::json &state)
{
    this->loadedBarriersState = state;
}

nlohmann::json StoreGameStateController::getLoadedBarriersState()
{
    return this->loadedBarriersState;
}

void StoreGameStateController::setLoadedGameControllerState(const nlohmann::json &state)
{
    this->loadedGameControllerState = state;
}

nlohmann::json StoreGameStateController::getLoadedGameControllerState()
{
    return this->loadedGameControllerState;
}

void StoreGameStateController::setLoadedEnemiesState(const nlohmann::json &state)
{
    this->loadedEnemiesState = state;
}

nlohmann::json StoreGameStateController::getLoadedEnemiesState()
{
    return this->loadedEnemiesState;
}