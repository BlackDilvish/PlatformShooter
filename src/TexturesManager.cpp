#include "TexturesManager.h"

void TexturesManager::LoadTextures()
{
    goblinTexture.loadFromFile("Assets/Images/GoblinWalk.png");
    orcTexture.loadFromFile("Assets/Images/OrcWalk.png");
    coinTexture.loadFromFile("Assets/Images/Coin.png");
    blacksmithTexture.loadFromFile("Assets/Images/blacksmithIdle.png");
    magicMissileTexture.loadFromFile("Assets/Images/MagicMissile1.png");
}

sf::Texture TexturesManager::goblinTexture;
sf::Texture TexturesManager::orcTexture;
sf::Texture TexturesManager::coinTexture;
sf::Texture TexturesManager::blacksmithTexture;
sf::Texture TexturesManager::magicMissileTexture;
