#ifndef TITLEMENU_H
#define TITLEMENU_H

#include<SFML/Graphics.hpp>
#include"IMenu.h"
#include"Canvas.h"
#include"Button.h"

class TitleMenu : public IMenu
{
    public:
        TitleMenu(sf::Vector2u size);
        virtual ~TitleMenu();

        void update(const sf::RenderWindow& window, bool& gameover);
        void render(sf::RenderTarget& window) const;

        enum State {hidden, newGame, main, options};

    private:
        void initCanvases(sf::Vector2u size);
        void initButtons();

        void deleteCanvases();
        void deleteButtons();

        ///GUI
            ///Canvas
            Canvas* _mainCanvas;

            ///Buttons
            Button* _newGameButton;
            Button* _optionsButton;
            Button* _exitButton;
};

#endif // TITLEMENU_H
