#ifndef COIN_H
#define COIN_H

#include<SFML/Graphics.hpp>
#include"Collectable.h"

class Coin : public Collectable
{
    public:
        Coin(sf::Vector2f size, sf::Vector2f pos, size_t value);
        virtual ~Coin();

    private:
        char* _path;
        size_t _nOfFrames;
        sf::Vector2f _size;
        float _frequency;
};

#endif // COIN_H
