#ifndef ENEMY_H
#define ENEMY_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include"PlatformsManager.h"
#include"Animation.h"


class Enemy
{
    public:
        Enemy(sf::RectangleShape &platform);
        Enemy(const sf::Vector2f &Position,const sf::Vector2f &Range);
        Enemy(float *enemyParams);
        virtual ~Enemy();

        void update();
        void render(sf::RenderTarget& window);

        sf::FloatRect getGlobalBounds();
        size_t getHP();

        void setHP(size_t newHP);
    protected:
        void setAnimation(char* path,size_t numberOfFrames,sf::Vector2f sizeOfFrame,float cooldown);
        void updateAnimations();
        void renderAnimations(sf::RenderTarget& window);
        void freeAnimation();

    private:
        void initVariables();

        sf::RectangleShape enemyShape;
        sf::Vector2f movingRange;
        float speed;

        sf::RectangleShape redHealthBar;
        sf::RectangleShape greenHealthBar;
        size_t maxHP;
        size_t currHP;

        Animation* walkAnimationRight;
        Animation* walkAnimationLeft;

};

#endif // ENEMY_H
