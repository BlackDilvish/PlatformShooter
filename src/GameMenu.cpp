#include "GameMenu.h"

GameMenu::GameMenu(sf::Vector2u size)
{
    buttonSize(sf::Vector2f(250.f,100.f));

    initCanvases(size);
    initButtons();

    setStatus(GameMenu::title);
}

GameMenu::~GameMenu()
{
    deleteCanvases();
    deleteButtons();
    deleteFont();
}

void GameMenu::initCanvases(sf::Vector2u size)
{
    menuCanvas      = new Canvas(size, sf::Color(0,0,0,100), getFont(), "Menu glowne");
    gameoverCanvas  = new Canvas(size, sf::Color(255, 0, 0, 150), getFont(), "Nie zyjesz...", sf::Color::Black);

    _titleCanvas    = new Canvas(size, "Assets/Images/titleMenu.png");
}

void GameMenu::initButtons()
{
    resumeButton   = new Button(buttonSize(), menuCanvas->getSize()/2.f - sf::Vector2f(buttonSize().x/2.f, buttonSize().y*2.f), getFont(),(char*) "Resume", sf::Color::Green);
    optionsButton  = new Button(buttonSize(), resumeButton->getPosition() + sf::Vector2f(0, buttonSize().y*2.f), getFont(),(char*) "Options", sf::Color::Blue);
    exitButton     = new Button(buttonSize(), optionsButton->getPosition() + sf::Vector2f(0, buttonSize().y*2.f), getFont(),(char*) "Exit", sf::Color::Red);

    _restartButton = new Button(buttonSize(), resumeButton->getPosition(), getFont(), "Restart", sf::Color::Blue);

    _newGameButton = new Button(buttonSize(), _titleCanvas->getSize()/6.f, getFont(), "New Game", sf::Color::Red, 42);
    _optionsButton = new Button(buttonSize(), _titleCanvas->getSize()/6.f + sf::Vector2f(0, 2*buttonSize().y), getFont(), "Options", sf::Color::Red, 42);
    _exitButton    = new Button(buttonSize(), _titleCanvas->getSize()/6.f + sf::Vector2f(0, 4*buttonSize().y), getFont(), "Exit", sf::Color::Red, 42);

}

void GameMenu::update(const sf::RenderWindow& window, bool& gameover)
{
    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window)) + dMove;

    switch(getStatus())
    {
    case GameMenu::main:
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
                std::cout<<"Options\n";
        }
        else if(exitButton->hovers(mousePos))
        {
            exitButton->Light();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                setStatus(GameMenu::title);
        }
        else
        {
            resumeButton->Dark();
            optionsButton->Dark();
            exitButton->Dark();
        }
        break;
    case GameMenu::gameOver:
        if(_restartButton->hovers(mousePos))
        {
            _restartButton->Light();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                setStatus(GameMenu::restart);
        }
        else if(exitButton->hovers(mousePos))
        {
            exitButton->Light();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                setStatus(GameMenu::title);
        }
        else
        {
            _restartButton->Dark();
            exitButton->Dark();
        }
        break;
    case GameMenu::title:
        if(_newGameButton->hovers(mousePos))
        {
            _newGameButton->Light();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                setStatus(GameMenu::newGame);
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

void GameMenu::render(sf::RenderTarget& window) const
{
    switch(getStatus())
    {
    case GameMenu::main:
        menuCanvas->render(window);

        resumeButton->render(window);
        optionsButton->render(window);
        exitButton->render(window);
        break;
    case GameMenu::gameOver:
        gameoverCanvas->render(window);

        _restartButton->render(window);
        exitButton->render(window);
        break;
    case GameMenu::title:
        _titleCanvas->render(window);

        _newGameButton->render(window);
        _optionsButton->render(window);
        _exitButton->render(window);
        break;
    default:
        break;
    }

}

void GameMenu::setPosition(sf::Vector2f deltaMove)
{
    menuCanvas->move(deltaMove);
    gameoverCanvas->move(deltaMove);
    _titleCanvas->move(deltaMove);

    resumeButton->move(deltaMove);
    optionsButton->move(deltaMove);
    exitButton->move(deltaMove);
    _restartButton->move(deltaMove);

    _newGameButton->move(deltaMove);
    _optionsButton->move(deltaMove);
    _exitButton->move(deltaMove);
}

void GameMenu::open(sf::Vector2f deltaMove)
{
    dMove = deltaMove;

    if(getStatus() == GameMenu::hidden)
    {
        setPosition(deltaMove);
        setStatus(GameMenu::main);
    }
    else
    {
        setPosition(-deltaMove);
        setStatus(GameMenu::hidden);
    }
}

void GameMenu::openGameover(sf::Vector2f deltaMove)
{
    dMove = deltaMove;

    setPosition(deltaMove);
    setStatus(GameMenu::gameOver);
}

void GameMenu::deleteCanvases()
{
    delete menuCanvas;
    delete gameoverCanvas;
    delete _titleCanvas;
}

void GameMenu::deleteButtons()
{
    delete resumeButton;
    delete optionsButton;
    delete exitButton;
    delete _restartButton;

    delete _newGameButton;
    delete _optionsButton;
    delete _exitButton;
}
