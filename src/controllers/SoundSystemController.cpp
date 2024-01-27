#include "../../include/controllers/SoundSystemController.h"
SoundSystemController::SoundSystemController()
{
}

void SoundSystemController::loadBackgroundMusic()
{
    if (!backgroundMusic.openFromFile("/assets/sounds/background_music.ogg"))
    {
        // std::filesystem::path currentPath = std::filesystem::current_path();
        // std::cout << "Current working directory: " << currentPath << std::endl;
        // std::cout << "Error loading background music\n";
    }
}

void SoundSystemController::playBackgroundMusic()
{
    backgroundMusic.play();
    backgroundMusic.setVolume(50);
    backgroundMusic.setLoop(true);
};
void SoundSystemController::stopBackgroundMusic()
{
    backgroundMusic.stop();
};
void SoundSystemController::setBackgroundMusicVolume(float volume)
{
    backgroundMusic.setVolume(50);
};