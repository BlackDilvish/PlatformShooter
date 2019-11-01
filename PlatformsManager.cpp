#include "PlatformsManager.h"

PlatformsManager::PlatformsManager()
{

}

PlatformsManager::~PlatformsManager()
{

}

void PlatformsManager::addPlatform(sf::Vector2f size, sf::Vector2f pos)
{
    sf::RectangleShape tempPlatform;
    tempPlatform.setSize(size);
    tempPlatform.setPosition(pos);

    platformsVector.push_back(tempPlatform);
}

void PlatformsManager::addPlatform(float *platformParams)
{
    sf::RectangleShape tempPlatform;
    tempPlatform.setSize(sf::Vector2f(platformParams[0],platformParams[1]));
    tempPlatform.setPosition(sf::Vector2f(platformParams[2],platformParams[3]));

    platformsVector.push_back(tempPlatform);
}

void PlatformsManager::render(sf::RenderTarget &window)
{
    for(size_t i=0; i<platformsVector.size(); i++)
        window.draw(platformsVector[i]);
}

sf::RectangleShape& PlatformsManager::operator[](size_t id)
{
    return platformsVector[id];
}

void PlatformsManager::destroyPlatform(size_t id)
{
    platformsVector.erase(platformsVector.begin() + id);
}

size_t PlatformsManager::getSize()
{
    return platformsVector.size();
}
