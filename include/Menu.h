#ifndef MENU_H
#define MENU_H

#include<SFML/Graphics.hpp>
#include"iostream"

class Menu
{
    public:
        Menu(sf::Vector2u size);
        virtual ~Menu();

        void update(const sf::RenderWindow& window, bool& gameover);
        void render(sf::RenderTarget& window);

        size_t getStatus();
        void setStatus(size_t newStatus);

        enum state {hidden,main,options};
    private:
        ///Functions
        void initText();

        ///Menu GUI
        sf::RectangleShape menuCanvas;
        size_t currentState;

        ///Variables
        sf::Font font;

        ///Main
        sf::RectangleShape resumeButton;
        sf::RectangleShape optionsButton;
        sf::RectangleShape exitButton;

        sf::Text resumeText;
        sf::Text optionsText;
        sf::Text exitText;
};

#endif // MENU_H
