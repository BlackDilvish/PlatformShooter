#include "Player.h"

Player::Player()
{
    initPlayer();
}

Player::~Player()
{
    deleteAnimations();
}

void Player::initPlayer()
{
    initVariables();
    initShapes();
    initAnimations();
    initHealthBar();
    initText();
}

void Player::initVariables()
{
    playerSize={90.f, 105.f};
    playerPosition={100.f,100.f};
    movementSpeed=10.f;
    gravity=9.81f;
    previousDirection=1;

    bulletSpeed = 5.f;
    shootCooldown = 1.f;
    shootTimer = 0;
    deltaTime = 0;

    startingLife = 3;
    currentHP = startingLife;

    invulnerableFlag = false;
    invulnerableCooldown = 3.f;
    invulnerableTimer = 0;

    inSpace=true;
    collidingTop=false;
    _talks = false;
}

void Player::initShapes()
{
    playerShape.setSize(playerSize);
    playerShape.setPosition(playerPosition);

    tempBullet.bulletShape.setRadius(5.f);
    tempBullet.bulletShape.setFillColor(sf::Color::Red);

    tempBullet.periodOfLife = 2.f;
    tempBullet.lifeTimer = 0;
}

void Player::initAnimations()
{
    runAnimationRight = new Animation((char*)"Assets/Images/MageRun.png",5,{978, 1127},playerShape.getSize(),0.08f,true,false);
    runAnimationLeft = new Animation((char*)"Assets/Images/MageRun.png",5,{978, 1127},playerShape.getSize(),0.08f,true,true);
    idleAnimationRight = new Animation((char*)"Assets/Images/MageStands.png",5,{867, 1059},playerShape.getSize(),0.15f,true,false);
    idleAnimationLeft = new Animation((char*)"Assets/Images/MageStands.png",5,{867, 1059},playerShape.getSize(),0.15f,true,true);
}

void Player::initText()
{
    _font.loadFromFile("Assets/Fonts/McLaren.ttf");

    _pointsText.setFont(_font);
    _pointsText.setCharacterSize(32);
    _pointsText.setPosition(hearthVector[hearthVector.size()-1].getPosition());
    updatePoints(0);
}

void Player::initHealthBar()
{
    hearthTex.loadFromFile("Assets/Images/PixelHearth.png");

    tempHearth.setSize(sf::Vector2f(50.f, 50.f));
    tempHearth.setTexture(&hearthTex);

    for(size_t i=0; i<startingLife; i++)
        hearthVector.push_back(tempHearth);

}

void Player::reset(sf::Vector2f pos,sf::Vector2f mapSize)
{
    playerShape.setPosition(pos);
    currentMapSize = mapSize;

    hearthVector.clear();
    for(size_t i=0; i<startingLife; i++)
    {
        tempHearth.setPosition(tempHearth.getPosition() + sf::Vector2f(tempHearth.getSize().x * i, 0));
        hearthVector.push_back(tempHearth);
    }
}

void Player::updateTime()
{
    deltaTime = clock.getElapsedTime().asSeconds();

    shootTimer += deltaTime;

    if(invulnerableFlag)
        invulnerableTimer += deltaTime;

    for(size_t i=0; i<bulletsVector.size(); i++)
        bulletsVector[i].lifeTimer += deltaTime;

    deltaTime = 0;
    clock.restart();
}

void Player::updateInput()
{
    velocity.x=0;

    ///Player falls faster then he hovers
    if(inSpace)
        if(velocity.y < 0)
            velocity.y+=gravity*0.15;
        else
            velocity.y+=gravity*0.2;
    else
        velocity.y=0;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !inSpace)
    {
        inSpace=true;
        velocity.y-=gravity*3;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocity.x-=movementSpeed;
        previousDirection = 0;

        if(!inSpace)
            runAnimationLeft->update();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocity.x+=movementSpeed;
        previousDirection = 1;

        if(!inSpace)
            runAnimationRight->update();
    }
    else if(!inSpace)
    {
        if(previousDirection)
            idleAnimationRight->update();
        else
            idleAnimationLeft->update();
    }

    playerShape.move(velocity);

    if(collidingTop)
    {
        runAnimationRight->setPosition(sf::Vector2f(playerShape.getPosition().x, runAnimationRight->getPosition().y));
        runAnimationLeft->setPosition(sf::Vector2f(playerShape.getPosition().x, runAnimationRight->getPosition().y));
        idleAnimationRight->setPosition(sf::Vector2f(playerShape.getPosition().x, runAnimationRight->getPosition().y));
        idleAnimationLeft->setPosition(sf::Vector2f(playerShape.getPosition().x, runAnimationRight->getPosition().y));
    }
    else
    {
        runAnimationRight->setPosition(playerShape.getPosition());
        runAnimationLeft->setPosition(playerShape.getPosition());
        idleAnimationRight->setPosition(playerShape.getPosition());
        idleAnimationLeft->setPosition(playerShape.getPosition());
    }
}

void Player::updateHealthBar(sf::RenderWindow& window, sf::View view)
{
    for(size_t i=0; i<hearthVector.size(); i++)
    {
        hearthVector[i].setPosition(view.getCenter() - sf::Vector2f(window.getSize().x/2.f - tempHearth.getSize().x*i - 10.f, window.getSize().y/2.f - 10.f));
        _pointsText.setPosition(hearthVector[0].getPosition() + sf::Vector2f(0, hearthVector[0].getSize().y));
    }

    if(invulnerableFlag)
    {
        if(invulnerableTimer>invulnerableCooldown)
        {
            invulnerableFlag = false;

            for(size_t i=0; i<hearthVector.size(); i++)
                hearthVector[i].setFillColor(sf::Color::White);
        }
        else
        {
            sf::Color tempColor = rand()%2 ? sf::Color::Black : sf::Color::White;

            for(size_t i=0; i<hearthVector.size(); i++)
                hearthVector[i].setFillColor(tempColor);
        }
    }

}

void Player::updatePoints(size_t newPoints)
{
    _pointsCounter = newPoints;

    std::stringstream ss;
    ss<<"Punkty: "<<_pointsCounter;
    _pointsText.setString(ss.str());
}

void Player::dealDamage(size_t damage, bool &gameover)
{
    if(currentHP == 0)
        gameover = true;

    if(!invulnerableFlag)
    {

        for(size_t i=0; i<damage; i++)
        {
            hearthVector.erase(hearthVector.end() - 1);
            currentHP--;
        }

        invulnerableFlag = true;
        invulnerableTimer = 0;
    }
}

void Player::updateShooting(sf::RenderWindow& window, sf::View view)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && canShoot())
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

void Player::updateEnemiesInteraction(std::vector<Enemy*> &enemiesVector, bool &gameover)
{
    for(size_t i=0; i<enemiesVector.size(); i++)
    {
        if(playerShape.getGlobalBounds().intersects(enemiesVector[i]->getGlobalBounds()))
            dealDamage(1, gameover);

        for(size_t j=0; j<bulletsVector.size(); j++)
            if(bulletsVector[j].bulletShape.getGlobalBounds().intersects(enemiesVector[i]->getGlobalBounds()))
            {
                if(enemiesVector[i]->getHP() > 1)
                    enemiesVector[i]->setHP(enemiesVector[i]->getHP() - 1);
                else
                {
                    delete enemiesVector[i];
                    enemiesVector.erase(enemiesVector.begin() + i);
                }

                bulletsVector.erase(bulletsVector.begin() + j);

            }
    }
}

void Player::updateCollectableInteraction(std::vector<Collectable*> &collectableVector)
{
    for(size_t i=0; i<collectableVector.size(); i++)
    {
        if(playerShape.getGlobalBounds().intersects(collectableVector[i]->getGlobalBounds()))
        {
            delete collectableVector[i];
            collectableVector.erase(collectableVector.begin() + i);

            updatePoints(_pointsCounter + 1);
        }
    }
}

void Player::updateWindowCollisions()
{
    sf::FloatRect playerBounds=playerShape.getGlobalBounds();

    if(playerBounds.top + playerBounds.height >= 1080)
    {
        playerShape.setPosition(playerBounds.left, 1080 - playerBounds.height);

        if(inSpace)
            inSpace=false;
    }
    if(playerBounds.top <= currentMapSize.y)
    {
        playerShape.setPosition(playerBounds.left, currentMapSize.y);
        velocity.y=0;
    }
    if(playerBounds.left <= 0)
        playerShape.setPosition(0, playerBounds.top);
    if(playerBounds.left + playerBounds.width >= currentMapSize.x)
        playerShape.setPosition(currentMapSize.x - playerBounds.width, playerBounds.top);
}

void Player::updatePlatformCollisions()
{


    sf::FloatRect playerBounds=playerShape.getGlobalBounds();
    collidingTop=false;

    for(size_t i=0;i<PlatformsManager::getSize();i++)
    {
        if(playerShape.getGlobalBounds().intersects(PlatformsManager::getPlatform(i).getGlobalBounds()))
        {
            sf::FloatRect wallBounds=PlatformsManager::getPlatform(i).getGlobalBounds();

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

    if(playerBounds.top + playerBounds.height<1080 && !collidingTop)
        inSpace=true;
}


void Player::update(sf::RenderWindow &window,sf::View view,bool &gameOver,std::vector<Enemy*> &enemiesVector, std::vector<Collectable*> &collectableVector)
{
    updateTime();
    updateInput();
    updateWindowCollisions();
    updateShooting(window,view);
    updateEnemiesInteraction(enemiesVector, gameOver);
    updateCollectableInteraction(collectableVector);
    updatePlatformCollisions();
    updateHealthBar(window, view);
}

void Player::renderHealthBar(sf::RenderTarget &window) const
{
    for(size_t i=0; i<hearthVector.size(); i++)
        window.draw(hearthVector[i]);
    window.draw(_pointsText);
}

void Player::render(sf::RenderTarget &window) const
{
    if(velocity.x > 0)
        runAnimationRight->render(window);
    else if(velocity.x < 0)
        runAnimationLeft->render(window);
    else
        if(previousDirection)
            idleAnimationRight->render(window);
        else
            idleAnimationLeft->render(window);

    for(size_t i=0; i<bulletsVector.size(); i++)
        window.draw(bulletsVector[i].bulletShape);

    renderHealthBar(window);
}

bool Player::canShoot() const
{
    return !_talks && shootTimer>shootCooldown;
}

void Player::deleteAnimations()
{
    delete runAnimationRight;
    delete runAnimationLeft;
    delete idleAnimationRight;
    delete idleAnimationLeft;
}

sf::Vector2f Player::getPosition()  const         {return playerShape.getPosition();       }
sf::Vector2f Player::getSize()    const           {return playerShape.getSize();           }
sf::FloatRect Player::getGlobalBounds() const     {return playerShape.getGlobalBounds();   }
void Player::Talks(bool state)                    {_talks = state;                         }
