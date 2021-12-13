#pragma once

class Figure
{
public:
    Figure(int id, int startMoney);

    int Id;
    int position;
    int toEarn;

    void subMoney(int q);
    void addMoney(int q);

private:
    int money;
};

