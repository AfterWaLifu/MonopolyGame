#include "mapsquare.h"


MapSquare::MapSquare(QString n, int tp, int cst)
{
    name = n;
    type = tp;
    cost = cst;
    toSell = cost / 5 * 4 ;
    toEarn = cost / 5 ;
    owner = -1;
}
