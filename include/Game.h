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
#include"Goblin.h"
#include"Npc.h"
#include"Blacksmith.h"
#include"Menu.h"
#include"InteractionObject.h"
#include"Object_Doors.h"

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
        void initImages();
        void initView();
        void initMap(size_t lvl);
        void setScene(size_t lvl,const sf::Vector2f& pos);

        ///updates
        void pollevents();
        void updateView();
        void updateEnemies();
        void updateNpc();
        void updateObjects();

        ///renders
        void renderImages();
        void renderEnemies();
        void renderNpc();
        void renderObjects();

        ///free
        void freeEnemies();
        void freeNpc();
        void freeObjects();


    ///-----VARIABLES-----///

        ///window and view
        sf::RenderWindow *window;

        size_t currentLevel;
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
        std::vector<Goblin*> enemiesVector;

        ///Npc
        std::vector<Blacksmith*> blacksmithVector;

        ///Objects
        std::vector<Object_Doors*> doorsVector;

        ///Mouse
        sf::Vector2f mousePos;

        ///Backgrounds
        sf::Texture forest1Texture;

        sf::Sprite mapSprite[2];
};

#endif // GAME_H
