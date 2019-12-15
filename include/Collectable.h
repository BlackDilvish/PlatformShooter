#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include"Animation.h"

class Collectable
{
    public:
        Collectable(sf::Vector2f pos, sf::Vector2f size, size_t value);
        virtual ~Collectable() = default;

        void Update();
        void Render(sf::RenderTarget& window) const;

        sf::FloatRect getGlobalBounds() const;

    protected:
        void setTexture(char* path);
        void setTexture(const sf::Texture& texture);
        void setAnimation(char* path,size_t numberOfFrames,sf::Vector2f sizeOfFrame,float cooldown);
        void setAnimation(const sf::Texture& texture,size_t numberOfFrames,sf::Vector2f sizeOfFrame,float cooldown);
        void deleteTexture();
        void deleteAnimation();

    private:
        sf::RectangleShape _shape;
        sf::Texture* _collectTexture;
        Animation* _collectAnimation;

        size_t _value;

        float _rangeLimit;
        float _topRange;
        float _bottomRange;
        float _velocity;
};

#endif // COLLECTABLE_H
