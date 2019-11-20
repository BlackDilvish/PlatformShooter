#ifndef MENU_H
#define MENU_H

#include<SFML/Graphics.hpp>
#include"iostream"
#include"Button.h"
#include"Canvas.h"

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
        void initCanvases(sf::Vector2u size);
        void initButtons();

        void deleteCanvases();
        void deleteButtons();

        ///Variables
        size_t currentState;
        sf::Font font;

        sf::Vector2f buttonSize;
        sf::Vector2f dMove;

        ///GUI

            ///Canvas
            Canvas* menuCanvas;
            Canvas* gameoverCanvas;

            ///Buttons
            Button* resumeButton;
            Button* optionsButton;
            Button* exitButton;
};

#endif // MENU_H
