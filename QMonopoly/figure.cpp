#include "figure.h"

Figure::Figure(int id, int startMoney)
{
    this->Id = id;
    position = 0;
    money = startMoney;
    toEarn = 0;
}
