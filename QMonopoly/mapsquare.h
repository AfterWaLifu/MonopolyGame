#pragma once

class MapSquare
{
public:
    MapSquare();

    const char* name;
    int Cost;
    int toSell;
    int toEarn;

    int type;

    int specialNum;

    enum TYPES {
        START           = 0,
        ENTERPRISE,
        NOTHING,

        JAIL            = 10,
        TRAIN,
        TAXES,
        WORMHOLE,
        SOCIAL_MONEY,
        SOCIAL_BANK,
        LENIN,
        STOCK,

        ONE_MORE_TIME   = 50,
        PENALTY,
        PLUS_ONE,
        PLUS_TWO,
        PLUS_THREE,
        MINUS_SIX,
        PLUS_MONEY,
        MINUS_CONSTMONEY,
        MINUS_LARGEST_MONEY,
        MOVE_SKIP
    };
};

