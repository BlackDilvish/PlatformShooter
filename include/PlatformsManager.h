#ifndef PLATFORMSMANAGER_H
#define PLATFORMSMANAGER_H

#include<SFML/Graphics.hpp>
#include<vector>

class PlatformsManager
{
    public:
        static void addPlatform(sf::Vector2f size, sf::Vector2f pos);
        static void addPlatform(float *platformParams, int platformType);
        static void render(sf::RenderTarget &window);

        static void initTextures();
        static size_t getSize();
        static sf::RectangleShape& getPlatform(size_t id);
        static void destroyPlatform(size_t id);
        static void clear();

    private:
        PlatformsManager() = default;
        virtual ~PlatformsManager() = default;

        static std::vector<sf::RectangleShape> platformsVector;
        static sf::Texture platformTextures[3];

};

#endif // PLATFORMSMANAGER_H
