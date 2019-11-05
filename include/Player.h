#ifndef Player_H
#define Player_H

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<vector>
#include<math.h>
#include"PlatformsManager.h"
#include"Enemy.h"
#include"Animation.h"

class Player
{
    public:
        Player();
        virtual ~Player();

        void render(sf::RenderTarget &window);
        void update(sf::RenderWindow &window, sf::View view,PlatformsManager Pman,bool &gameOver,std::vector<Enemy> &enemiesVector);

        void reset(sf::Vector2f pos,sf::Vector2f mapSize);
        sf::Vector2f getSize();
        sf::Vector2f getPosition();
        sf::FloatRect getGlobalBounds();
    protected:

    private:
        void initPlayer();

        void updateInput();
        void updateTime();
        void updateShooting(sf::RenderWindow& window, sf::View view);
        void updateEnemiesInteraction(std::vector<Enemy> &enemiesVector);
        void updateWindowCollisions();
        void updatePlatformCollisions(PlatformsManager Pman);

        ///Variables
        sf::Vector2f velocity;
        sf::Vector2f playerSize;
        sf::Vector2f playerPosition;
        sf::Vector2f currentMapSize;

        sf::RectangleShape playerShape;
        sf::Texture playerTex;

        float movementSpeed;
        float gravity;
        bool inSpace;
        bool collidingTop;

        sf::Clock clock;
        float deltaTime;
        ///Bullets

        struct Bullet
        {
            sf::CircleShape bulletShape;
            sf::Vector2f bulletTrajectory;

            float periodOfLife;
            float lifeTimer;
        }tempBullet;

        std::vector<Bullet> bulletsVector;
        float bulletSpeed;
        float shootCooldown;
        float shootTimer;
        bool previousDirection;

        ///Animation

        Animation* runAnimationRight;
        Animation* runAnimationLeft;
        Animation* idleAnimationRight;
        Animation* idleAnimationLeft;
};

#endif // Player_H
