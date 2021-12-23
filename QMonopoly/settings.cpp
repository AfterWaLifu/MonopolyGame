#include "settings.h"

Settings::Settings()
{
    diceCount = 2;
    startSumm = 300;
    moneyForCircle = 100;
    taxPercent = 7;
    moneyToAddOrSub = 100;
    percentToPtP = 5;

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
