#ifndef EDITORITEM_H
#define EDITORITEM_H

#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>

class EditorItem
{
    public:
        EditorItem(sf::Vector2f size, sf::Color color, size_t id);
        EditorItem(sf::Vector2f size, const std::string& texturePath, size_t id);
        EditorItem(const EditorItem& item, size_t id);
        virtual ~EditorItem() = default;

        void Render(sf::RenderTarget& window);

        ///Getters
        sf::Vector2f getPosition();
        sf::Vector2f getSize() const;
        int getPlatform();
        sf::FloatRect getGlobalBounds();
        size_t Id();

        ///Setters
        void setPosition(sf::Vector2f position);
        void Enlarge();
        void setPlatform(int value);
        void move(sf::Vector2f dist);

        void ResetItem();
        static void ResetPlatformCounter();

        bool IsPlatform() const;
        bool IsEnemy() const;
        bool IsPlayer() const;

    private:

        size_t _id;
        int _assignedPlatform;
        sf::Vector2f _defaultSize;

        sf::RectangleShape _itemShape;
        sf::Texture _itemTexture;

        static int _platformCounter;
};

#endif // EDITORITEM_H
