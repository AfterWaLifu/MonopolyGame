#include "settings.h"

Settings::Settings(int dicecount)
{
    switch (dicecount) {
    case 0:
        diceCount = 2;
        break;
    case 1:
        diceCount = 1;
        break;
    }


}
