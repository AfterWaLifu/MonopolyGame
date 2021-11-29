#include "game.h"
#include <stdlib.h>

Game::Game()
{
    for (int i = 0 ; i < 4 ; i++ ){
        players[i] = new Figure(i);
    }
    for (int i = 0 ; i < 36 ; i++ ){
        map[i] = new MapSquare();
    }
    settings = new Settings(0);

    currentPlayer = 0;
}

void Game::throwDices()
{
    int result = ( rand() % ( 6 * settings->diceCount ) ) + 1;
    this->diceResult = result;
}
