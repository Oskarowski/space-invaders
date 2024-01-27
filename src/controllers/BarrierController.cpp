#include "../../include/controllers/BarrierController.h"

BarrierController::BarrierController()
{
}

std::vector<std::shared_ptr<Barrier>> &BarrierController::getBarriers()
{
    return barriers;
}

void BarrierController::removeMarkedBarriers()
{
    for (auto it = barriers.begin(); it != barriers.end();)
    {
        if ((*it)->isMarkedForDeletion())
        {
            it = barriers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void BarrierController::heal(float healMultiplier)
{
    for (auto &barrier : barriers)
    {
        barrier->heal(healMultiplier);
    }
}

void BarrierController::createBarriers()
{
    const int numberOfBarriers = Constants::BASE_COUNT_OF_BARRIERS;
    const float barrierWidth = Constants::BASE_BARRIER_WIDTH;

    const float windowWidth = static_cast<float>(Constants::WINDOW_WIDTH);
    const float totalWidth = numberOfBarriers * barrierWidth;
    const float spacing = (windowWidth - totalWidth) / (numberOfBarriers + 1);

    for (int i = 0; i < numberOfBarriers; ++i)
    {
        float xPos = spacing * (i + 1) + i * barrierWidth;
        float yPos = 1000.0f;

        barriers.push_back(std::make_shared<Barrier>(xPos, yPos, Constants::BASE_BARRIER_HEALTH_POINTS));
    }
}

void BarrierController::render(sf::RenderWindow &window)
{
    for (auto &barrier : barriers)
    {
        barrier->render(window);
    }
}

void BarrierController::update()
{
    removeMarkedBarriers();
}

nlohmann::json BarrierController::serialize() const
{
    nlohmann::json barriersArray;

    for (const auto &barrier : barriers)
    {
        barriersArray.push_back(barrier->serialize());
    }

    return barriersArray;
}

void BarrierController::loadBarriers(const nlohmann::json &barriersJson)
{
    for (const auto &barrierJson : barriersJson)
    {
        const int xPos = barrierJson.at("x_pos");
        const int yPos = barrierJson.at("y_pos");
        const int healthPoints = barrierJson.at("health_points");

        barriers.push_back(std::make_shared<Barrier>(xPos, yPos, healthPoints));
    }
}