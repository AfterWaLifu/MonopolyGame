#include "settings.h"

Settings::Settings(int i)
{
    switch (i) {
    case 0:
        diceCount = 2;
        break;
    case 1:
        diceCount = 1;
        break;
    }
}
