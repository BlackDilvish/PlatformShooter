#include "Npc.h"

Npc::Npc(sf::Vector2f Position,const sf::Vector2f size)
{
    font.loadFromFile("Assets/Fonts/Lato.ttf");

    shape.setSize(size);
    shape.setPosition(Position);
    shape.setFillColor(sf::Color::Green);

    interactionIcon.icon.setSize(sf::Vector2f(30.f, 30.f));
    interactionIcon.icon.setPosition(Position - sf::Vector2f(0, 50.f));
    interactionIcon.icon.setFillColor(sf::Color::Yellow);
    interactionIcon.isDisplayed = false;

    MessageBox.canvas.setPosition(Position - sf::Vector2f(0, 500));
    MessageBox.canvas.setSize(sf::Vector2f(500.f, 300.f));
    MessageBox.canvas.setFillColor(sf::Color::Red);

    MessageBox.messageText.setFont(font);
    MessageBox.messageText.setPosition(MessageBox.canvas.getPosition());
    MessageBox.isDisplayed = false;
}

Npc::~Npc()
{

}

void Npc::popMessageBox(std::string message="")
{
    MessageBox.messageText.setString(message);
    MessageBox.isDisplayed = true;
}

void Npc::update(Player& player)
{
    if(shape.getGlobalBounds().intersects(player.getGlobalBounds()) && !interactionIcon.isDisplayed)
        interactionIcon.isDisplayed = true;

    if(!shape.getGlobalBounds().intersects(player.getGlobalBounds()) && interactionIcon.isDisplayed)
        interactionIcon.isDisplayed = false;
}

void Npc::render(sf::RenderTarget& window)
{
    window.draw(shape);

    if(interactionIcon.isDisplayed)
        window.draw(interactionIcon.icon);
}
