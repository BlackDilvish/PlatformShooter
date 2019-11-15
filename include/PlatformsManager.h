#ifndef PLATFORMSMANAGER_H
#define PLATFORMSMANAGER_H

#include<SFML/Graphics.hpp>
#include<vector>

class PlatformsManager
{
    public:
        PlatformsManager();
        virtual ~PlatformsManager();

        static void addPlatform(sf::Vector2f size, sf::Vector2f pos);
        static void addPlatform(float *platformParams);
        static void render(sf::RenderTarget &window);

        static size_t getSize();
        static sf::RectangleShape& getPlatform(size_t id);
        static void destroyPlatform(size_t id);
        static void clear();

    protected:

    private:
        static std::vector<sf::RectangleShape> platformsVector;


};

#endif // PLATFORMSMANAGER_H
