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

    // МЕТОДЫ

    int throwDices();
};

