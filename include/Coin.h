#ifndef COIN_H
#define COIN_H

#include<SFML/Graphics.hpp>
#include"Collectable.h"

class Coin : public Collectable
{
    public:
        Coin(sf::Vector2f pos, sf::Vector2f size = {40.f, 40.f}, size_t value = 1);
        virtual ~Coin();

    private:
        char* _path;
        size_t _nOfFrames;
        sf::Vector2f _size;
        float _frequency;
};

#endif // COIN_H
