#ifndef PLATFORMSMANAGER_H
#define PLATFORMSMANAGER_H

#include<SFML/Graphics.hpp>
#include<vector>

class PlatformsManager
{
    public:
        PlatformsManager();
        virtual ~PlatformsManager();

        void addPlatform(sf::Vector2f size, sf::Vector2f pos);
        void render(sf::RenderTarget &window);

        size_t getSize();
        sf::RectangleShape& operator[](size_t id);
        void destroyPlatform(size_t id);

    protected:

    private:
        std::vector<sf::RectangleShape> platformsVector;


};

#endif // PLATFORMSMANAGER_H
