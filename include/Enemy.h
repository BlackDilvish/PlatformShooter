#ifndef ENEMY_H
#define ENEMY_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include"PlatformsManager.h"


class Enemy
{
    public:
        Enemy(sf::RectangleShape &platform);
        virtual ~Enemy();

        void update();
        void render(sf::RenderTarget& window);

        sf::FloatRect getGlobalBounds();
    protected:

    private:

        sf::RectangleShape enemyShape;
        sf::RectangleShape* bindedPlatform;
        float speed;

};

#endif // ENEMY_H
