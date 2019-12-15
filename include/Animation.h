#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


class Animation
{
    public:
        Animation(char *path,size_t numberOfFrames,sf::Vector2f sizeOfFrame,sf::Vector2f sizeOfPlayer,float cooldown,bool repeatFlag,bool backwards);
        Animation(const sf::Texture& texture,size_t numberOfFrames,sf::Vector2f sizeOfFrame,sf::Vector2f sizeOfPlayer,float cooldown,bool repeatFlag,bool backwards);

        ~Animation() = default;

        void update();
        void setPosition(sf::Vector2f pos);
        void setScale(sf::Vector2f scale);
        void render(sf::RenderTarget &window);
        sf::Vector2f getPosition();

        bool isEnabled;
        bool isRecurrent;

    protected:

    private:
        std::vector<sf::IntRect> frames;
        sf::RectangleShape animation;
        sf::Texture framesPic;

        sf::Clock clock;
        float speed;
        float timer;
        size_t currentFrame;
};

#endif // ANIMATION_H
