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

        void initText(sf::Font& font, std::vector<std::string>& npcMessages);
        void popMessageBox(std::string message);
        void popDialogBox();

    protected:
        void setAnimation(char* path,size_t numberOfFrames,sf::Vector2f sizeOfFrame,float cooldown);
        void setAnimation(const sf::Texture& texture,size_t numberOfFrames,sf::Vector2f sizeOfFrame,float cooldown);
        void updateAnimations();
        void renderAnimations(sf::RenderTarget& window);
        void freeAnimation();

        void DefaultInfo(const std::string& info);

    private:

        void updateInteractionIcons(sf::Vector2f& mousePos);
        void updateDialogBox(sf::Vector2f& mousePos);

        sf::RectangleShape shape;
        Animation* idleAnimation;

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
        std::string _defaultInfo;

        struct interIcon
        {
            sf::RectangleShape icon;
            bool isDisplayed;
            int useLimit;
        }interactionIcon, dialogIcon;
};

#endif // NPC_H
