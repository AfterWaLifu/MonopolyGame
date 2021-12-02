#include "game.h"
#include <stdlib.h>

Game::Game()
{
    settings = new Settings(1);

    for (int i = 0 ; i < 4 ; i++ ){
        players[i] = new Figure(i, settings->startSumm);
    }
    setUpMap();

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
    map[1] = new MapSquare("", settings->ENTERPRISE);
    map[2] = new MapSquare("", settings->ENTERPRISE);
    map[3] = new MapSquare("", settings->ENTERPRISE);
    map[4] = new MapSquare("", settings->ENTERPRISE);
    map[5] = new MapSquare("Налоговая", settings->TAXES);
    map[6] = new MapSquare("Тюрьма", settings->JAIL);
    map[7] = new MapSquare("", settings->ENTERPRISE);
    map[8] = new MapSquare("", settings->ENTERPRISE);
    map[9] = new MapSquare("", settings->ENTERPRISE);
    map[10] = new MapSquare("", settings->ENTERPRISE);
    map[11] = new MapSquare("Ж/д Вокзал", settings->TRAIN);
    map[12] = new MapSquare("Шаурма/курица", settings->ENTERPRISE);
    map[13] = new MapSquare("Шаурма/свинина", settings->ENTERPRISE);
    map[14] = new MapSquare("Фондовая биржа", settings->STOCK);
    map[15] = new MapSquare("Общественный\nбанк", settings->SOCIAL_BANK);
    map[16] = new MapSquare("", settings->ENTERPRISE);
    map[17] = new MapSquare("", settings->ENTERPRISE);
    map[18] = new MapSquare("Ж/д Вокзал", settings->TRAIN);
    map[19] = new MapSquare("", settings->ENTERPRISE);
    map[20] = new MapSquare("", settings->ENTERPRISE);
    map[21] = new MapSquare("", settings->ENTERPRISE);
    map[22] = new MapSquare("", settings->ENTERPRISE);
    map[23] = new MapSquare("Червоточина", settings->WORMHOLE);
    map[24] = new MapSquare("Тюрьма", settings->JAIL);
    map[25] = new MapSquare("АвтоГЛАЗ", settings->ENTERPRISE);
    map[26] = new MapSquare("АвтоНАСТ", settings->ENTERPRISE);
    map[27] = new MapSquare("АвтоКАСТ", settings->ENTERPRISE);
    map[28] = new MapSquare("АвтоМАСТ", settings->ENTERPRISE);
    map[29] = new MapSquare("Ж/д Вокзал", settings->TRAIN);
    map[30] = new MapSquare("Xednay", settings->ENTERPRISE);
    map[31] = new MapSquare("ThreeStars", settings->ENTERPRISE);
    map[32] = new MapSquare("Революция", settings->LENIN);
    map[33] = new MapSquare("Общественная\nказна", settings->SOCIAL_MONEY);
    map[34] = new MapSquare("XiaNotYou", settings->ENTERPRISE);
    map[35] = new MapSquare("Pear", settings->ENTERPRISE);
}
