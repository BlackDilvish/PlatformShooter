#ifndef INTERACTIONOBJECT_H
#define INTERACTIONOBJECT_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include"Player.h"

class InteractionObject
{
    public:
        InteractionObject(sf::Vector2f pos, sf::Vector2f size);
        virtual ~InteractionObject();

        void update(Player &player);
        void render(sf::RenderTarget &window);

    protected:
        void setTexture(std::string path);
        virtual void Interact(const Player &player);

    private:
        void updatePlayerCollision(const Player &player);


        sf::RectangleShape objShape;
        sf::Texture objTex;
};

#endif // INTERACTIONOBJECT_H
