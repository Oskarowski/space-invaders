#ifndef BARRIER_CONTROLLER_H
#define BARRIER_CONTROLLER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <iostream>

#include "../models/Barrier.h"
#include "../controllers/StoreGameStateController.h"
#include "../Constants.h"

class BarrierController
{
private:
    std::vector<std::shared_ptr<Barrier>> barriers;

    void removeMarkedBarriers();

public:
    BarrierController();
    ~BarrierController() = default;

    std::vector<std::shared_ptr<Barrier>> &getBarriers();

    void createBarriers();
    void loadBarriers(const nlohmann::json &barriersJson);

    void update();
    void render(sf::RenderWindow &window);

    void heal(float healMultiplier);

    // Method to serialize all barriers and combine them into a JSON array
    nlohmann::json serialize() const;
};

#endif // BARRIER_CONTROLLER_H