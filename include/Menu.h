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
        void render(sf::RenderTarget& window) const;

        size_t getStatus() const;
        void setStatus(size_t newStatus);

        void open(sf::Vector2f deltaMove);
        void openGameover(sf::Vector2f deltaMove);

        void setPosition(sf::Vector2f deltaMove);

        enum state {hidden,main,options,gameOver};
    private:
        ///Functions
        void initText();

        ///Menu GUI
        sf::RectangleShape menuCanvas;
        size_t currentState;

        sf::Vector2f dMove;

        ///Variables
        sf::Font font;

        ///Main
        sf::RectangleShape resumeButton;
        sf::RectangleShape optionsButton;
        sf::RectangleShape exitButton;

        sf::Text resumeText;
        sf::Text optionsText;
        sf::Text exitText;

        ///Gameover
        sf::RectangleShape gameoverCanvas;

        sf::Text gameoverText;
};

#endif // MENU_H
