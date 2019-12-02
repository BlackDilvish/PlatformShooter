#include "Npc.h"

Npc::Npc(sf::Vector2f Position,const sf::Vector2f size)
{
    shape.setSize(size);
    shape.setPosition(Position);
    shape.setFillColor(sf::Color::Green);

    interactionIcon.icon.setSize(sf::Vector2f(30.f, 30.f));
    interactionIcon.icon.setPosition(Position - sf::Vector2f(0, 50.f));
    interactionIcon.icon.setFillColor(sf::Color::Yellow);
    interactionIcon.isDisplayed = false;
    interactionIcon.useLimit = 0;

    dialogIcon.icon.setSize(sf::Vector2f(30.f, 30.f));
    dialogIcon.icon.setPosition(Position - sf::Vector2f(-60.f, 50.f));
    dialogIcon.icon.setFillColor(sf::Color::Yellow);
    dialogIcon.isDisplayed = false;
    dialogIcon.useLimit = 0;


    MessageBox.canvas.setPosition(Position - sf::Vector2f(0, 500));
    MessageBox.canvas.setSize(sf::Vector2f(500.f, 300.f));
    MessageBox.canvas.setFillColor(sf::Color::Red);
    MessageBox.isDisplayed = false;

    DialogBox.canvas.setPosition(MessageBox.canvas.getPosition());
    DialogBox.canvas.setSize(MessageBox.canvas.getSize());
    DialogBox.canvas.setFillColor(MessageBox.canvas.getFillColor());
    DialogBox.isDisplayed = false;
    DialogBox.nextPage.setSize(sf::Vector2f(30.f, 30.f));
    DialogBox.nextPage.setFillColor(sf::Color::Yellow);
    DialogBox.nextPage.setPosition(DialogBox.canvas.getPosition() + DialogBox.canvas.getSize() - DialogBox.nextPage.getSize());
    DialogBox.useLimit = 0;
}

Npc::~Npc()
{

}

void Npc::setAnimation(char* path,size_t numberOfFrames,sf::Vector2f sizeOfFrame,float cooldown)
{
    idleAnimation = new Animation(path, numberOfFrames, sizeOfFrame, shape.getSize(), cooldown, true, false);
    idleAnimation->setPosition(shape.getPosition());
}

void Npc::initText(sf::Font& font, std::vector<std::string>& npcMessages)
{
    MessageBox.messageText.setFont(font);
    MessageBox.messageText.setPosition(MessageBox.canvas.getPosition());
    MessageBox.messageText.setString("");

    DialogBox.messageText.setFont(font);
    DialogBox.messageText.setPosition(DialogBox.canvas.getPosition());
    DialogBox.messageText.setString("");

    numberOfPages = npcMessages.size();
    currentPage = 0;
    for(size_t i=0; i<numberOfPages; i++)
        messegesVector.push_back(npcMessages[i]);

}

void Npc::popMessageBox(std::string message="")
{
    MessageBox.messageText.setString(message);
    MessageBox.isDisplayed = true;
}

void Npc::DefaultInfo(const std::string& info)
{
    _defaultInfo = info;
}

void Npc::popDialogBox()
{
    currentPage = 0;
    DialogBox.useLimit = 0;

    DialogBox.messageText.setString(messegesVector[currentPage]);
    DialogBox.isDisplayed = true;
}

void Npc::updateInteractionIcons(sf::Vector2f& mousePos)
{
    if(interactionIcon.icon.getGlobalBounds().contains(mousePos))
    {
        interactionIcon.icon.setFillColor(sf::Color::Red);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && interactionIcon.useLimit>20 && !DialogBox.isDisplayed)
        {
            interactionIcon.useLimit = 0;

            if(!MessageBox.isDisplayed)
                popMessageBox(_defaultInfo);
            else
                MessageBox.isDisplayed = false;
        }
    }
    else if(dialogIcon.icon.getGlobalBounds().contains(mousePos))
    {
        dialogIcon.icon.setFillColor(sf::Color::Red);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && dialogIcon.useLimit>20 && !MessageBox.isDisplayed)
        {
            dialogIcon.useLimit = 0;

            if(!DialogBox.isDisplayed)
                popDialogBox();
            else
                DialogBox.isDisplayed = false;
        }
    }
    else
    {
        interactionIcon.icon.setFillColor(sf::Color::Yellow);
        dialogIcon.icon.setFillColor(sf::Color::Yellow);
    }

    if(interactionIcon.useLimit < 60)
        interactionIcon.useLimit += 1;
    if(dialogIcon.useLimit < 60)
        dialogIcon.useLimit += 1;

}

void Npc::updateDialogBox(sf::Vector2f& mousePos)
{
    if(DialogBox.isDisplayed)
    {
        if(DialogBox.nextPage.getGlobalBounds().contains(mousePos))
        {
            DialogBox.nextPage.setFillColor(sf::Color::Blue);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && DialogBox.useLimit>30)
            {
                if(currentPage < numberOfPages - 1)
                {
                    DialogBox.useLimit = 0;

                    DialogBox.messageText.setString(messegesVector[++currentPage]);
                }
                else
                    DialogBox.isDisplayed = false;
            }
        }
        else
            DialogBox.nextPage.setFillColor(sf::Color::Yellow);
    }

    if(DialogBox.useLimit <= 30)
        DialogBox.useLimit += 1;
}

void Npc::updateAnimations()
{
    idleAnimation->update();
}

void Npc::update(sf::RenderWindow& window, Player& player, sf::Vector2f& deltaMove)
{
    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window)) + deltaMove;

    if(shape.getGlobalBounds().intersects(player.getGlobalBounds()))
    {
        if(!interactionIcon.isDisplayed)
        {
            player.Talks(true);
            interactionIcon.isDisplayed = true;
            dialogIcon.isDisplayed = true;
        }
    }
    else
        updateAnimations();

    if(!shape.getGlobalBounds().intersects(player.getGlobalBounds()) && interactionIcon.isDisplayed)
    {
        player.Talks(false);
        interactionIcon.isDisplayed = false;
        dialogIcon.isDisplayed = false;
        MessageBox.isDisplayed =false;
        DialogBox.isDisplayed = false;
    }

    updateInteractionIcons(mousePos);
    updateDialogBox(mousePos);

}

void Npc::renderAnimations(sf::RenderTarget& window)
{
    idleAnimation->render(window);
}

void Npc::render(sf::RenderTarget& window)
{
    renderAnimations(window);

    if(interactionIcon.isDisplayed)
        window.draw(interactionIcon.icon);
    if(dialogIcon.isDisplayed)
        window.draw(dialogIcon.icon);

    if(MessageBox.isDisplayed)
    {
        window.draw(MessageBox.canvas);
        window.draw(MessageBox.messageText);
    }

    if(DialogBox.isDisplayed)
    {
        window.draw(DialogBox.canvas);
        window.draw(DialogBox.messageText);
        window.draw(DialogBox.nextPage);
    }
}

void Npc::freeAnimation()
{
    delete idleAnimation;
}
