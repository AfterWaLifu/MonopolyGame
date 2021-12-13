#pragma once

class Figure
{
public:
    Figure(int id, int startMoney);

    int Id;
    int position;
    int toEarn;

    inline void subMoney(int q) { money -= q; if (money <= 0) Id = -1;}
    inline void addMoney(int q) { money += q; }
    inline int getMoneyQ() { return money; }

private:
    int money;
};

