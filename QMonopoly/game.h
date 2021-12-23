#pragma once

#include "mapsquare.h"
#include "figure.h"
#include "settings.h"

class Game
{
public:
    Game(int plCnt);

    MapSquare *map[36];
    Figure *players[4];
    Settings *settings;

    int playersCount;
    int currentPlayer;
    int diceResult;

    int socialMoney;
    int skippingPlayers[4];
    bool toCheckOrNotToCheck = true;

    // МЕТОДЫ

    void throwDices();
    void setUpMap();
};

