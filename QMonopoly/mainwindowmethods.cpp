#include "mainwindow.h"

QPoint MainWindow::makeCoords(int pos)
{
    QPoint point = squares[pos]->pos();
    switch (game.currentPlayer) {
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
    for (int i = 0 ; i < 4 ; i++ ){
       Lbalance[i]->setText( QString::number(game.players[i]->getMoneyQ()) ) ;
       LtoEarn[i]->setText( QString::number(game.players[i]->toEarn + game.settings->moneyForCircle) ) ;

       QString temp;
       temp.append("Список предприятий:\n");
       for (int j = 0 ; j < 36 ; j++ ) {
            if ( game.map[j]->owner == i ) {
                temp.append(game.map[j]->name + ", +" + QString::number(game.map[j]->toEarn) + ", s=" + QString::number(game.map[j]->toSell));
            }
       }
       TplayersOwns[i]->setPlainText(temp);
    }
}

void MainWindow::checkForSpecialSquares()
{
    int temp = game.map[ game.players[game.currentPlayer]->position + game.diceResult]->type ;
    if ( temp != game.settings->ENTERPRISE ){

        if ( temp == game.settings->JAIL ){
            game.skippingPlayers[game.currentPlayer] = 1;
            wl->addLine( "Игрок " + QString::number(game.currentPlayer + 1) + " пропускает следующий ход\n\n" , 2);
        }
        else if ( temp == game.settings->TRAIN ) {
            int station;

            if (game.players[game.currentPlayer]->position == 11) station = 1;
            else if (game.players[game.currentPlayer]->position == 18) station = 2;
            else station = 3;

            if (station == 2) game.diceResult+=11;
            else game.diceResult+=7;

            game.toCheckOrNotToCheck=false;
            wl->addLine( "Игрок " + QString::number(game.currentPlayer + 1) + " чучухает от станции " + QString::number(station) + "\n\n" , 2);
        }
        else if ( temp == game.settings->TAXES ) {

        }
        else if ( temp == game.settings->WORMHOLE ) {

        }
        else if ( temp == game.settings->SOCIAL_MONEY ) {

        }
        else if ( temp == game.settings->SOCIAL_BANK ) {

        }
        else if ( temp == game.settings->LENIN ) {

        }
        else if ( temp == game.settings->STOCK ) {

        }
        else if ( temp == game.settings->ONE_MORE_TIME ) {

        }
        else if ( temp == game.settings->PENALTY ) {

        }
        else if ( temp == game.settings->PLUS_ONE ) {

        }
        else if ( temp == game.settings->PLUS_TWO ) {

        }
        else if ( temp == game.settings->PLUS_THREE ) {

        }
        else if ( temp == game.settings->MINUS_SIX ) {

        }
        else if ( temp == game.settings->PLUS_MONEY ) {

        }
        else if ( temp == game.settings->MINUS_CONSTMONEY ) {

        }
        else if ( temp == game.settings->MINUS_LARGEST_MONEY ) {

        }
    }
}

void MainWindow::runforestrun()
{
    QPoint p = makeCoords(game.players[game.currentPlayer]->position);
    QPoint add = addCoords(game.currentPlayer);

    if (Lplayers[game.currentPlayer]->pos() == p) {
        timer->stop();
        buttonsEnable();
        if (game.currentPlayer == 3) game.currentPlayer = 0;
        else game.currentPlayer++;
    }
    else{
        if ( game.diceResult < 18 ) {
            if (Lplayers[game.currentPlayer]->x() < 1100+add.x() && Lplayers[game.currentPlayer]->y() == 0+add.y()){
                Lplayers[game.currentPlayer]->move(Lplayers[game.currentPlayer]->x() + 10 , Lplayers[game.currentPlayer]->y());
            }else if (Lplayers[game.currentPlayer]->x() == 1100+add.x() && Lplayers[game.currentPlayer]->y() < 700+add.y()){
                Lplayers[game.currentPlayer]->move(Lplayers[game.currentPlayer]->x() , Lplayers[game.currentPlayer]->y() + 10);
            }else if (Lplayers[game.currentPlayer]->x() > 0+add.x() && Lplayers[game.currentPlayer]->y() == 700+add.y()){
                Lplayers[game.currentPlayer]->move(Lplayers[game.currentPlayer]->x() - 10 , Lplayers[game.currentPlayer]->y());
            }else{
                Lplayers[game.currentPlayer]->move(Lplayers[game.currentPlayer]->x() , Lplayers[game.currentPlayer]->y() - 10);
            }
        }
        else{
            if (Lplayers[game.currentPlayer]->x() > 0+add.x() && Lplayers[game.currentPlayer]->y() == 0+add.y()){
                Lplayers[game.currentPlayer]->move(Lplayers[game.currentPlayer]->x() - 10 , Lplayers[game.currentPlayer]->y());
            }else if (Lplayers[game.currentPlayer]->x() == 0+add.x() && Lplayers[game.currentPlayer]->y() < 700+add.y()){
                Lplayers[game.currentPlayer]->move(Lplayers[game.currentPlayer]->x() , Lplayers[game.currentPlayer]->y() + 10);
            }else if (Lplayers[game.currentPlayer]->x() < 1100+add.x() && Lplayers[game.currentPlayer]->y() == 700+add.y()){
                Lplayers[game.currentPlayer]->move(Lplayers[game.currentPlayer]->x() + 10 , Lplayers[game.currentPlayer]->y());
            }else{
                Lplayers[game.currentPlayer]->move(Lplayers[game.currentPlayer]->x() , Lplayers[game.currentPlayer]->y() - 10);
            }
        }
    }
}

void MainWindow::buttonsEnable()
{
    for (int i = 0 ; i < 4 ; i++ ){
        buyButtons[i]->setEnabled(true);
        sellButtons[i]->setEnabled(true);
        diceButton->setEnabled(true);
    }
}

void MainWindow::buttonsDisable()
{
    for (int i = 0 ; i < 4 ; i++ ){
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
            if ( game.map[i]->type == game.settings->ENTERPRISE )
                temp.append( "\nЦена: " + QString::number(game.map[i]->cost) +
                             ", продать: " + QString::number(game.map[i]->toSell) +
                             ", за круг: " + QString::number(game.map[i]->toEarn) );
            else{
                if ( game.map[i]->type == game.settings->JAIL ) temp.append("\nИгрок пропускает ход");
                else if ( game.map[i]->type == game.settings->TRAIN ) temp.append("\nИгрок переходи на следующую станцию");
                else if ( game.map[i]->type == game.settings->TAXES ) temp.append("\nИгрок платит налоги с предприятий");
                else if ( game.map[i]->type == game.settings->WORMHOLE ) temp.append("\nИгрок переносится на случайную позицию");
                else if ( game.map[i]->type == game.settings->SOCIAL_MONEY ) temp.append("\nИгрок забирает скопившиеся деньги (" +QString::number(game.socialMoney) + ")");
                else if ( game.map[i]->type == game.settings->SOCIAL_BANK ) temp.append("\nИгрок отдаёт часть денег в общественную казну");
                else if ( game.map[i]->type == game.settings->LENIN ) temp.append("\nИгрок теряет случайное предприятие");
                else if ( game.map[i]->type == game.settings->STOCK ) temp.append("\nИгрок играет на бирже на прибыль с круга");
                else if ( game.map[i]->type == game.settings->ONE_MORE_TIME ) temp.append("\nИгрок делает ещё один бросок");
                else if ( game.map[i]->type == game.settings->PENALTY ) temp.append("\nИгрок пропускает два хода");
                else if ( game.map[i]->type == game.settings->PLUS_ONE ) temp.append("\nИгрок делает шаг вперёд");
                else if ( game.map[i]->type == game.settings->PLUS_TWO ) temp.append("\nИгрок делает два шага вперёд");
                else if ( game.map[i]->type == game.settings->PLUS_THREE ) temp.append("\nИгрок делает три шага вперёд");
                else if ( game.map[i]->type == game.settings->MINUS_SIX ) temp.append("\nИгрок делает шесть шагов назад");
                else if ( game.map[i]->type == game.settings->PLUS_MONEY ) temp.append("\nИгрок получает сумму за круг");
                else if ( game.map[i]->type == game.settings->MINUS_CONSTMONEY ) temp.append("\nИгрок теряет сумму за круг");
                else if ( game.map[i]->type == game.settings->MINUS_LARGEST_MONEY ){
                    temp.append("\nИгрок отдаёт стоимость самого дорогого\nпредприятия");
                    lines++;
                }
            }
            wl->addLine( temp + "\n\n" , lines );
        }
    }
}

void MainWindow::forBuyButtons()
{
    updFigureInfo();
}

void MainWindow::forSellButtons()
{
    updFigureInfo();
}

void MainWindow::move(int q)
{
    if (game.skippingPlayers[game.currentPlayer]){
        game.skippingPlayers[game.currentPlayer]--;
        wl->addLine( "Игрок " + QString::number(game.currentPlayer+1) + " своё отсидел\n\n" , 2 );
        if (game.currentPlayer == 3) game.currentPlayer = 0;
        else game.currentPlayer++;
        return;
    }

    buttonsDisable();

    if ( !q ) game.diceResult = 14 + y;
    else game.diceResult = q ;
    if (game.currentPlayer == 0)y++;
    wl->addLine("Игрок " + QString::number(game.currentPlayer+1) + "\nРезультат броска " + QString::number(game.diceResult)+"\n\n", 3 );

    if (game.toCheckOrNotToCheck) checkForSpecialSquares();
    else game.toCheckOrNotToCheck = true;

    game.players[game.currentPlayer]->position += game.diceResult ;

    if (game.players[game.currentPlayer]->position >35) {
        game.players[game.currentPlayer]->position -= 36;
        game.players[game.currentPlayer]->addMoney( game.settings->moneyForCircle );
        game.players[game.currentPlayer]->addMoney( game.players[game.currentPlayer]->toEarn ) ;
        Lbalance[game.currentPlayer]->setText(QString::number(game.players[game.currentPlayer]->getMoneyQ()));
    }
    else if (game.players[game.currentPlayer]->position <0)game.players[game.currentPlayer]->position += 36;

    updFigureInfo();

    timer->start();
}
