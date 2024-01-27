#ifndef RENDERABLE_ENTITY_H
#define RENDERABLE_ENTITY_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class RenderableEntity
{
public:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::FloatRect colliderBox;

    int xPos;
    int yPos;

    int width;
    int height;

    bool markedForDeletion;

    /**
     * @brief Constructs a RenderableEntity with the specified parameters.
     *
     * @param texture A reference to the SFML texture to be applied to the entity.
     * @param xPos The x-coordinate of the initial position of the entity.
     * @param yPos The y-coordinate of the initial position of the entity.
     * @param width The width of the entity.
     * @param height The height of the entity.
     */
    RenderableEntity(std::string texturePath, int xPos, int yPos, int width, int height);
    RenderableEntity(std::string texturePath, int xPos, int yPos, int width, int height, sf::FloatRect colliderBox);
    virtual ~RenderableEntity() = default;

    sf::Sprite &getSprite();
    sf::FloatRect &getColliderBox();

    void markForDeletion();
    bool isMarkedForDeletion() const;

    virtual void render(sf::RenderWindow &window) = 0;
    void loadTexture(const std::string &texturePath);
    void setTexture(const std::string texturePath);
};

#endif // RENDERABLE_ENTITY_H
