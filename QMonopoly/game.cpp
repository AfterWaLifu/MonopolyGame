#include "game.h"
#include <stdlib.h>

Game::Game()
{
    settings = new Settings(1);
    setUpMap();

    for (int i = 0 ; i < 4 ; i++ ){
        players[i] = new Figure(i, settings->startSumm);
    }
    for (int i = 0 ; i < 36 ; i++ ){
        map[i] = new MapSquare( "Шаурма №" + QString::number(i) , settings->ENTERPRISE );
    }

    currentPlayer = 0;
}

void Game::throwDices()
{
    int result = ( rand() % ( 6 * settings->diceCount ) ) + 1;
    this->diceResult = result;
}

void Game::setUpMap()
{
    map[0] = new MapSquare("Старт", settings->START);
    map[1] = new MapSquare();
    map[2] = new MapSquare();
    map[3] = new MapSquare();
    map[4] = new MapSquare();
    map[5] = new MapSquare("Налоговая", settings->TAXES);
    map[6] = new MapSquare("Тюрьма", settings->JAIL);
    map[7] = new MapSquare();
    map[8] = new MapSquare();
    map[9] = new MapSquare();
    map[10] = new MapSquare();
    map[11] = new MapSquare("Ж/д Вокзал", settings->TRAIN);
    map[12] = new MapSquare();
    map[13] = new MapSquare();
    map[14] = new MapSquare();
    map[15] = new MapSquare();
    map[16] = new MapSquare();
    map[17] = new MapSquare();
    map[18] = new MapSquare("Ж/д Вокзал", settings->TRAIN);
    map[19] = new MapSquare();
    map[20] = new MapSquare();
    map[21] = new MapSquare();
    map[22] = new MapSquare();
    map[23] = new MapSquare("Червоточина", settings->WORMHOLE);
    map[24] = new MapSquare("Тюрьма", settings->JAIL);
    map[25] = new MapSquare();
    map[26] = new MapSquare();
    map[27] = new MapSquare();
    map[28] = new MapSquare();
    map[29] = new MapSquare("Ж/д Вокзал", settings->TRAIN);
    map[30] = new MapSquare();
    map[31] = new MapSquare();
    map[32] = new MapSquare();
    map[33] = new MapSquare();
    map[34] = new MapSquare();
    map[35] = new MapSquare();
}
