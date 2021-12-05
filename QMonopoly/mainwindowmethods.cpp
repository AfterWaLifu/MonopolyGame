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
        if ( std::abs(  game.players[game.currentPlayer]->position - (game.players[game.currentPlayer]->position - game.diceResult) ) <=
             std::abs( (game.players[game.currentPlayer]->position - game.diceResult) - game.players[game.currentPlayer]->position )  ){
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
            if ( game.map[i]->type == game.settings->ENTERPRISE )
                temp.append( "\nЦена: " + QString::number(game.map[i]->cost) +
                             ", продать: " + QString::number(game.map[i]->toSell) +
                             ", за круг: " + QString::number(game.map[i]->toEarn) );
            else{
                if ( game.map[i]->type == game.settings->JAIL ) temp.append("\nИгрок пропускает ход");
                if ( game.map[i]->type == game.settings->TRAIN ) temp.append("\nИгрок переходи на следующую станцию");
                if ( game.map[i]->type == game.settings->TAXES ) temp.append("\nИгрок платит налоги с предприятий");
                if ( game.map[i]->type == game.settings->WORMHOLE ) temp.append("\nИгрок переносится на случайную позицию");
                if ( game.map[i]->type == game.settings->SOCIAL_MONEY ) temp.append("\nИгрок забирает скопившиеся деньги (" +QString::number(game.socialMoney) + ")");
                if ( game.map[i]->type == game.settings->SOCIAL_BANK ) temp.append("\nИгрок отдаёт часть денег в общественную казну");
                if ( game.map[i]->type == game.settings->LENIN ) temp.append("\nИгрок теряет случайное предприятие");
                if ( game.map[i]->type == game.settings->STOCK ) temp.append("\nИгрок играет на бирже на прибыль с круга");
                if ( game.map[i]->type == game.settings->ONE_MORE_TIME ) temp.append("\n");
                if ( game.map[i]->type == game.settings->PENALTY ) temp.append("\n");
                if ( game.map[i]->type == game.settings->PLUS_ONE ) temp.append("\n");
                if ( game.map[i]->type == game.settings->PLUS_TWO ) temp.append("\n");
                if ( game.map[i]->type == game.settings->PLUS_THREE ) temp.append("\n");
                if ( game.map[i]->type == game.settings->MINUS_SIX ) temp.append("\n");
                if ( game.map[i]->type == game.settings->PLUS_MONEY ) temp.append("\n");
                if ( game.map[i]->type == game.settings->MINUS_CONSTMONEY ) temp.append("\n");
                if ( game.map[i]->type == game.settings->MINUS_LARGEST_MONEY ) temp.append("\n");
            }
            wl->addLine( temp + "\n\n" , 3 );
        }
    }
}

void MainWindow::forBuyButtons()
{

}

void MainWindow::forSellButtons()
{

}

void MainWindow::forDiceButton()
{
    buttonsDisable();
    game.throwDices();
    wl->addLine("Игрок " + QString::number(game.currentPlayer+1) + "\nРезультат броска " + QString::number(game.diceResult)+"\n\n", 3 );
    game.players[game.currentPlayer]->position += game.diceResult ;
    if (game.players[game.currentPlayer]->position >35) game.players[game.currentPlayer]->position -= 36;
    else if (game.players[game.currentPlayer]->position <0)game.players[game.currentPlayer]->position += 36;
    timer->start();
}
