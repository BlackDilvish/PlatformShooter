#ifndef Player_H
#define Player_H

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<math.h>
#include"PlatformsManager.h"
#include"Enemy.h"
#include"Goblin.h"
#include"Animation.h"
#include"Collectable.h"

class Player
{
    public:
        Player();
        virtual ~Player();

        void render(sf::RenderTarget &window) const;
        void update(sf::RenderWindow &window, sf::View view,bool &gameOver,std::vector<Enemy*> &enemiesVector,std::vector<Collectable*> &collectableVector);

        void reset(sf::Vector2f pos,sf::Vector2f mapSize);
        void Talks(bool state);

        sf::Vector2f getSize() const;
        sf::Vector2f getPosition() const;
        sf::FloatRect getGlobalBounds() const;

    private:
        void initPlayer();
        void initVariables();
        void initShapes();
        void initAnimations();
        void initHealthBar();
        void initText();

        void updateInput();
        void updateTime();
        void updateShooting(sf::RenderWindow& window, sf::View view);
        void updateEnemiesInteraction(std::vector<Enemy*> &enemiesVector, bool &gameover);
        void updateCollectableInteraction(std::vector<Collectable*> &collectableVector);
        void updateWindowCollisions();
        void updatePlatformCollisions();
        void updateHealthBar(sf::RenderWindow& window, sf::View view);
        void updatePoints(size_t newPoints);

        void renderHealthBar(sf::RenderTarget &window) const;

        void deleteAnimations();

        void dealDamage(size_t damage, bool &gameover);
        bool canShoot() const;

        ///Variables
        sf::Vector2f velocity;
        sf::Vector2f playerSize;
        sf::Vector2f playerPosition;
        sf::Vector2f currentMapSize;

        sf::RectangleShape playerShape;
        sf::Texture playerTex;
        sf::Font _font;

        float movementSpeed;
        float gravity;
        bool inSpace;

        bool collidingTop;
        bool _talks;

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
        ///HealthBar

        sf::Texture hearthTex;
        sf::RectangleShape tempHearth;
        std::vector<sf::RectangleShape> hearthVector;
        size_t startingLife;
        size_t currentHP;

        bool invulnerableFlag;
        float invulnerableTimer;
        float invulnerableCooldown;
        ///Points

        sf::Text _pointsText;
        size_t _pointsCounter;
        ///Animation

        Animation* runAnimationRight;
        Animation* runAnimationLeft;
        Animation* idleAnimationRight;
        Animation* idleAnimationLeft;
};

#endif // Player_H
