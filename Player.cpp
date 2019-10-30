#include "Player.h"

Player::Player()
{
    initPlayer();
}

Player::~Player()
{
    //dtor
}

void Player::initPlayer()
{
    playerSize={50.f, 50.f};
    playerPosition={100.f,100.f};
    movementSpeed=10.f;
    gravity=9.81f;

    bulletSpeed = 5.f;
    shootCooldown = 1.f;
    shootTimer = 0;
    deltaTime = 0;

    inSpace=true;
    collidingTop=false;
    //playerTex.loadFromFile("assets/images/player1.png");


    playerShape.setSize(playerSize);
    //playerShape.setTexture(&playerTex);
    playerShape.setPosition(playerPosition);

    tempBullet.bulletShape.setRadius(5.f);
    tempBullet.bulletShape.setFillColor(sf::Color::Red);

    tempBullet.periodOfLife = 2.f;
    tempBullet.lifeTimer = 0;
}

void Player::reset(sf::Vector2f pos,sf::Vector2f mapSize)
{
    //playerShape.setTexture(&playerTex);
    playerShape.setPosition(pos);
    currentMapSize = mapSize;
}

void Player::updateTime()
{
    deltaTime = clock.getElapsedTime().asSeconds();

    shootTimer += deltaTime;
    for(size_t i=0; i<bulletsVector.size(); i++)
        bulletsVector[i].lifeTimer += deltaTime;

    deltaTime = 0;
    clock.restart();
}

void Player::updateInput()
{
    velocity.x=0;

    if(inSpace)
        velocity.y+=gravity*0.15;
    else
        velocity.y=0;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !inSpace )
    {
        inSpace=true;
        velocity.y-=gravity*3;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocity.x-=movementSpeed;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocity.x+=movementSpeed;

    playerShape.move(velocity);
}

void Player::updateShooting(sf::RenderWindow& window, sf::View view)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootTimer > shootCooldown)
    {
        shootTimer = 0;

        sf::Vector2f playerPos = (getPosition() + getSize()/2.f) - (view.getCenter() - sf::Vector2f(window.getSize())/2.f);

        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window)) - playerPos;
        float mouseSize = sqrt(pow(mousePos.x,2) + pow(mousePos.y,2));
        mousePos /= mouseSize;

        tempBullet.bulletShape.setPosition(getPosition() + getSize()/2.f);
        tempBullet.bulletTrajectory = mousePos*bulletSpeed;

        bulletsVector.push_back(tempBullet);
    }

    for(size_t i=0; i<bulletsVector.size(); i++)
    {
        bulletsVector[i].bulletShape.move(bulletsVector[i].bulletTrajectory);

        if(bulletsVector[i].lifeTimer > bulletsVector[i].periodOfLife)
        {
            bulletsVector.erase(bulletsVector.begin() + i);
        }
    }

}

void Player::updateEnemiesInteraction(std::vector<Enemy> &enemiesVector)
{
    for(size_t i=0; i<enemiesVector.size(); i++)
    {
        if(playerShape.getGlobalBounds().intersects(enemiesVector[i].getGlobalBounds()))
            std::cout<<"Kolizja! Zrobie pozniej";

        for(size_t j=0; j<bulletsVector.size(); j++)
            if(bulletsVector[j].bulletShape.getGlobalBounds().intersects(enemiesVector[i].getGlobalBounds()))
            {
                bulletsVector.erase(bulletsVector.begin() + j);
                enemiesVector.erase(enemiesVector.begin() + i);
            }
    }
}

void Player::updateWindowCollisions()
{
    sf::FloatRect playerBounds=playerShape.getGlobalBounds();

    if(playerBounds.top + playerBounds.height >= currentMapSize.y)
    {
        playerShape.setPosition(playerBounds.left, currentMapSize.y - playerBounds.height);

        if(inSpace)
            inSpace=false;
    }
    if(playerBounds.top <= 0)
    {
        playerShape.setPosition(playerBounds.left, 0);
        velocity.y=0;
    }
    if(playerBounds.left <= 0)
        playerShape.setPosition(0, playerBounds.top);
    if(playerBounds.left + playerBounds.width >= currentMapSize.x)
        playerShape.setPosition(currentMapSize.x - playerBounds.width, playerBounds.top);
}

void Player::updatePlatformCollisions(PlatformsManager Pman)
{
    sf::FloatRect playerBounds=playerShape.getGlobalBounds();
    collidingTop=false;

    for(size_t i=0;i<Pman.getSize();i++)
    {
        if(playerShape.getGlobalBounds().intersects(Pman[i].getGlobalBounds()))
        {
            sf::FloatRect wallBounds=Pman[i].getGlobalBounds();

            if(playerBounds.left<wallBounds.left
               && playerBounds.left+playerBounds.width<wallBounds.left+wallBounds.width
               && playerBounds.top<wallBounds.top+wallBounds.height
               && playerBounds.top+playerBounds.height>wallBounds.top)
            {
                velocity.x=0.f;
                playerShape.setPosition(wallBounds.left-playerBounds.width,playerBounds.top);
            }
            else if(playerBounds.left>wallBounds.left
               && playerBounds.left+playerBounds.width>wallBounds.left+wallBounds.width
               && playerBounds.top<wallBounds.top+wallBounds.height
               && playerBounds.top+playerBounds.height>wallBounds.top)
            {
                velocity.x=0.f;
                playerShape.setPosition(wallBounds.left+wallBounds.width,playerBounds.top);
            }

            if(playerBounds.top<wallBounds.top
               && playerBounds.top+playerBounds.height<wallBounds.top+wallBounds.height
               && playerBounds.left<wallBounds.left+wallBounds.width
               && playerBounds.left+playerBounds.width>wallBounds.left)
            {
                velocity.y=0.f;
                playerShape.setPosition(playerBounds.left,wallBounds.top-playerBounds.height);
                collidingTop=true;

                if(inSpace);
                    inSpace=false;
            }
            else if(playerBounds.top>wallBounds.top
               && playerBounds.top+playerBounds.height>wallBounds.top+wallBounds.height
               && playerBounds.left<wallBounds.left+wallBounds.width
               && playerBounds.left+playerBounds.width>wallBounds.left)
            {
                velocity.y=0.f;
                playerShape.setPosition(playerBounds.left,wallBounds.top+playerBounds.height);
            }
        }

    }

    if(playerBounds.top + playerBounds.height<720 && !collidingTop)
        inSpace=true;
}


void Player::update(sf::RenderWindow &window,sf::View view,PlatformsManager Pman,bool &gameOver,std::vector<Enemy> &enemiesVector)
{
    updateTime();
    updateInput();
    updateWindowCollisions();
    updateShooting(window,view);
    updateEnemiesInteraction(enemiesVector);
    updatePlatformCollisions(Pman);
}

void Player::render(sf::RenderTarget &window)
{
    window.draw(playerShape);

    for(size_t i=0; i<bulletsVector.size(); i++)
        window.draw(bulletsVector[i].bulletShape);
}

sf::Vector2f Player::getPosition()   {return playerShape.getPosition(); }
sf::Vector2f Player::getSize()       {return playerShape.getSize();     }
