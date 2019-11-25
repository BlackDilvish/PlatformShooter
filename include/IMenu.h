#ifndef IMENU_H
#define IMENU_H

#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>

class IMenu
{
    public:
        IMenu();

        virtual void update(const sf::RenderWindow& window, bool& gameover) = 0;
        virtual void render(sf::RenderTarget& window) const = 0;

        size_t getStatus() const;
        void setStatus(size_t newStatus);

    protected:
        virtual void initCanvases(sf::Vector2u size) = 0;
        virtual void initButtons() = 0;

        virtual void deleteCanvases() = 0;
        virtual void deleteButtons() = 0;

        sf::Font& getFont() const;
        void setFont(std::string path);
        void deleteFont();

        const sf::Vector2f& buttonSize();
        void buttonSize(sf::Vector2f size);

    private:
        size_t _status;
        sf::Font *_font;

        sf::Vector2f _buttonSize;
};

#endif // MENU_H
