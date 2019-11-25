#ifndef GAMEMENU_H
#define GAMEMENU_H

#include<SFML/Graphics.hpp>
#include"iostream"
#include"Button.h"
#include"Canvas.h"
#include"IMenu.h"

class GameMenu : public IMenu
{
    public:
        GameMenu(sf::Vector2u size);
        virtual ~GameMenu();

        void update(const sf::RenderWindow& window, bool& gameover);
        void render(sf::RenderTarget& window) const;

        void open(sf::Vector2f deltaMove);
        void openGameover(sf::Vector2f deltaMove);

        void setPosition(sf::Vector2f deltaMove);

        enum state {title, newGame, hidden, main, options, restart, gameOver};
    private:

        ///Functions
        void initCanvases(sf::Vector2u size);
        void initButtons();

        void deleteCanvases();
        void deleteButtons();

        ///GUI
            ///Variables
            sf::Vector2f dMove;

            ///Canvas
            Canvas* menuCanvas;
            Canvas* gameoverCanvas;
            Canvas* _titleCanvas;

            ///Buttons
            Button* resumeButton;
            Button* optionsButton;
            Button* exitButton;
            Button* _restartButton;

            Button* _newGameButton;
            Button* _optionsButton;
            Button* _exitButton;
};

#endif // MENU_H
