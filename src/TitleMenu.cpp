#include "TitleMenu.h"

TitleMenu::TitleMenu(sf::Vector2u size)
{
    buttonSize(sf::Vector2f(200.f, 100.f));

    initCanvases(size);
    initButtons();

    setStatus(TitleMenu::main);
}

TitleMenu::~TitleMenu()
{
    deleteButtons();
    deleteCanvases();
    deleteFont();
}

void TitleMenu::initCanvases(sf::Vector2u size)
{
    _mainCanvas = new Canvas(size, "Assets/Images/titleMenu.png");
}

void TitleMenu::initButtons()
{
    _newGameButton = new Button(buttonSize(), _mainCanvas->getSize()/6.f, getFont(), "New Game", sf::Color::Red, 42);
    _optionsButton = new Button(buttonSize(), _mainCanvas->getSize()/6.f + sf::Vector2f(0, 2*buttonSize().y), getFont(), "Options", sf::Color::Red, 42);
    _exitButton    = new Button(buttonSize(), _mainCanvas->getSize()/6.f + sf::Vector2f(0, 4*buttonSize().y), getFont(), "Exit", sf::Color::Red, 42);
}

void TitleMenu::update(const sf::RenderWindow& window, bool& gameover)
{
    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

    switch(getStatus())
    {
    case TitleMenu::main:
        if(_newGameButton->hovers(mousePos))
        {
            _newGameButton->Light();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                setStatus(TitleMenu::newGame);
        }
        else if(_optionsButton->hovers(mousePos))
        {
            _optionsButton->Light();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                std::cout<<"Wejdz w opcje\n";
        }
        else if(_exitButton->hovers(mousePos))
        {

            _exitButton->Light();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                gameover = true;
        }
        else
        {
            _newGameButton->Dark();
            _optionsButton->Dark();
            _exitButton->Dark();
        }
        break;
    default:
        break;
    }
}

void TitleMenu::render(sf::RenderTarget& window) const
{
    switch(getStatus())
    {
    case TitleMenu::main:
        _mainCanvas->render(window);

        _newGameButton->render(window);
        _optionsButton->render(window);
        _exitButton->render(window);
        break;
    default:
        break;
    }

}

void TitleMenu::deleteCanvases()
{
    delete _mainCanvas;
}

void TitleMenu::deleteButtons()
{
    delete _newGameButton;
    delete _optionsButton;
    delete _exitButton;
}

