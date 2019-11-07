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

        void update(sf::RenderWindow& window, Player& player, sf::Vector2f& deltaMove);
        void render(sf::RenderTarget& window);

        void initText(sf::Font& font);
        void popMessageBox(std::string message);
        void popDialogBox();

    private:

        void updateInteractionIcons(sf::Vector2f& mousePos);
        void updateDialogBox(sf::Vector2f& mousePos);

        sf::RectangleShape shape;

        struct MessBox
        {
            sf::RectangleShape canvas;
            sf::Text messageText;
            bool isDisplayed;
        }MessageBox;

        struct DialBox : public MessBox
        {
            sf::RectangleShape nextPage;
            int useLimit;
        }DialogBox;

        size_t numberOfPages;
        size_t currentPage;
        std::vector<std::string> messegesVector;

        struct interIcon
        {
            sf::RectangleShape icon;
            bool isDisplayed;
            int useLimit;
        }interactionIcon, dialogIcon;
};

#endif // NPC_H
