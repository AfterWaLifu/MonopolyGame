#pragma once

#include <QString>

class MapSquare
{
public:
    MapSquare( QString n , int tp , int cst = -1 );

    QString name;
    int cost;
    int toSell;
    int toEarn;

    int type;

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

