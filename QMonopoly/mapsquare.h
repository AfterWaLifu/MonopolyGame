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
};

