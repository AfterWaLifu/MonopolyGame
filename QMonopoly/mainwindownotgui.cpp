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
