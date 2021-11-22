#pragma once


class Figure
{
public:
    Figure(int id);

    int Id;
    int direction;
    int position;
    int money;
    int toEarn;

    void checkForDirection();
};

