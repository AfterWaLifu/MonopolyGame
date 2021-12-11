#pragma once

#include "mapsquare.h"
#include "figure.h"
#include "settings.h"

class Game
{
public:
    Game();

    // ПЕРЕМЕШКИ

    MapSquare *map[36];
    Figure *players[4];
    Settings *settings;

    int currentPlayer;
    int diceResult;

    int socialMoney;
    int skippingPlayers[4];

    // МЕТОДЫ

    void throwDices();
    void setUpMap();
};

