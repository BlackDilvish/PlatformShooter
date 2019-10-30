#ifndef GAME_H
#define GAME_H

#include<vector>
#include<iostream>
#include<SFML/Graphics.hpp>
#include"Player.h"
#include"PlatformsManager.h"
#include"Enemy.h"

class Game
{
    public:
        Game();
        virtual ~Game();

        void update();
        void render();

        const bool isPlaying();

    protected:

    private:

    ///-----FUNCTIONS-----///

        ///initializes
        void initWindow();
        void initVariables();
        void initView();

        ///updates
        void pollevents();
        void updateView();
        void updateEnemies();

        ///renders
        void renderEnemies();


    ///-----VARIABLES-----///

        ///window and view
        sf::RenderWindow *window;
        bool gameover;

        sf::View mainView;
        sf::Vector2f mapSize;

        ///platform Management
        PlatformsManager platformManager;

        ///players
        Player player1;

        ///Enemies
        std::vector<Enemy> enemiesVector;

        ///Mouse
        sf::Vector2f mousePos;
};

#endif // GAME_H
