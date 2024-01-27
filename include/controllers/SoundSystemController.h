#ifndef SOUND_SYSTEM_CONTROLLER_H
#define SOUND_SYSTEM_CONTROLLER_H

#include <SFML/Audio.hpp>
#include <iostream>
#include <filesystem>

class SoundSystemController
{
private:
    sf::Music backgroundMusic;

public:
    SoundSystemController();
    ~SoundSystemController() = default;

    void loadBackgroundMusic();
    void playBackgroundMusic();
    void stopBackgroundMusic();
    void setBackgroundMusicVolume(float volume);
};

#endif // SOUND_SYSTEM_CONTROLLER_H
