#include "figure.h"

Figure::Figure(int id)
{
    this->Id = id;
    direction = 0;
}

void Figure::checkForDirection()
{
    if (position < 11) direction = 0;
    else if (position >= 11 && position < 18) direction = 1;
    else if (position > 29) direction =3;
    else direction = 2;
}
