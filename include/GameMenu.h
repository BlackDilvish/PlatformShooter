#ifndef GAMEMENU_H
#define GAMEMENU_H

#include<SFML/Graphics.hpp>
#include"iostream"
#include"Button.h"
#include"Canvas.h"
#include"IMenu.h"
#include"LevelEditor.h"

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

        enum state {title, newGame, hidden, main, options, restart, gameOver, inEditor};
    private:

        ///Functions
        void initCanvases(sf::Vector2u size);
        void initButtons();
        void initEditor(sf::Vector2u size);
        void openEditor();

        void updateMainmenu(const sf::Vector2f& mousePos);
        void updateTitlemenu(const sf::Vector2f& mousePos, bool& gameover);
        void updateGameoverMenu(const sf::Vector2f& mousePos);
        void updateEditor(const sf::Vector2f& mousePos);

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
            Button* _editorButton;

            ///Editor

            LevelEditor* _levelEditor;
};

#endif // MENU_H
