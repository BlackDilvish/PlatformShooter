#ifndef GAME_H
#define GAME_H

#include<vector>
#include<iostream>
#include<sstream>
#include<fstream>
#include<SFML/Graphics.hpp>
#include"Icon.c"
#include"Player.h"
#include"PlatformsManager.h"
#include"Enemy.h"
#include"Goblin.h"
#include"Orc.h"
#include"Npc.h"
#include"Blacksmith.h"
#include"GameMenu.h"
#include"InteractionObject.h"
#include"Object_Doors.h"
#include"Collectable.h"
#include"Coin.h"
#include"FileReader.h"
#include"TexturesManager.h"

class Game
{
    public:
        Game();
        virtual ~Game();

        void update();
        void render();

        const bool isPlaying() const;

    private:

    ///-----FUNCTIONS-----///

        ///initializes
        void initWindow();
        void initVariables();
        void initImages();
        void initView();
        void initMap(size_t lvl);
        void setScene(size_t lvl,const sf::Vector2f& pos);
        void setView();

        ///updates
        void pollevents();
        void updateView();
        void updateMenu();
        void updateExit();
        void updateEnemies();
        void updateNpc();
        void updateObjects();
        void updateCollect();

        ///renders
        void renderImages() const;
        void renderEnemies() const;
        void renderNpc() const;
        void renderObjects() const;
        void renderCollect() const;

        ///free
        void ClearLevel();
        void freeEnemies();
        void freeNpc();
        void freeObjects();
        void freeCollect();


    ///-----VARIABLES-----///

        ///window and view
        sf::RenderWindow *window;

        size_t currentLevel;
        bool gameover;
        bool isDead;

        sf::View mainView;
        sf::Vector2f mapSize;
        sf::Vector2f _playerPosition;

        ///Menu
        GameMenu* gameMenu;

        ///Text
        sf::Font defaultFont;

        ///players
        Player player1;

        ///Enemies
        std::vector<Enemy*> enemiesVector;

        ///Npc
        std::vector<Npc*> npcVector;

        ///Objects
        std::vector<Object_Doors*> doorsVector;

        ///Collect
        std::vector<Collectable*> collectVector;

        ///Mouse
        sf::Vector2f mousePos;

        ///Backgrounds
        sf::Texture forest1Texture;
        sf::Texture loadingTexture;

        sf::Sprite mapSprite[4];
};

#endif // GAME_H
