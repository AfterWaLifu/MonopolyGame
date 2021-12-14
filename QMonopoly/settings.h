#pragma once

class Settings
{
public:
    Settings(int dicecount);

    int Jail;
    int Train;
    int Taxes;
    int Wormhole;
    int SocialMoney;
    int SocialBank;
    int Stock;

    int percentToPtP;
    int moneyForCircle;
    int startSumm;
    int diceCount;
    int taxPercent;
    int moneyToAddOrSub;

    void setMapConf();

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
        MINUS_LARGEST_MONEY
    };
};

