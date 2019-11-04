#include "Menu.h"

Menu::Menu(sf::Vector2u size)
{
    menuCanvas.setSize(sf::Vector2f(size));
    menuCanvas.setFillColor(sf::Color(180,180,180,100));

    resumeButton.setSize(sf::Vector2f(250.f,100.f));
    resumeButton.setPosition(sf::Vector2f(menuCanvas.getSize().x/2.f - resumeButton.getSize().x/2.f, menuCanvas.getSize().y/2.f - 2*resumeButton.getSize().y));

    optionsButton.setSize(resumeButton.getSize());
    optionsButton.setPosition(sf::Vector2f(resumeButton.getPosition().x, resumeButton.getPosition().y + 2*optionsButton.getSize().y));

    exitButton.setSize(resumeButton.getSize());
    exitButton.setPosition(sf::Vector2f(resumeButton.getPosition().x, optionsButton.getPosition().y + 2*exitButton.getSize().y));

    initText();

    currentState = Menu::hidden;
}

Menu::~Menu()
{
    //dtor
}

void Menu::initText()
{
    font.loadFromFile("Assets/Fonts/Lato.ttf");

    resumeText.setFont(font);
    resumeText.setPosition(resumeButton.getPosition());
    resumeText.setCharacterSize(63);
    resumeText.setString("Resume");

    optionsText.setFont(font);
    optionsText.setPosition(optionsButton.getPosition());
    optionsText.setCharacterSize(63);
    optionsText.setString("Opcje");

    exitText.setFont(font);
    exitText.setPosition(exitButton.getPosition());
    exitText.setCharacterSize(63);
    exitText.setString("Exit");
}

void Menu::update(const sf::RenderWindow& window, bool& gameover)
{
    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

    switch(currentState)
    {
    case Menu::main:
        if(resumeButton.getGlobalBounds().contains(mousePos))
        {
            resumeButton.setFillColor(sf::Color::Green);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                currentState=hidden;
        }
        else if(optionsButton.getGlobalBounds().contains(mousePos))
        {
            optionsButton.setFillColor(sf::Color::Blue);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                std::cout<<"Jakies opcje\n";
        }
        else if(exitButton.getGlobalBounds().contains(mousePos))
        {
            exitButton.setFillColor(sf::Color::Red);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                gameover = 1;
        }
        else
        {
            resumeButton.setFillColor(sf::Color::White);
            optionsButton.setFillColor(sf::Color::White);
            exitButton.setFillColor(sf::Color::White);
        }
        break;
    default:
        break;
    }
}

void Menu::render(sf::RenderTarget& window)
{
    switch(currentState)
    {
    case Menu::main:
        window.draw(menuCanvas);
        window.draw(resumeButton);
        window.draw(optionsButton);
        window.draw(exitButton);

        window.draw(resumeText);
        window.draw(optionsText);
        window.draw(exitText);
        break;
    default:
        break;
    }

}

size_t Menu::getStatus()
{
    return currentState;
}

void Menu::setStatus(size_t newStatus)
{
    currentState = newStatus;
}
