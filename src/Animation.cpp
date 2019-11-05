#include "Animation.h"

 Animation::Animation(char *path,size_t numberOfFrames,sf::Vector2f sizeOfFrame,sf::Vector2f sizeOfPlayer,float cooldown,bool repeatFlag,bool backwards)
 {
    this->framesPic.loadFromFile(path);

    if(!backwards)
        for(size_t i=0;i<numberOfFrames;i++)
            this->frames.push_back(sf::IntRect(i*sizeOfFrame.x,0,sizeOfFrame.x,sizeOfFrame.y));
    else
        for(size_t i=0;i<numberOfFrames;i++)
            this->frames.push_back(sf::IntRect((i+1)*sizeOfFrame.x,0,-sizeOfFrame.x,sizeOfFrame.y));

    this->animation.setSize(sizeOfPlayer);
    this->animation.setTexture(&this->framesPic);
    this->animation.setTextureRect(this->frames[0]);

    this->speed=cooldown;
    this->timer=0;
    this->currentFrame=0;
    this->isEnabled=1;
    this->isRecurrent=repeatFlag;
 }

Animation::~Animation()
{
    //dtor
}

void Animation::setPosition(sf::Vector2f pos)
{
    this->animation.setPosition(pos);
}

void Animation::setScale(sf::Vector2f scale)
{
    this->animation.setScale(scale);
}

void Animation::render(sf::RenderTarget &window)
{
    window.draw(this->animation);
}

void Animation::update()
{
    this->timer+=clock.getElapsedTime().asSeconds();
    clock.restart();

    if(this->timer > this->speed)
    {
        this->timer=0;
        this->currentFrame++;

    }

    if(this->currentFrame >= this->frames.size())
    {
        if(this->isRecurrent)
            this->currentFrame=0;
        else
            this->isEnabled=0;
    }
    else
        this->animation.setTextureRect(this->frames[this->currentFrame]);
}

sf::Vector2f Animation::getPosition()
{
    return animation.getPosition();
}
