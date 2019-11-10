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
    currentLevel = 1;

    mapSize = sf::Vector2f(window->getSize().x, 0);

    defaultFont.loadFromFile("Assets/Fonts/Lato.ttf");
}

void Game::initImages()
{
    forest1Texture.loadFromFile("Assets/Images/forest1Background.png");

    mapSprite[0].setTexture(forest1Texture);
}

void Game::initMap(size_t mapId)
{
    currentLevel = mapId;
    freeEnemies();
    platformManager.clear();

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

                platformManager.addPlatform(platformParams);
            }
            else if(type == "enemyOnPlatform:")
            {
                int platformId;
                configFile>>platformId;

                Goblin* temp = new Goblin(platformManager[platformId]);
                enemiesVector.push_back(temp);
            }
            else if(type == "enemyFree:")
            {
                float enemyParams[4];
                for(size_t i=0; i<4 ;i++)
                     configFile>>enemyParams[i];

                Goblin* temp = new Goblin(enemyParams);
                enemiesVector.push_back(temp);
            }
            else if(type == "NPC:")
            {
                std::vector<std::string> messagesNPC;
                std::string tempMessage;
                int count;
                float npcParams[4];

                for(size_t i=0; i<4 ;i++)
                    configFile>>npcParams[i];

                if(npcParams[2] == 0 && npcParams[3] == 0)
                    npcVector.push_back(Npc(sf::Vector2f(npcParams[0],npcParams[1])));
                else
                    npcVector.push_back(Npc(sf::Vector2f(npcParams[0],npcParams[1]), sf::Vector2f(npcParams[2],npcParams[3])));

                configFile>>count;
                for(int i=0; i<count; i++)
                {
                    configFile>>tempMessage;

                    ///Replacing underlines with spaces
                    for(size_t j=0; j<tempMessage.length(); j++)
                        if(tempMessage[j] == '_')
                            tempMessage[j] = ' ';

                    messagesNPC.push_back(tempMessage);
                }

                npcVector[npcVector.size() -1].initText(defaultFont, messagesNPC);
            }
            else if(type == "mapSize:")
            {
                configFile>>mapSize.x;
                configFile>>mapSize.y;
            }
            else
                std::cout<<"Undefined type of data in config file\n";
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
    for(size_t i=0; i<enemiesVector.size(); i++)
        enemiesVector[i]->update();
}

void Game::updateNpc()
{
    sf::Vector2f deltaMove = mainView.getCenter() - sf::Vector2f(window->getSize())/2.f;

    for(size_t i=0; i<npcVector.size(); i++)
        npcVector[i].update(*window, player1, deltaMove);
}

void Game::update()
{
    pollevents();

    if(menu->getStatus() == Menu::hidden)
    {
        player1.update(*window,mainView, platformManager, gameover, enemiesVector);
        updateEnemies();
        updateNpc();
    }

    updateView();
    menu->update(*window,gameover);
}

void Game::renderImages()
{
    switch(currentLevel)
    {
    case 1:
        window->draw(mapSprite[0]);
        break;
    default:
        break;
    }
}

void Game::renderEnemies()
{
    for(size_t i=0; i<enemiesVector.size();i++)
        enemiesVector[i]->render(*window);
}

void Game::renderNpc()
{
    for(size_t i=0; i<npcVector.size(); i++)
        npcVector[i].render(*window);
}

void Game::render()
{
    window->clear();

    renderImages();
    platformManager.render(*window);
    renderEnemies();
    renderNpc();
    player1.render(*window);
    menu->render(*window);

    window->display();
}

void Game::freeEnemies()
{
    for(size_t i=0; i<enemiesVector.size(); i++)
        delete enemiesVector[i];

    enemiesVector.clear();
}

const bool Game::isPlaying()
{
    return !gameover;
}
