#include "game.h"
#include <stdlib.h>

Game::Game(int plCnt , int startLave)
{
    settings = new Settings();

    setUpMap();

    playersCount = plCnt;
    currentPlayer = 0;
    socialMoney = 0;

    for (int i = 0 ; i < 4 ; i++ ) skippingPlayers[i] = 0;

    for (int i = 0 ; i < playersCount ; i++ ){
        players[i] = new Figure(i, startLave);
    }
}

void Game::throwDices()
{
    int result = ( rand() % ( 6 * settings->diceCount ) ) + 1;
    this->diceResult = result;
}

void Game::setUpMap()
{
    map[0] = new MapSquare("Старт",                 settings->START             );
    map[1] = new MapSquare("Лоток на рынке",        settings->ENTERPRISE , 250  );
    map[2] = new MapSquare("Овощебаза",             settings->ENTERPRISE , 350  );
    map[3] = new MapSquare("Птичий рынок",          settings->ENTERPRISE , 450  );
    map[4] = new MapSquare("Мир Отторг",            settings->ENTERPRISE , 500  );
    map[5] = new MapSquare("Налоговая",             settings->TAXES             );
    map[6] = new MapSquare("Тюрьма",                settings->JAIL              );
    map[7] = new MapSquare("Пилорама",              settings->ENTERPRISE , 650  );
    map[8] = new MapSquare("Стекольный\nзавод",     settings->ENTERPRISE , 700  );
    map[9] = new MapSquare("Сталелитейный\nзавод",  settings->ENTERPRISE , 900  );
    map[10] = new MapSquare("Никелевый завод",      settings->ENTERPRISE , 1000 );
    map[11] = new MapSquare("Ж/д Вокзал",           settings->TRAIN             );
    map[12] = new MapSquare("Шаурма/курица",        settings->ENTERPRISE , 1200 );
    map[13] = new MapSquare("Шаурма/свинина",       settings->ENTERPRISE , 1300 );
    map[14] = new MapSquare("Фондовая биржа",       settings->STOCK             );
    map[15] = new MapSquare("Общественный\nбанк",   settings->SOCIAL_BANK       );
    map[16] = new MapSquare("BiLier",               settings->ENTERPRISE , 1800 );
    map[17] = new MapSquare("ОмегаФонк",            settings->ENTERPRISE , 2000 );
    map[18] = new MapSquare("Ж/д Вокзал",           settings->TRAIN             );
    map[19] = new MapSquare("Eric Games",           settings->ENTERPRISE , 2400 );
    map[20] = new MapSquare("Lizzard",              settings->ENTERPRISE , 2650 );
    map[21] = new MapSquare("Fliptendo",            settings->ENTERPRISE , 2900 );
    map[22] = new MapSquare("MegaSoft",             settings->ENTERPRISE , 3300 );
    map[23] = new MapSquare("Червоточина",          settings->WORMHOLE          );
    map[24] = new MapSquare("Тюрьма",               settings->JAIL              );
    map[25] = new MapSquare("АвтоГЛАЗ",             settings->ENTERPRISE , 4000 );
    map[26] = new MapSquare("АвтоНАСТ",             settings->ENTERPRISE , 4500 );
    map[27] = new MapSquare("АвтоКАСТ",             settings->ENTERPRISE , 5000 );
    map[28] = new MapSquare("АвтоМАСТ",             settings->ENTERPRISE , 5700 );
    map[29] = new MapSquare("Ж/д Вокзал",           settings->TRAIN             );
    map[30] = new MapSquare("Xednay",               settings->ENTERPRISE , 7000 );
    map[31] = new MapSquare("ThreeStars",           settings->ENTERPRISE , 8000 );
    map[32] = new MapSquare("Революция",            settings->LENIN             );
    map[33] = new MapSquare("Общественная\nказна",  settings->SOCIAL_MONEY      );
    map[34] = new MapSquare("XiaNotYou",            settings->ENTERPRISE , 9000 );
    map[35] = new MapSquare("Pear",                 settings->ENTERPRISE ,10000 );
}
