#include"Game.h"

int main()
{
    Game game;

    while(game.isPlaying())
    {
        game.update();
        game.render();
    }

    return 0;
}
