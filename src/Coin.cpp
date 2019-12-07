#include "Coin.h"

Coin::Coin(sf::Vector2f pos, sf::Vector2f size, size_t value) : Collectable(pos, size, value)
{
    _path = "Assets/Images/Coin.png";
    _nOfFrames = 8;
    _size = sf::Vector2f(45.f, 48.f);
    _frequency = 0.1f;

    setAnimation(_path, _nOfFrames, _size, _frequency);
}

Coin::~Coin()
{
    deleteAnimation();
}
