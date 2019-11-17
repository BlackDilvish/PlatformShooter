#include "Menu.h"

Menu::Menu(sf::Vector2u size)
{
    ///Main
    menuCanvas.setSize(sf::Vector2f(size));
    menuCanvas.setFillColor(sf::Color(0,0,0,100));

    resumeButton.setSize(sf::Vector2f(250.f,100.f));
    resumeButton.setPosition(sf::Vector2f(menuCanvas.getSize().x/2.f - resumeButton.getSize().x/2.f, menuCanvas.getSize().y/2.f - 2*resumeButton.getSize().y));

    optionsButton.setSize(resumeButton.getSize());
    optionsButton.setPosition(sf::Vector2f(resumeButton.getPosition().x, resumeButton.getPosition().y + 2*optionsButton.getSize().y));

    exitButton.setSize(resumeButton.getSize());
    exitButton.setPosition(sf::Vector2f(resumeButton.getPosition().x, optionsButton.getPosition().y + 2*exitButton.getSize().y));

    ///Gameover
    gameoverCanvas.setSize(sf::Vector2f(size));
    gameoverCanvas.setFillColor(sf::Color(255, 0, 0, 150));


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

    gameoverText.setFont(font);
    gameoverText.setPosition(resumeButton.getPosition());
    gameoverText.setCharacterSize(63);
    gameoverText.setFillColor(sf::Color::Black);
    gameoverText.setString("Nie zyjesz...");
}

void Menu::update(const sf::RenderWindow& window, bool& gameover)
{
    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window)) + dMove;

    switch(currentState)
    {
    case Menu::main:
        if(resumeButton.getGlobalBounds().contains(mousePos))
        {
            resumeButton.setFillColor(sf::Color::Green);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                open(dMove);
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
                gameover = true;
        }
        else
        {
            resumeButton.setFillColor(sf::Color::White);
            optionsButton.setFillColor(sf::Color::White);
            exitButton.setFillColor(sf::Color::White);
        }
        break;
    case Menu::gameOver:
        if(exitButton.getGlobalBounds().contains(mousePos))
        {
            exitButton.setFillColor(sf::Color::Red);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                gameover = true;
        }
        else
        {
            exitButton.setFillColor(sf::Color::White);
        }
        break;
    default:
        break;
    }
}

void Menu::render(sf::RenderTarget& window) const
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
    case Menu::gameOver:
        window.draw(gameoverCanvas);
        window.draw(exitButton);

        window.draw(gameoverText);
        window.draw(exitText);
    default:
        break;
    }

}

size_t Menu::getStatus() const
{
    return currentState;
}

void Menu::setStatus(size_t newStatus)
{
    currentState = newStatus;
}

void Menu::setPosition(sf::Vector2f deltaMove)
{
    menuCanvas.move(deltaMove);
    gameoverCanvas.move(deltaMove);

    resumeButton.move(deltaMove);
    optionsButton.move(deltaMove);
    exitButton.move(deltaMove);

    resumeText.move(deltaMove);
    optionsText.move(deltaMove);
    exitText.move(deltaMove);
    gameoverText.move(deltaMove);
}

void Menu::open(sf::Vector2f deltaMove)
{
    dMove = deltaMove;

    if(currentState == Menu::hidden)
    {
        setPosition(deltaMove);
        currentState = Menu::main;
    }
    else
    {
        setPosition(-deltaMove);
        currentState = Menu::hidden;
    }
}

void Menu::openGameover(sf::Vector2f deltaMove)
{
    dMove = deltaMove;

    setPosition(deltaMove);
    currentState = Menu::gameOver;
}
