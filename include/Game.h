#ifndef GAME_H
#define GAME_H

#include<vector>
#include<iostream>
#include<sstream>
#include<fstream>
#include<SFML/Graphics.hpp>
#include"Player.h"
#include"PlatformsManager.h"
#include"Enemy.h"
#include"Npc.h"
#include"Menu.h"

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
        void initMap(size_t mapId);

        ///updates
        void pollevents();
        void updateView();
        void updateEnemies();
        void updateNpc();

        ///renders
        void renderEnemies();
        void renderNpc();


    ///-----VARIABLES-----///

        ///window and view
        sf::RenderWindow *window;
        bool gameover;

        sf::View mainView;
        sf::Vector2f mapSize;

        Menu* menu;

        ///Text
        sf::Font defaultFont;

        ///platform Management
        PlatformsManager platformManager;

        ///players
        Player player1;

        ///Enemies
        std::vector<Enemy> enemiesVector;

        ///Npcs
        std::vector<Npc> npcVector;

        ///Mouse
        sf::Vector2f mousePos;
};

#endif // GAME_H
