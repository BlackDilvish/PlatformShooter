#ifndef FILEREADER_H
#define FILEREADER_H

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<SFML/Graphics.hpp>
#include"PlatformsManager.h"
#include"Enemy.h"
#include"Goblin.h"
#include"Orc.h"
#include"Npc.h"
#include"Blacksmith.h"
#include"InteractionObject.h"
#include"Object_Doors.h"
#include"Collectable.h"
#include"Coin.h"

class FileReader
{
    public:
        static void Load(std::vector<Enemy*> &enemiesVector,
                         std::vector<Npc*> &npcVector,
                         std::vector<Object_Doors*> &doorsVector,
                         std::vector<Collectable*> &collectVector,
                         sf::Vector2f& mapSize);

        static void AssignFile(size_t mapId, sf::Font& defaultFont);

    private:
        FileReader() = default;
        ~FileReader() = default;

        ///Load functions

        static void LoadPlatform();
        static void LoadEnemies(std::vector<Enemy*> &enemiesVector, std::string type);
        static void LoadEnemiesPlatform(std::vector<Enemy*> &enemiesVector, std::string type);
        static void LoadNPC(std::vector<Npc*> &npcVector);
        static void LoadDoors(std::vector<Object_Doors*> &doorsVector);
        static void LoadCollectables(std::vector<Collectable*> &collectVector);
        static void LoadMapSize(sf::Vector2f& mapSize);

        ///Utilities functions

        static std::string FileToString(size_t id);

        ///Variables

        static std::ifstream _configFile;
        static std::string _path;
        static sf::Font _defaultFont;
};

#endif // FILEREADER_H
