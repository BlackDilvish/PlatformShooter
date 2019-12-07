#include "PlatformsManager.h"

void PlatformsManager::initTextures()
{
    PlatformsManager::platformTextures[0].loadFromFile("Assets/Images/Platforms/brownPlatform.png");
    PlatformsManager::platformTextures[1].loadFromFile("Assets/Images/Platforms/brownPlatform.png");
    PlatformsManager::platformTextures[2].loadFromFile("Assets/Images/Platforms/brownPlatform.png");
}

void PlatformsManager::addPlatform(sf::Vector2f pos, sf::Vector2f size)
{
    sf::RectangleShape tempPlatform;
    tempPlatform.setSize(size);
    tempPlatform.setPosition(pos);
    tempPlatform.setFillColor(sf::Color::Green);

    platformsVector.push_back(tempPlatform);
}

void PlatformsManager::addPlatform(float *platformParams, int platformType)
{
    sf::RectangleShape tempPlatform;
    tempPlatform.setPosition(sf::Vector2f(platformParams[0],platformParams[1]));
    tempPlatform.setSize(sf::Vector2f(platformParams[2],platformParams[3]));
    tempPlatform.setTexture(platformTextures + platformType);

    platformsVector.push_back(tempPlatform);
}

void PlatformsManager::render(sf::RenderTarget &window)
{
    for(size_t i=0; i<platformsVector.size(); i++)
        window.draw(platformsVector[i]);
}

sf::RectangleShape& PlatformsManager::getPlatform(size_t id)
{
    return platformsVector[id];
}

void PlatformsManager::destroyPlatform(size_t id)
{
    platformsVector.erase(platformsVector.begin() + id);
}

void PlatformsManager::clear()
{
    platformsVector.clear();
}

size_t PlatformsManager::getSize()
{
    return platformsVector.size();
}

std::vector<sf::RectangleShape> PlatformsManager::platformsVector;
sf::Texture PlatformsManager::platformTextures[3];
