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

    void setMapConf(int j, int tr, int ta, int w, int sm, int sb, int st);
};

