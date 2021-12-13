#include "figure.h"

Figure::Figure(int id, int startMoney)
{
    this->Id = id;
    position = 0;
    money = startMoney;
    toEarn = 0;
}

void Figure::subMoney(int q)
{
    money -= q;
    if (money <= 0) Id = -1;
}

void Figure::addMoney(int q)
{
    money += q;
}
