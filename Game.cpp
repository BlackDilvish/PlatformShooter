#include "Game.h"

Game::Game()
{
    initWindow();
    initVariables();
    initView();
    player1.reset({100.f,100.f}, mapSize);
}

Game::~Game()
{
    delete window;
}

void Game::initWindow()
{
    sf::VideoMode videomode;
    videomode.width = 960;
    videomode.height = 720;

    window = new sf::RenderWindow(videomode, "Platformer");

    window->setFramerateLimit(60);
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

    mapSize = {2000.f, (float)window->getSize().y};
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
                platformManager.addPlatform({300.f,50.f},{600.f,600.f});
                platformManager.addPlatform({300.f,50.f},{1000.f,400.f});
                platformManager.addPlatform({300.f,50.f},{1500.f,600.f});
                enemiesVector.push_back(Enemy(platformManager[1]));
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

    window->setView(mainView);
}

void Game::updateEnemies()
{
    for(size_t i=0; i<enemiesVector.size(); i++)
        enemiesVector[i].update();
}

void Game::update()
{
    pollevents();
    player1.update(*window,mainView, platformManager, gameover, enemiesVector);
    updateEnemies();
    updateView();
}

void Game::renderEnemies()
{
    for(size_t i=0; i<enemiesVector.size();i++)
        enemiesVector[i].render(*window);
}

void Game::render()
{
    window->clear();

    platformManager.render(*window);
    renderEnemies();
    player1.render(*window);

    window->display();
}

const bool Game::isPlaying()
{
    return !gameover;
}
