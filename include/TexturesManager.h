#ifndef TEXTURESMANAGER_H
#define TEXTURESMANAGER_H

#include<SFML/Graphics.hpp>

class TexturesManager
{
    public:
        static void LoadTextures();

        ///Textures

            ///Enemies
            static sf::Texture goblinTexture;
            static sf::Texture orcTexture;

            ///Npc
            static sf::Texture blacksmithTexture;

            ///Collect
            static sf::Texture coinTexture;


    private:
        TexturesManager();
        ~TexturesManager();
};

#endif // TEXTURESMANAGER_H
