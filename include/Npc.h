#ifndef NPC_H
#define NPC_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include"Player.h"

class Npc
{
    public:
        Npc(sf::Vector2f Position,const sf::Vector2f size = {90.f,90.f});
        virtual ~Npc();

        void update(Player& player);
        void render(sf::RenderTarget& window);
        void popMessageBox(std::string message);

    private:

        sf::RectangleShape shape;

        sf::Font font;

        struct MessBox
        {
            sf::RectangleShape canvas;
            sf::Text messageText;
            bool isDisplayed;
        }MessageBox;

        struct interIcon
        {
            sf::RectangleShape icon;
            bool isDisplayed;
        }interactionIcon;
};

#endif // NPC_H
