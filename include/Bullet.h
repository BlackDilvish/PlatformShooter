#ifndef BULLET_H
#define BULLET_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include"PlatformsManager.h"

class Bullet
{
    public:
        Bullet(sf::Vector2f pos, sf::Vector2f dir, float radius = 5.f, sf::Color color = sf::Color::Red, float lifetime = 2.f, float speed = 5.f);
        virtual ~Bullet() = default;

        void Update();
        void Render(sf::RenderTarget& window) const;

        sf::FloatRect getGlobalBounds() const;
        bool Hit(sf::FloatRect hitbox) const;
        bool Dead();

    private:
        void CollisionWithPlatforms();
        void UpdateTime();

        sf::Clock _clock;
        float _bulletSpeed;

        sf::CircleShape _bulletShape;
        sf::Vector2f _bulletTrajectory;

        float _lifeTimer;
        float _periodOfLife;

};

#endif // BULLET_H
