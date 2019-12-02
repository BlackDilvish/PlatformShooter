#include "Game.h"

Game::Game()
{
    initWindow();
    initVariables();
    initImages();
    initView();
    initMap(0);
}

Game::~Game()
{
    freeEnemies();
    freeNpc();
    freeObjects();
    freeCollect();

    delete gameMenu;
    delete window;
}

void Game::initWindow()
{
    sf::VideoMode videomode = sf::VideoMode::getDesktopMode();

    window = new sf::RenderWindow(videomode, "Platformer", sf::Style::Fullscreen);
    window->setFramerateLimit(60);

    gameMenu = new GameMenu(window->getSize());
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
    loadingTexture.loadFromFile("Assets/Images/load.png");

    mapSprite[0].setTexture(loadingTexture);
    mapSprite[1].setTexture(forest1Texture);
    mapSprite[2].setTexture(forest1Texture);

    PlatformsManager::initTextures();
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

    FileReader::AssignFile(ss.str(), defaultFont);
    FileReader::Load(enemiesVector, npcVector, doorsVector, collectVector, mapSize);

    player1.reset({10,800}, mapSize, collectVector.size());
    mainView.setCenter(sf::Vector2f(window->getSize())/2.f);
    setScene(currentLevel, sf::Vector2f(0, mapSize.y));
}

void Game::setScene(size_t lvl,const sf::Vector2f& pos)
{
    mapSprite[lvl].setPosition(pos);
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
                gameMenu->openGameover(mainView.getCenter() - sf::Vector2f(window->getSize())/2.f);
                break;
            case sf::Keyboard::Escape:
                if(gameMenu->getStatus() == GameMenu::hidden)
                    gameMenu->open(mainView.getCenter() - sf::Vector2f(window->getSize())/2.f);
                break;
            default:
                break;
            }
    }
}

void Game::updateView()
{
    if( (player1.getPosition().x + player1.getSize().x/2.f > window->getSize().x/2.f) && (player1.getPosition().x + player1.getSize().x/2.f < mapSize.x - window->getSize().x/2.f) )
        mainView.move(player1.getPosition().x + player1.getSize().x/2.f - mainView.getCenter().x, 0);

    if( (player1.getPosition().y + player1.getSize().y/2.f < window->getSize().y/2.f)  &&  (player1.getPosition().y + player1.getSize().y/2.f > mapSize.y + window->getSize().y/2.f) )
         mainView.move(0, player1.getPosition().y + player1.getSize().y/2.f - mainView.getCenter().y);

    if(player1.getPosition().y + player1.getSize().y == window->getSize().y)
        mainView.setCenter(mainView.getCenter().x, window->getSize().y/2.f);

    window->setView(mainView);
}

void Game::updateMenu()
{
    switch(gameMenu->getStatus())
    {
    case GameMenu::newGame:
        gameMenu->open(mainView.getCenter() - sf::Vector2f(window->getSize())/2.f);
        initMap(1);
        break;
    case GameMenu::restart:
        gameMenu->open(mainView.getCenter() - sf::Vector2f(window->getSize())/2.f);
        initMap(currentLevel);
        break;
    default:
        break;
    }

    gameMenu->update(*window,gameover);

    if(gameMenu->getStatus() != GameMenu::gameOver && isDead)
    {
        gameMenu->openGameover(mainView.getCenter() - sf::Vector2f(window->getSize())/2.f);
        isDead = false;
    }

    if(gameover)
        window->close();
}

void Game::updateEnemies()
{
    for(auto& enemy : enemiesVector)
        enemy->update();
}

void Game::updateNpc()
{
    sf::Vector2f deltaMove = mainView.getCenter() - sf::Vector2f(window->getSize())/2.f;

    for(auto& npc : npcVector)
        npc->update(*window, player1, deltaMove);
}

void Game::updateObjects()
{
    for(auto& door : doorsVector)
    {
        door->update(player1);

        if(door->getOpenStatus())
            initMap(door->getScene());
    }
}

void Game::updateCollect()
{
    for(auto& collect : collectVector)
        collect->Update();
}

void Game::update()
{
    pollevents();

    if(gameMenu->getStatus() == GameMenu::hidden)
    {
        player1.update(*window,mainView, isDead, enemiesVector, collectVector);
        updateEnemies();
        updateNpc();
        updateObjects();
        updateCollect();
    }

    updateView();
    updateMenu();
}

void Game::renderImages() const
{
    if(currentLevel)
        window->draw(mapSprite[currentLevel]);
}

void Game::renderEnemies() const
{
    for(auto& enemy : enemiesVector)
        enemy->render(*window);
}

void Game::renderNpc() const
{
    for(auto& npc : npcVector)
        npc->render(*window);
}

void Game::renderObjects() const
{
    for(auto& door : doorsVector)
        door->render(*window);
}

void Game::renderCollect() const
{
    for(auto& collectable : collectVector)
        collectable->Render(*window);
}

void Game::render()
{
    window->clear();

    renderImages();

    if(currentLevel)
    {
        PlatformsManager::render(*window);
        renderEnemies();
        renderNpc();
        renderObjects();
        renderCollect();
        player1.render(*window);
    }
    gameMenu->render(*window);

    window->display();
}

void Game::freeEnemies()
{
    for(auto& enemy : enemiesVector)
        delete enemy;

    enemiesVector.clear();
}

void Game::freeNpc()
{
    for(auto& npc : npcVector)
        delete npc;

    npcVector.clear();
}

void Game::freeObjects()
{
    for(auto& door : doorsVector)
        delete door;

    doorsVector.clear();
}

void Game::freeCollect()
{
    for(auto& collectable : collectVector)
        delete collectable;

    collectVector.clear();
}

const bool Game::isPlaying() const
{
    return !gameover;
}
