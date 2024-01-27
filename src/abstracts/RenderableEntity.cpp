#include "../../include/abstracts/RenderableEntity.h"

RenderableEntity::RenderableEntity(std::string texturePath, int xPos, int yPos, int width, int height)
    : xPos(xPos), yPos(yPos), width(width), height(height),
      markedForDeletion(false)
{
    if (!texturePath.empty())
    {
        loadTexture(texturePath);
    }

    // Set the origin to the center of the sprite
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

    this->sprite.setPosition(static_cast<float>(xPos), static_cast<float>(yPos));
}

RenderableEntity::RenderableEntity(std::string texturePath, int xPos, int yPos, int width, int height,
                                   sf::FloatRect colliderBox)
    : xPos(xPos), yPos(yPos), width(width), height(height),
      colliderBox(std::move(colliderBox)), markedForDeletion(false)
{
    loadTexture(texturePath);
    this->sprite.setPosition(static_cast<float>(xPos), static_cast<float>(yPos));
}

sf::Sprite &RenderableEntity::getSprite()
{
    return sprite;
}

sf::FloatRect &RenderableEntity::getColliderBox()
{
    return colliderBox;
}

void RenderableEntity::markForDeletion()
{
    markedForDeletion = true;
}

bool RenderableEntity::isMarkedForDeletion() const
{
    return markedForDeletion;
}

void RenderableEntity::render(sf::RenderWindow &window)
{
    window.draw(sprite);
}

void RenderableEntity::loadTexture(const std::string &texturePath)
{
    if (texture.loadFromFile(texturePath))
    {
        this->sprite.setTexture(texture);
    }
}

void RenderableEntity::setTexture(const std::string texturePath)
{
    sf::Texture newTexture;
    if (!newTexture.loadFromFile(texturePath))
    {
        std::cerr << "Error loading texture from file: " << texturePath << std::endl;
    }

    texture = newTexture;
    sprite.setTexture(texture);
}