#include "settings.h"

Settings::Settings(int dicecount)
{
    switch (dicecount) {
    case 0:
        diceCount = 1;
        break;
    case 1:
        diceCount = 2;
        break;
    }

    startSumm = 300;
    moneyForCircle = 100;
}

void Settings::setMapConf(int j, int tr, int ta, int w, int sm, int sb, int st)
{
    Jail = j;
    Train = tr;
    Taxes = ta;
    Wormhole = w;
    SocialMoney = sm;
    SocialBank = sb;
    Stock = st;
}
