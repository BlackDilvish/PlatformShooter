#include "FileReader.h"

void FileReader::AssignFile(size_t mapId, sf::Font& defaultFont)
{
    _path = FileReader::FileToString(mapId);
    std::cout<<"Otwieranie: "<<_path<<"\n";
    _defaultFont = defaultFont;
}

void FileReader::LoadPlatform()
{
    float platformParams[4];
    int platformType;

    for(size_t i=0; i<4 ;i++)
         _configFile>>platformParams[i];
    _configFile>>platformType;

    PlatformsManager::addPlatform(platformParams, platformType);
}

void FileReader::LoadEnemies(std::vector<Enemy*> &enemiesVector, std::string type)
{
    float enemyParams[4];
    for(size_t i=0; i<4 ;i++)
         _configFile>>enemyParams[i];

    if(type == "Goblin:")
        enemiesVector.push_back(new Goblin(enemyParams));
    else if(type == "Orc:")
        enemiesVector.push_back(new Orc(enemyParams));
}

void FileReader::LoadEnemiesPlatform(std::vector<Enemy*> &enemiesVector, std::string type)
{
    int platformId;
    _configFile>>platformId;

    if(type == "Goblin(Platform):")
        enemiesVector.push_back(new Goblin(PlatformsManager::getPlatform(platformId)));
    else if(type == "Orc(Platform):")
        enemiesVector.push_back(new Orc(PlatformsManager::getPlatform(platformId)));
}

void FileReader::LoadNPC(std::vector<Npc*> &npcVector)
{
    std::vector<std::string> messagesNPC;
    std::string tempMessage;
    int count;
    float npcParams[4];

    for(size_t i=0; i<4 ;i++)
        _configFile>>npcParams[i];

    if(npcParams[2] == 0 && npcParams[3] == 0)
        npcVector.push_back(new Blacksmith(sf::Vector2f(npcParams[0],npcParams[1])));
    else
        npcVector.push_back(new Blacksmith(sf::Vector2f(npcParams[0],npcParams[1]), sf::Vector2f(npcParams[2],npcParams[3])));

    _configFile>>count;
    for(int i=0; i<count; i++)
    {
        _configFile>>tempMessage;

        ///Replacing underlines with spaces
        for(size_t j=0; j<tempMessage.length(); j++)
        {
            if(tempMessage[j] == '_')
                tempMessage[j] = ' ';
            else if(tempMessage[j] == '^')
                tempMessage[j] = '\n';
        }

        messagesNPC.push_back(tempMessage);
    }

    npcVector[npcVector.size() -1]->initText(_defaultFont, messagesNPC);
}

void FileReader::LoadDoors(std::vector<Object_Doors*> &doorsVector)
{
    float objParams[4];
    size_t scene;
    for(int i=0; i<4; i++)
        _configFile>>objParams[i];
    _configFile>>scene;

    doorsVector.push_back(new Object_Doors({objParams[0], objParams[1]},
                                           {objParams[2], objParams[3]},
                                            scene));
}

void FileReader::LoadCollectables(std::vector<Collectable*> &collectVector)
{
    float collectParams[4];
    size_t value;

    for(auto i : {0,1,2,3})
        _configFile>>collectParams[i];
    _configFile>>value;

    collectVector.push_back(new Coin({collectParams[0], collectParams[1]},
                                     {collectParams[2], collectParams[3]},
                                      value));
}

void FileReader::LoadMapSize(sf::Vector2f& mapSize)
{
    _configFile>>mapSize.x;
    _configFile>>mapSize.y;
}

void FileReader::Load(std::vector<Enemy*>&        enemiesVector,
                      std::vector<Npc*>&          npcVector,
                      std::vector<Object_Doors*>& doorsVector,
                      std::vector<Collectable*>&  collectVector,
                      sf::Vector2f&               mapSize)
{
    _configFile.open(_path);

    if(_configFile.is_open())
    {
        std::string type;

        while(_configFile>>type)
        {
            if(type == "platform:")
                FileReader::LoadPlatform();
            else if(type == "Goblin(Platform):" || type == "Orc(Platform):")
                FileReader::LoadEnemiesPlatform(enemiesVector, type);
            else if(type == "Goblin:" || type == "Orc:")
                FileReader::LoadEnemies(enemiesVector, type);
            else if(type == "BlackSmith:")
                FileReader::LoadNPC(npcVector);
            else if(type == "Doors:")
                FileReader::LoadDoors(doorsVector);
            else if(type == "Coin:")
                FileReader::LoadCollectables(collectVector);
            else if(type == "mapSize:")
                FileReader::LoadMapSize(mapSize);
        }

        _configFile.close();
    }
    else
        std::cout<<"Brak pliku\n";
}

std::string FileReader::FileToString(size_t id)
{
    std::stringstream ss;
    ss<<"Assets/Data/level"<<id<<".txt";

    return ss.str();
}

std::string FileReader::_path;
std::ifstream FileReader::_configFile;
sf::Font FileReader::_defaultFont;
