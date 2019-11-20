#include "Game.h"

Game::Game()
{
    initWindow();
    initVariables();
    initImages();
    initView();
    initMap(currentLevel);
}

Game::~Game()
{
    freeEnemies();
    freeNpc();
    freeObjects();
    freeCollect();

    delete window;
}

void Game::initWindow()
{
    sf::VideoMode videomode = sf::VideoMode::getDesktopMode();

    window = new sf::RenderWindow(videomode, "Platformer", sf::Style::Fullscreen);
    window->setFramerateLimit(60);

    menu = new Menu(window->getSize());
}

void Game::initView()
{
    mainView.setCenter(window->getSize().x/2.f,window->getSize().y/2.f);
    mainView.setSize(sf::Vector2f(window->getSize().x,window->getSize().y));

    window->setView(mainView);
}

void Game::initVariables()
{
    gameover = false;
    isDead = false;
    currentLevel = 1;

    mapSize = sf::Vector2f(window->getSize().x, 0);

    defaultFont.loadFromFile("Assets/Fonts/Lato.ttf");
}

void Game::initImages()
{
    forest1Texture.loadFromFile("Assets/Images/forest1Background.png");

    mapSprite[0].setTexture(forest1Texture);
    mapSprite[1].setTexture(forest1Texture);
}

void Game::initMap(size_t mapId)
{
    currentLevel = mapId;
    freeEnemies();
    freeNpc();
    freeObjects();
    freeCollect();
    PlatformsManager::clear();

    std::stringstream ss;
    ss<<"Assets/Data/level"<<mapId<<".txt";
    std::ifstream configFile(ss.str());

    if(configFile.is_open())
    {
        std::string type;

        while(configFile>>type)
        {
            if(type == "platform:")
            {
                float platformParams[4];
                for(size_t i=0; i<4 ;i++)
                     configFile>>platformParams[i];

                PlatformsManager::addPlatform(platformParams);
            }
            else if(type == "Goblin(Platform):" || type == "Orc(Platform):")
            {
                int platformId;
                configFile>>platformId;

                if(type == "Goblin(Platform):")
                    enemiesVector.push_back(new Goblin(PlatformsManager::getPlatform(platformId)));
                else if(type == "Orc(Platform):")
                    enemiesVector.push_back(new Orc(PlatformsManager::getPlatform(platformId)));

            }
            else if(type == "Goblin:" || type == "Orc:")
            {
                float enemyParams[4];
                for(size_t i=0; i<4 ;i++)
                     configFile>>enemyParams[i];

                if(type == "Goblin:")
                    enemiesVector.push_back(new Goblin(enemyParams));
                else if(type == "Orc:")
                    enemiesVector.push_back(new Orc(enemyParams));

            }
            else if(type == "BlackSmith:")
            {
                std::vector<std::string> messagesNPC;
                std::string tempMessage;
                int count;
                float npcParams[4];

                for(size_t i=0; i<4 ;i++)
                    configFile>>npcParams[i];

                if(npcParams[2] == 0 && npcParams[3] == 0)
                    npcVector.push_back(new Blacksmith(sf::Vector2f(npcParams[0],npcParams[1])));
                else
                    npcVector.push_back(new Blacksmith(sf::Vector2f(npcParams[0],npcParams[1]), sf::Vector2f(npcParams[2],npcParams[3])));

                configFile>>count;
                for(int i=0; i<count; i++)
                {
                    configFile>>tempMessage;

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

                npcVector[npcVector.size() -1]->initText(defaultFont, messagesNPC);
            }
            else if(type == "Doors:")
            {
                float objParams[4];
                size_t scene;
                for(int i=0; i<4; i++)
                    configFile>>objParams[i];
                configFile>>scene;

                doorsVector.push_back(new Object_Doors({objParams[0], objParams[1]}, {objParams[2], objParams[3]}, scene));
            }
            else if(type == "Coin:")
            {
                float collectParams[4];
                size_t value;

                for(auto i : {0,1,2,3})
                    configFile>>collectParams[i];
                configFile>>value;

                collectVector.push_back(new Coin({collectParams[0], collectParams[1]}, {collectParams[2], collectParams[3]}, value));
            }
            else if(type == "mapSize:")
            {
                configFile>>mapSize.x;
                configFile>>mapSize.y;
            }
            else; ///"Undefined type of data in configuration file";
        }

        configFile.close();
    }
    else
        std::cout<<"Brak pliku\n";

    player1.reset({10,400}, mapSize);
    mainView.setCenter(sf::Vector2f(window->getSize())/2.f);
    setScene(currentLevel, sf::Vector2f(0, mapSize.y));
}

void Game::setScene(size_t lvl,const sf::Vector2f& pos)
{
    mapSprite[lvl-1].setPosition(pos);
}

void Game::pollevents()
{
    sf::Event event;

    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            gameover = true;

        if(event.type == sf::Event::KeyPressed)
            switch(event.key.code)
            {
            case sf::Keyboard::T:
                initMap(1);
                break;
            case sf::Keyboard::Escape:
                menu->open(mainView.getCenter() - sf::Vector2f(window->getSize())/2.f);
                break;
            default:
                break;
            }
    }

    if(menu->getStatus() != Menu::gameOver && isDead)
        menu->openGameover(mainView.getCenter() - sf::Vector2f(window->getSize())/2.f);

    if(gameover)
        window->close();
}

void Game::updateView()
{
    if( (player1.getPosition().x + player1.getSize().x/2.f > window->getSize().x/2.f)  &&  (player1.getPosition().x + player1.getSize().x/2.f < mapSize.x - window->getSize().x/2.f) )
        mainView.move(player1.getPosition().x + player1.getSize().x/2.f - mainView.getCenter().x, 0);

    if( (player1.getPosition().y + player1.getSize().y/2.f < window->getSize().y/2.f)  &&  (player1.getPosition().y + player1.getSize().y/2.f > mapSize.y + window->getSize().y/2.f) )
         mainView.move(0, player1.getPosition().y + player1.getSize().y/2.f - mainView.getCenter().y);

    if( player1.getPosition().y + player1.getSize().y == window->getSize().y)
        mainView.setCenter(mainView.getCenter().x, window->getSize().y/2.f);

    window->setView(mainView);
}

void Game::updateEnemies()
{
    for(auto&& enemy : enemiesVector)
        enemy->update();
}

void Game::updateNpc()
{
    sf::Vector2f deltaMove = mainView.getCenter() - sf::Vector2f(window->getSize())/2.f;

    for(auto&& npc : npcVector)
        npc->update(*window, player1, deltaMove);
}

void Game::updateObjects()
{
    for(auto&& door : doorsVector)
    {
        door->update(player1);

        if(door->getOpenStatus())
            initMap(door->getScene());
    }
}

void Game::updateCollect()
{
    for(auto&& collect : collectVector)
        collect->Update();
}

void Game::update()
{
    pollevents();

    if(menu->getStatus() == Menu::hidden)
    {
        player1.update(*window,mainView, isDead, enemiesVector, collectVector);
        updateEnemies();
        updateNpc();
        updateObjects();
        updateCollect();
    }

    updateView();
    menu->update(*window,gameover);
}

void Game::renderImages() const
{
    window->draw(mapSprite[currentLevel - 1]);
}

void Game::renderEnemies() const
{
    for(auto&& enemy : enemiesVector)
        enemy->render(*window);
}

void Game::renderNpc() const
{
    for(auto&& npc : npcVector)
        npc->render(*window);
}

void Game::renderObjects() const
{
    for(auto&& door : doorsVector)
        door->render(*window);
}

void Game::renderCollect() const
{
    for(auto&& collectable : collectVector)
        collectable->Render(*window);
}

void Game::render()
{
    window->clear();

    renderImages();
    PlatformsManager::render(*window);
    renderEnemies();
    renderNpc();
    renderObjects();
    renderCollect();
    player1.render(*window);
    menu->render(*window);

    window->display();
}

void Game::freeEnemies()
{
    for(auto&& enemy : enemiesVector)
        delete enemy;

    enemiesVector.clear();
}

void Game::freeNpc()
{
    for(auto&& npc : npcVector)
        delete npc;

    npcVector.clear();
}

void Game::freeObjects()
{
    for(auto&& door : doorsVector)
        delete door;

    doorsVector.clear();
}

void Game::freeCollect()
{
    for(auto&& collectable : collectVector)
        delete collectable;

    collectVector.clear();
}

const bool Game::isPlaying() const
{
    return !gameover;
}
