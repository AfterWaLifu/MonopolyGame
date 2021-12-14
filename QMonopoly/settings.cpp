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
    taxPercent = 7;
    moneyToAddOrSub = 100;

    setMapConf();
}

void Settings::setMapConf()
{
    Jail = JAIL;
    Train = TRAIN;
    Taxes = TAXES;
    Wormhole = WORMHOLE;
    SocialMoney = SOCIAL_MONEY;
    SocialBank = SOCIAL_BANK;
    Stock = STOCK;
}
