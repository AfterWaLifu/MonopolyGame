#include "mainwindow.h"

QPoint MainWindow::makeCoords(int pos)
{
    QPoint point = squares[pos]->pos();
    switch (game->currentPlayer) {
    case 1:
        point.setX(point.x()+55);
        point.setY(point.y()+5);
        break;
    case 2:
        point.setX(point.x()+5);
        point.setY(point.y()+55);
        break;
    case 3:
        point.setX(point.x()+55);
        point.setY(point.y()+55);
        break;
    default:
        point.setX(point.x()+5);
        point.setY(point.y()+5);
        break;
    }
    return point;
}

QPoint MainWindow::addCoords(int p)
{
    QPoint result(0,0);
    switch (p) {
    case 0:
        result.setX(5);
        result.setY(5);
        break;
    case 1:
        result.setX(55);
        result.setY(5);
        break;
    case 2:
        result.setX(5);
        result.setY(55);
        break;
    case 3:
        result.setX(55);
        result.setY(55);
        break;
    }
    return result;
}

void MainWindow::updFigureInfo()
{
    for (int i = 0 ; i < game->playersCount ; i++ ){
       Lbalance[i]->setText( QString::number(game->players[i]->getMoneyQ()) ) ;
       LtoEarn[i]->setText( QString::number(game->players[i]->toEarn + game->settings->moneyForCircle) ) ;

       QString temp;
       temp.append("Список предприятий:\n");
       for (int j = 0 ; j < 36 ; j++ ) {
            if ( game->map[j]->owner == i ) {
                temp.append(game->map[j]->name + ", +" + QString::number(game->map[j]->toEarn) + ", s=" + QString::number(game->map[j]->toSell) + "\n");
            }
       }
       TplayersOwns[i]->setPlainText(temp);
    }
}

void MainWindow::checkForSpecialSquares()
{
    int temploc = game->players[game->currentPlayer]->position + game->diceResult;
    if (temploc > 35) temploc -= 36;
    else if (temploc < 0) temploc +=36;

    int temp = game->map[ temploc ]->type ;

    if ( temp != game->settings->ENTERPRISE ){
        if ( temp == game->settings->JAIL ){
            game->skippingPlayers[game->currentPlayer] = 1;
            wl->addLine( "Игрок " + QString::number(game->currentPlayer + 1) + " пропускает следующий ход\n\n" , 2);
        }
        else if ( temp == game->settings->TRAIN ) {
            int station;

            if (game->players[game->currentPlayer]->position+ game->diceResult == 11) station = 1;
            else if (game->players[game->currentPlayer]->position+ game->diceResult == 18) station = 2;
            else station = 3;

            if (station == 2) game->diceResult+=11;
            else game->diceResult+=7;

            game->toCheckOrNotToCheck=false;
            wl->addLine( "Игрок " + QString::number(game->currentPlayer + 1) + " чучухает от станции " + QString::number(station) + "\n\n" , 2);
        }
        else if ( temp == game->settings->TAXES ) {
            int tax = 0;
            for (int i = 0 ; i < 36 ; i++ ){
                if (game->map[i]->owner == game->currentPlayer) tax += game->map[i]->cost*game->settings->taxPercent/100;
            }
            game->players[game->currentPlayer]->subMoney(tax);
            wl->addLine( "Игрок " + QString::number(game->currentPlayer + 1) + " заплатил налог " + QString::number(tax) + "\n\n" , 2);
        }
        else if ( temp == game->settings->WORMHOLE ) {
            game->diceResult = rand()%35 + 1;
            wl->addLine("Игрок " + QString::number(game->currentPlayer + 1) + " попал в червоточину\n\n" , 2);
        }
        else if ( temp == game->settings->SOCIAL_MONEY ) {
            wl->addLine("Игрок " + QString::number(game->currentPlayer + 1) + " забрал из общих денег " + QString::number(game->socialMoney) + " валюты\n\n" , 2);
            game->players[game->currentPlayer]->addMoney(game->socialMoney);
            game->socialMoney = 0;
        }
        else if ( temp == game->settings->SOCIAL_BANK ) {
            wl->addLine("Игрок " + QString::number(game->currentPlayer + 1) + " оставил в общих деньгах полтос\n\n" , 2);
            game->players[game->currentPlayer]->subMoney(50);
            game->socialMoney += 50;
        }
        else if ( temp == game->settings->LENIN ) {
            std::vector<int> builds;
            for (int i = 0 ; i < 36 ; i++ ){
                if (game->map[i]->owner == game->currentPlayer) builds.push_back(i);
            }
            if (builds.size()){
                int stealed = rand() % builds.size();
                game->map[ builds.at(stealed) ]->owner = -1;
                wl->addLine("Игрок " + QString::number(game->currentPlayer + 1) + " потерял " + game->map[stealed]->name + "\n\n" , 2);
                squares[stealed]->setPalette( QPalette(QColor(255,255,255,255)) );
            }
            else{
                wl->addLine("Игрок " + QString::number(game->currentPlayer + 1) + " ничего не потерял, тк нечего\n\n" , 2);
            }
        }
        else if ( temp == game->settings->STOCK ) {
            int pc, pl;
            pc = rand()%5+1;
            pl = rand()%5+1;
            wl->addLine("Игрок " + QString::number(pl) + " : " + QString::number(pc) + "Не игрок\n\n" , 2 );
            if (pc > pl){
                game->players[game->currentPlayer]->subMoney(game->players[game->currentPlayer]->toEarn);
                wl->addLine("Вы проиграли сумму за круг\n" , 1 );
            }
            else if (pc == pl) wl->addLine( "НИЧЬЯ\n" , 1 );
            else{
                game->players[game->currentPlayer]->addMoney(game->players[game->currentPlayer]->toEarn);
                wl->addLine("Вы выиграли сумму за круг\n" , 1 );
            }
            wl->addLine("Игрок " + QString::number(game->currentPlayer+1) + ",\n" , 1 );
        }
        else if ( temp == game->settings->ONE_MORE_TIME ) {
            int add = ( rand() % ( 6 * game->settings->diceCount ) ) + 1;
            game->diceResult += add;
            wl->addLine("Игрок " + QString::number(game->currentPlayer + 1) + " бросил ещё кубов и получил " + QString::number(add) + "\n\n" , 2);
        }
        else if ( temp == game->settings->PENALTY ) {
            game->skippingPlayers[game->currentPlayer] = 2;
            wl->addLine( "Игрок " + QString::number(game->currentPlayer + 1) + " пропускает следующие 2 хода\n\n" , 2);
        }
        else if ( temp == game->settings->PLUS_ONE ) {
            game->diceResult += 1;
            wl->addLine( "Игрок " + QString::number(game->currentPlayer + 1) + " совершает ещё шаг\n\n" , 2 );
        }
        else if ( temp == game->settings->PLUS_TWO ) {
            game->diceResult += 2;
            wl->addLine( "Игрок " + QString::number(game->currentPlayer + 1) + " совершает ещё 2 шага\n\n" , 2 );
        }
        else if ( temp == game->settings->PLUS_THREE ) {
            game->diceResult += 3;
            wl->addLine( "Игрок " + QString::number(game->currentPlayer + 1) + " совершает ещё 3 шага\n\n" , 2 );
        }
        else if ( temp == game->settings->MINUS_SIX ) {
            game->diceResult += 6;
            wl->addLine( "Игрок " + QString::number(game->currentPlayer + 1) + " отходит на 6 назад\n\n" , 2 );
        }
        else if ( temp == game->settings->PLUS_MONEY ) {
            game->players[game->currentPlayer]->addMoney(game->settings->moneyToAddOrSub);
            wl->addLine( "Игрок " + QString::number(game->currentPlayer + 1) + " нашёл денюжку\n\n" , 2 );
        }
        else if ( temp == game->settings->MINUS_CONSTMONEY ) {
            game->players[game->currentPlayer]->subMoney(game->settings->moneyToAddOrSub);
            wl->addLine( "Игрок " + QString::number(game->currentPlayer + 1) + " потерял денюжку\n\n" , 2 );
        }
        else if ( temp == game->settings->MINUS_LARGEST_MONEY ) {
            int cost = -1;
            for (int i = 0 ; i < 36 ; i++ ){
                if (game->map[i]->owner  == game->currentPlayer && cost < game->map[i]->cost ) cost = game->map[i]->cost;
            }
            if (cost > 0){
                game->players[game->currentPlayer]->subMoney(cost);
                wl->addLine( "Игрок " + QString::number(game->currentPlayer + 1) + " теряет " + QString::number(cost) + " валюты\n\n" , 2 );
            }
            else{
                wl->addLine( "Игрок " + QString::number(game->currentPlayer + 1) + " не имеет что терять\n\n" , 2 );
            }
        }
        else if ( temp == game->settings->NOTHING ) wl->addLine( "Кто-то попал на пустою клетку\n\n" , 2 );
    }
    else{
        if (game->map[temploc]->owner == game->currentPlayer){
            game->players[game->currentPlayer]->addMoney(game->map[temploc]->toEarn);
        }
        else if (game->map[temploc]->owner > -1){
            game->players[game->currentPlayer]->subMoney(game->map[temploc]->cost * game->settings->percentToPtP / 100);
            game->players[game->map[temploc]->owner]->addMoney(game->map[temploc]->cost * game->settings->percentToPtP / 100);
        }
    }
}

void MainWindow::updateSettings()
{
    if (ws->jail->currentIndex() == 0 ) {
        game->map[6]->name = "Тюрьма";
        game->map[6]->type = game->settings->JAIL;
        squares[6]->setText(game->map[6]->name);
        game->map[24]->name = "Тюрьма";
        game->map[24]->type = game->settings->JAIL;
        squares[24]->setText(game->map[24]->name);
    }
    else if (ws->jail->currentIndex() == 1 ){
        game->map[6]->name = "Штраф";
        game->map[6]->type = game->settings->MINUS_CONSTMONEY;
        squares[6]->setText(game->map[6]->name);
        game->map[24]->name = "Штраф";
        game->map[24]->type = game->settings->MINUS_CONSTMONEY;
        squares[24]->setText(game->map[24]->name);
    }
    else if (ws->jail->currentIndex() == 2 ){
        game->map[6]->name = "Повторный бросок";
        game->map[6]->type = game->settings->ONE_MORE_TIME;
        squares[6]->setText(game->map[6]->name);
        game->map[24]->name = "Повторный бросок";
        game->map[24]->type = game->settings->ONE_MORE_TIME;
        squares[24]->setText(game->map[24]->name);
    }
    else if (ws->jail->currentIndex() == 3 ){
        game->map[6]->name = "Ничего";
        game->map[6]->type = game->settings->NOTHING;
        squares[6]->setText(game->map[6]->name);
        game->map[24]->name = "Ничего";
        game->map[24]->type = game->settings->NOTHING;
        squares[24]->setText(game->map[24]->name);
    }

    if (ws->train->currentIndex() == 0 ){
        game->map[11]->name = "Ж/д Вокзал";
        game->map[11]->type = game->settings->TRAIN;
        squares[11]->setText(game->map[11]->name);
        game->map[18]->name = "Ж/д Вокзал";
        game->map[18]->type = game->settings->TRAIN;
        squares[18]->setText(game->map[18]->name);
        game->map[29]->name = "Ж/д Вокзал";
        game->map[29]->type = game->settings->TRAIN;
        squares[29]->setText(game->map[29]->name);
    }
    else if (ws->train->currentIndex() == 1 ){
        game->map[11]->name = "+1 шаг";
        game->map[11]->type = game->settings->PLUS_ONE;
        squares[11]->setText(game->map[11]->name);
        game->map[18]->name = "+2 шага";
        game->map[18]->type = game->settings->PLUS_TWO;
        squares[18]->setText(game->map[18]->name);
        game->map[29]->name = "+3 шага";
        game->map[29]->type = game->settings->PLUS_THREE;
        squares[29]->setText(game->map[29]->name);
    }
    else if (ws->train->currentIndex() == 2 ){
        game->map[11]->name = "Повторный бросок";
        game->map[11]->type = game->settings->ONE_MORE_TIME;
        squares[11]->setText(game->map[11]->name);
        game->map[18]->name = "Повторный бросок";
        game->map[18]->type = game->settings->ONE_MORE_TIME;
        squares[18]->setText(game->map[18]->name);
        game->map[29]->name = "Повторный бросок";
        game->map[29]->type = game->settings->ONE_MORE_TIME;
        squares[29]->setText(game->map[29]->name);
    }
    else if (ws->train->currentIndex() == 3 ){
        game->map[11]->name = "Ничего";
        game->map[11]->type = game->settings->NOTHING;
        squares[11]->setText(game->map[11]->name);
        game->map[18]->name = "Ничего";
        game->map[18]->type = game->settings->NOTHING;
        squares[18]->setText(game->map[18]->name);
        game->map[29]->name = "Ничего";
        game->map[29]->type = game->settings->NOTHING;
        squares[29]->setText(game->map[29]->name);
    }

    if (ws->worm->currentIndex() == 0){
        game->map[23]->name = "Червоточина";
        game->map[23]->type = game->settings->WORMHOLE;
        squares[23]->setText(game->map[23]->name);
    }
    else if (ws->worm->currentIndex() == 1) {
        game->map[23]->name = "6 шагов назад";
        game->map[23]->type = game->settings->MINUS_SIX;
        squares[23]->setText(game->map[23]->name);
    }
    else if (ws->worm->currentIndex() == 2) {
        game->map[23]->name = "Ничего";
        game->map[23]->type = game->settings->NOTHING;
        squares[23]->setText(game->map[23]->name);
    }

    if (ws->social->currentIndex() == 0){
        game->map[15]->name = "Общественный\nбанк";
        game->map[15]->type = game->settings->SOCIAL_BANK;
        squares[15]->setText(game->map[15]->name);
        game->map[33]->name = "Общественная\nказна";
        game->map[33]->type = game->settings->SOCIAL_MONEY;
        squares[33]->setText(game->map[33]->name);
    }
    else if (ws->social->currentIndex() == 1){
        game->map[15]->name = "Отдать валюты";
        game->map[15]->type = game->settings->MINUS_CONSTMONEY;
        squares[15]->setText(game->map[15]->name);
        game->map[33]->name = "Взять валюты";
        game->map[33]->type = game->settings->PLUS_MONEY;
        squares[33]->setText(game->map[33]->name);
    }
    else if (ws->social->currentIndex() == 2){
        game->map[15]->name = "Ничего";
        game->map[15]->type = game->settings->NOTHING;
        squares[15]->setText(game->map[15]->name);
        game->map[33]->name = "Ничего";
        game->map[33]->type = game->settings->NOTHING;
        squares[33]->setText(game->map[33]->name);
    }

    if (ws->lenin->currentIndex() == 0) {
        game->map[32]->name = "Революция";
        game->map[32]->type = game->settings->LENIN;
        squares[32]->setText(game->map[32]->name);
    }
    else if (ws->lenin->currentIndex() == 1) {
        game->map[32]->name = "Штраф в цену\nдорогого пр.";
        game->map[32]->type = game->settings->MINUS_LARGEST_MONEY;
        squares[32]->setText(game->map[32]->name);
    }
    else if (ws->lenin->currentIndex() == 2) {
        game->map[32]->name = "Ничего";
        game->map[32]->type = game->settings->NOTHING;
        squares[32]->setText(game->map[32]->name);
    }

    if (ws->stock->currentIndex() == 0) {
        game->map[14]->name = "Фондовая биржа";
        game->map[14]->type = game->settings->STOCK;
        squares[14]->setText(game->map[14]->name);
    }
    else if (ws->stock->currentIndex() == 1) {
        game->map[14]->name = "Пропуск хода х2";
        game->map[14]->type = game->settings->PENALTY;
        squares[14]->setText(game->map[14]->name);
    }
    else if (ws->stock->currentIndex() == 2) {
        game->map[14]->name = "Ничего";
        game->map[14]->type = game->settings->NOTHING;
        squares[14]->setText(game->map[14]->name);
    }

    game->settings->taxPercent = ws->taxes->value();
    game->settings->moneyForCircle = ws->circle->value();
    game->settings->startSumm = ws->startLave->value();

    if (ws->dicesQ[0]->isChecked()) game->settings->diceCount = 1;
    else game->settings->diceCount = 2;

    updFigureInfo();
}

void MainWindow::startNewGame()
{
    updateSettings();
    game->currentPlayer = 0;
    game->socialMoney = 0;

    for (int i = 0 ; i < 4 ; i++ ) game->skippingPlayers[i] = 0;

    for (int i = 0 ; i < game->playersCount ; i++ ){
        game->players[i] = new Figure(i, game->settings->startSumm);
        Lplayers[i]->move( 5 + ( i % 2 * 50 ) , 5 + ( i / 2 * 50));

    }

    for (int i = 0 ; i < 36 ; i++){
        if (game->map[i]->type == game->settings->ENTERPRISE) game->map[i]->owner = -1;
    }

    updFigureInfo();

    wl->addLine("Новая игра была начата\n\n", 2);

}

void MainWindow::runforestrun()
{
    QPoint p = makeCoords(game->players[game->currentPlayer]->position);
    QPoint add = addCoords(game->currentPlayer);

    if (Lplayers[game->currentPlayer]->pos() == p) {

        timer->stop();
        buttonsEnable();

        if (game->currentPlayer == game->playersCount-1) game->currentPlayer = 0;
        else game->currentPlayer++;

        if (game->skippingPlayers[game->currentPlayer]){
            game->skippingPlayers[game->currentPlayer]--;
            wl->addLine( "Игрок " + QString::number(game->currentPlayer+1) + " пропускает ход\n\n" , 2 );
            if (game->currentPlayer == game->playersCount-1) game->currentPlayer = 0;
            else game->currentPlayer++;
            return;
        }
        updFigureInfo();
    }
    else{
        if ( game->diceResult <= 18 ) {
            if (Lplayers[game->currentPlayer]->x() < 1100+add.x() && Lplayers[game->currentPlayer]->y() == 0+add.y()){
                Lplayers[game->currentPlayer]->move(Lplayers[game->currentPlayer]->x() + 10 , Lplayers[game->currentPlayer]->y());
            }else if (Lplayers[game->currentPlayer]->x() == 1100+add.x() && Lplayers[game->currentPlayer]->y() < 700+add.y()){
                Lplayers[game->currentPlayer]->move(Lplayers[game->currentPlayer]->x() , Lplayers[game->currentPlayer]->y() + 10);
            }else if (Lplayers[game->currentPlayer]->x() > 0+add.x() && Lplayers[game->currentPlayer]->y() == 700+add.y()){
                Lplayers[game->currentPlayer]->move(Lplayers[game->currentPlayer]->x() - 10 , Lplayers[game->currentPlayer]->y());
            }else{
                Lplayers[game->currentPlayer]->move(Lplayers[game->currentPlayer]->x() , Lplayers[game->currentPlayer]->y() - 10);
            }
        }
        else{
            if (Lplayers[game->currentPlayer]->x() > 0+add.x() && Lplayers[game->currentPlayer]->y() == 0+add.y()){
                Lplayers[game->currentPlayer]->move(Lplayers[game->currentPlayer]->x() - 10 , Lplayers[game->currentPlayer]->y());
            }else if (Lplayers[game->currentPlayer]->x() == 0+add.x() && Lplayers[game->currentPlayer]->y() < 700+add.y()){
                Lplayers[game->currentPlayer]->move(Lplayers[game->currentPlayer]->x() , Lplayers[game->currentPlayer]->y() + 10);
            }else if (Lplayers[game->currentPlayer]->x() < 1100+add.x() && Lplayers[game->currentPlayer]->y() == 700+add.y()){
                Lplayers[game->currentPlayer]->move(Lplayers[game->currentPlayer]->x() + 10 , Lplayers[game->currentPlayer]->y());
            }else{
                Lplayers[game->currentPlayer]->move(Lplayers[game->currentPlayer]->x() , Lplayers[game->currentPlayer]->y() - 10);
            }
        }
    }
}

void MainWindow::buttonsEnable()
{
    for (int i = 0 ; i < game->playersCount ; i++ ){
        buyButtons[i]->setEnabled(true);
        sellButtons[i]->setEnabled(true);
        diceButton->setEnabled(true);
    }
}

void MainWindow::buttonsDisable()
{
    for (int i = 0 ; i < game->playersCount ; i++ ){
        buyButtons[i]->setEnabled(false);
        sellButtons[i]->setEnabled(false);
        diceButton->setEnabled(false);
    }
}

void MainWindow::forHelpButton()
{
    if (wh->isHidden()){
        wh->show();
    }
    else{
        wh->hide();
    }
}

void MainWindow::forSettingsButton()
{
    if (ws->isHidden()){
        ws->show();
    }
    else{
        ws->hide();
    }
}

void MainWindow::forAnyButton()
{
    QObject* s = QObject::sender();
    for (int i = 0 ; i < 36 ; i++ ){
        if (squares[i] == s){
            QString temp = squares[i]->text();
            temp.replace('\n',' ');
            int lines = 3;
            if ( game->map[i]->type == game->settings->ENTERPRISE )
                temp.append( "\nЦена: " + QString::number(game->map[i]->cost) +
                             ", продать: " + QString::number(game->map[i]->toSell) +
                             ", за круг: " + QString::number(game->map[i]->toEarn) );
            else{
                if ( game->map[i]->type == game->settings->JAIL ) temp.append("\nИгрок пропускает ход");
                else if ( game->map[i]->type == game->settings->TRAIN ) temp.append("\nИгрок переходи на следующую станцию");
                else if ( game->map[i]->type == game->settings->TAXES ) temp.append("\nИгрок платит налоги с предприятий");
                else if ( game->map[i]->type == game->settings->WORMHOLE ) temp.append("\nИгрок переносится на случайную позицию");
                else if ( game->map[i]->type == game->settings->SOCIAL_MONEY ) temp.append("\nИгрок забирает скопившиеся деньги (" +QString::number(game->socialMoney) + ")");
                else if ( game->map[i]->type == game->settings->SOCIAL_BANK ) temp.append("\nИгрок отдаёт часть денег в общественную казну");
                else if ( game->map[i]->type == game->settings->LENIN ) temp.append("\nИгрок теряет случайное предприятие");
                else if ( game->map[i]->type == game->settings->STOCK ) temp.append("\nИгрок играет на бирже на прибыль с круга");
                else if ( game->map[i]->type == game->settings->ONE_MORE_TIME ) temp.append("\nИгрок делает ещё один бросок");
                else if ( game->map[i]->type == game->settings->PENALTY ) temp.append("\nИгрок пропускает два хода");
                else if ( game->map[i]->type == game->settings->PLUS_ONE ) temp.append("\nИгрок делает шаг вперёд");
                else if ( game->map[i]->type == game->settings->PLUS_TWO ) temp.append("\nИгрок делает два шага вперёд");
                else if ( game->map[i]->type == game->settings->PLUS_THREE ) temp.append("\nИгрок делает три шага вперёд");
                else if ( game->map[i]->type == game->settings->MINUS_SIX ) temp.append("\nИгрок делает шесть шагов назад");
                else if ( game->map[i]->type == game->settings->PLUS_MONEY ) temp.append("\nИгрок получает сумму за круг");
                else if ( game->map[i]->type == game->settings->MINUS_CONSTMONEY ) temp.append("\nИгрок теряет сумму за круг");
                else if ( game->map[i]->type == game->settings->MINUS_LARGEST_MONEY ){
                    temp.append("\nИгрок отдаёт стоимость самого дорогого\nпредприятия");
                    lines++;
                }
                else if ( game->map[i]->type == game->settings->NOTHING ) temp.append("\nИгрок ничего не делает");
            }
            wl->addLine( temp + "\n\n" , lines );
        }
    }
}

void MainWindow::forBuyButtons()
{
    QObject *s = QObject::sender();
    int pWannaBuy = -1;

    for (int i = 0 ; i < game->playersCount ; i++ ){
        if (buyButtons[i] == s){
            pWannaBuy = i;
            break;
        }
    }

    int needed = game->players[pWannaBuy]->position;

    if ( game->map[needed]->type == game->settings->ENTERPRISE ){
        if (game->map[needed]->owner > -1) {
            wl->addLine( game->map[needed]->name + " принадлежит " + QString::number(game->map[needed]->owner+1) + "\n\n" , 2 );
            return;
        }
        else if (game->map[needed]->cost > game->players[pWannaBuy]->getMoneyQ()){
            wl->addLine( "У игрока " + QString::number(pWannaBuy+1) + " не хватает денег для покупки\n" + game->map[needed]->name + "\n\n" , 3 );
            return;
        }
        else{
            game->players[pWannaBuy]->subMoney(game->map[needed]->cost);
            game->players[pWannaBuy]->toEarn += game->map[needed]->toEarn;
            game->map[needed]->owner = pWannaBuy;
            switch(pWannaBuy){
            case 0:
                squares[needed]->setPalette( QPalette(QColor(75,90,160)) );
                break;
            case 1:
                squares[needed]->setPalette( QPalette(QColor(100,165,105)) );
                break;
            case 2:
                squares[needed]->setPalette( QPalette(QColor(185,85,100)) );
                break;
            case 3:
                squares[needed]->setPalette( QPalette(QColor(165,100,165)) );
                break;
            }
            wl->addLine( "Игрок " + QString::number(pWannaBuy+1) + " купил\n" + game->map[needed]->name + "\n\n", 3 );
        }
    }
    else{
        wl->addLine( game->map[game->players[pWannaBuy]->position]->name + " нельзя купить\n\n", 2 );
        return;
    }

    updFigureInfo();
}

void MainWindow::forSellButtons()
{
    QObject *s = QObject::sender();
    int pWannaSell = -1;

    for (int i = 0 ; i < game->playersCount ; i++ ){
        if (sellButtons[i] == s){
            pWannaSell = i;
            break;
        }
    }

    int needed = game->players[pWannaSell]->position;

    if (game->map[game->players[pWannaSell]->position]->type == game->settings->ENTERPRISE){
        if (game->map[needed]->owner != pWannaSell){
            wl->addLine( "Игрок " + QString::number(pWannaSell+1) + " не владеет\n" + game->map[needed]->name + "\n\n" , 3 );
            return;
        }
        else{
            game->players[pWannaSell]->addMoney(game->map[needed]->toSell);
            game->players[pWannaSell]->toEarn -= game->map[needed]->toEarn;
            game->map[needed]->owner = -1;
            squares[needed]->setPalette( QPalette(QColor(255,255,255,255)) );
            wl->addLine( "Игрок " + QString::number(pWannaSell+1) + " продал\n" + game->map[needed]->name + "\n\n", 3 );
        }
    }
    else{
        wl->addLine( game->map[game->players[pWannaSell]->position]->name + " нельзя продать\n\n", 2 );
    }

    updFigureInfo();
}

void MainWindow::move(int q)
{
    buttonsDisable();

    if ( !q ) game->throwDices();
    else game->diceResult = q ;

    wl->addLine("Игрок " + QString::number(game->currentPlayer+1) + "\nРезультат броска " + QString::number(game->diceResult)+"\n\n", 3 );

    checkForSpecialSquares();

    game->players[game->currentPlayer]->position += game->diceResult ;

    if (game->players[game->currentPlayer]->position >35) {
        game->players[game->currentPlayer]->position -= 36;
        game->players[game->currentPlayer]->addMoney( game->settings->moneyForCircle );
        game->players[game->currentPlayer]->addMoney( game->players[game->currentPlayer]->toEarn ) ;
        Lbalance[game->currentPlayer]->setText(QString::number(game->players[game->currentPlayer]->getMoneyQ()));
    }
    else if (game->players[game->currentPlayer]->position <0)game->players[game->currentPlayer]->position += 36;

    if (game->players[game->currentPlayer]->Id < 0){
        game->skippingPlayers[game->currentPlayer] = 2000000;
        game->currentPlayer++;
        int temp = 0;
        int winner = -1;
        for (int i = 0 ; i < game->playersCount ; i++ ) {if ( game->players[i]->Id < 0) temp++; else winner = i;}
        if (temp == ( game->playersCount - 1 ) ) {
            QMessageBox message;
            message.setText("Победил игрок " + QString::number(winner+1) );
            message.setStandardButtons(QMessageBox::Ok);
            int ret = message.exec();
            if (ret == QMessageBox::Ok) this->close();
        }
        buttonsEnable();
        return;
    }

    timer->start();
}

void MainWindow::updateSkin()
{
    QObject* s = QObject::sender();
    int skin = 0;
    for (int i = 0 ; i < 13 ; i++ ){
        if ( ws->skins[i] == s ) {
            skin = i;
        }
    }
    QString path = QCoreApplication::applicationDirPath();
    path.append("\\resources\\players\\");
    QPixmap pix( path + ws->availableSkins[skin] );
    pix = pix.scaled( Lplayers[0]->size(), Qt::IgnoreAspectRatio);
    Lplayers[ ws->choosingPlayer->currentIndex() ]->setPixmap(pix);
}
