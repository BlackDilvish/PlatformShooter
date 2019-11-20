#include "Menu.h"

Menu::Menu(sf::Vector2u size)
{
    font.loadFromFile("Assets/Fonts/Lato.ttf");
    buttonSize = sf::Vector2f(250.f,100.f);

    initCanvases(size);
    initButtons();

    currentState = Menu::hidden;
}

Menu::~Menu()
{
    deleteCanvases();
    deleteButtons();
}

void Menu::initCanvases(sf::Vector2u size)
{
    menuCanvas = new Canvas(size, sf::Color(0,0,0,100), font, "Menu glowne");
    gameoverCanvas = new Canvas(size, sf::Color(255, 0, 0, 150), font, "Nie zyjesz...", sf::Color::Black);
}

void Menu::initButtons()
{
    resumeButton = new Button(buttonSize, menuCanvas->getSize()/2.f - sf::Vector2f(buttonSize.x/2.f, buttonSize.y*2.f), font, "Resume", sf::Color::Green);
    optionsButton = new Button(buttonSize, resumeButton->getPosition() + sf::Vector2f(0, buttonSize.y*2.f), font, "Options", sf::Color::Blue);
    exitButton = new Button(buttonSize, optionsButton->getPosition() + sf::Vector2f(0, buttonSize.y*2.f), font, "Exit", sf::Color::Red);
}

void Menu::update(const sf::RenderWindow& window, bool& gameover)
{
    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window)) + dMove;

    switch(currentState)
    {
    case Menu::main:
        if(resumeButton->hovers(mousePos))
        {
            resumeButton->Light();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                open(dMove);
        }
        else if(optionsButton->hovers(mousePos))
        {
            optionsButton->Light();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                std::cout<<"Jakies opcje\n";
        }
        else if(exitButton->hovers(mousePos))
        {
            exitButton->Light();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                gameover = true;
        }
        else
        {
            resumeButton->Dark();
            optionsButton->Dark();
            exitButton->Dark();
        }
        break;
    case Menu::gameOver:
        if(exitButton->hovers(mousePos))
        {
            exitButton->Light();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                gameover = true;
        }
        else
        {
            exitButton->Dark();
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
        menuCanvas->render(window);

        resumeButton->render(window);
        optionsButton->render(window);
        exitButton->render(window);
        break;
    case Menu::gameOver:
        gameoverCanvas->render(window);

        exitButton->render(window);
        break;
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
    menuCanvas->move(deltaMove);
    gameoverCanvas->move(deltaMove);

    resumeButton->move(deltaMove);
    optionsButton->move(deltaMove);
    exitButton->move(deltaMove);
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

void Menu::deleteCanvases()
{
    delete menuCanvas;
    delete gameoverCanvas;
}

void Menu::deleteButtons()
{
    delete resumeButton;
    delete optionsButton;
    delete exitButton;
}
