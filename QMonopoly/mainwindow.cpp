#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    windowsInit();
    labelsInit();
    buttonsInit();
    playersInit();
    timerInit();

    start->show();

    this->setGeometry(100,100,1200,800);
    this->setMaximumSize(1200,800);
    this->setMinimumSize(1200,800);

    QString path = QCoreApplication::applicationDirPath();
    path.append("\\resources\\back.jpg");
    QPixmap background(path);
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);
}

MainWindow::~MainWindow()
{

}

void MainWindow::buttonsInit()
{
    QFont font("Verdana", 14);

    diceButton = new QPushButton("Бросить куб",this);
    diceButton->setGeometry( 500 , 350 , 200 , 50 );
    diceButton->setFont(font);
    connect( diceButton , SIGNAL( clicked() ) , this , SLOT( forDiceButton() ) );

    font.setPointSize(12);

    helpButton = new QPushButton("Помощь", this);
    helpButton->setGeometry( 500 , 400 , 100 , 50 );
    helpButton->setFont(font);
    connect(helpButton, SIGNAL(clicked()), this, SLOT(forHelpButton()));

    setsButton = new QPushButton("Настройки", this);
    setsButton->setGeometry( 600 , 400 , 100 , 50 );
    setsButton->setFont(font);
    connect(setsButton, SIGNAL(clicked()), this, SLOT(forSettingsButton()));

    font.setPointSize(16);
    //кнопки по периметру
    for ( int i = 0 ; i < 12 ; i++ ){
        //горизонталь верх
        squares[i] = new QPushButton( QString::number(i) ,this);
        squares[i]->setGeometry(i*100, 0, 100,100);
        squares[i]->setFont(font);
        //горизонталь низ
        squares[i+18] = new QPushButton( QString::number(i+18) , this);
        squares[i+18]->setGeometry(1100-i*100 , 700, 100,100);
        squares[i+18]->setFont(font);
    }
    for ( int i = 12 ; i < 18 ; i++ ){
        //вертикаль право
        squares[i] = new QPushButton( QString::number(i) , this);
        squares[i]->setGeometry(1100, (i-11)*100, 100,100);
        squares[i]->setFont(font);
        //вертикаль лево
        squares[i+18] = new QPushButton( QString::number(i+18) , this);
        squares[i+18]->setGeometry(0, 700-(i-11)*100, 100,100);
        squares[i+18]->setFont(font);
    }

    font.setPointSize(14);

    //игроки покупки продажки
    for ( int i = 0 ; i < 4 ; i++ ){
        buyButtons[i] = new QPushButton( "Купить" , this );
        buyButtons[i]->setGeometry( 110 + ( i % 2 * 780 ) , 210 + ( i / 2 * 300 ) , 200 , 80 );
        buyButtons[i]->setFont( font );

        sellButtons[i] = new QPushButton( "Продать" , this );
        sellButtons[i]->setGeometry( 110 + ( i % 2 * 780 ) , 310 + ( i / 2 * 300 ) , 200 , 80 );
        sellButtons[i]->setFont( font );
    }

    font.~QFont();
}

void MainWindow::labelsInit()
{
    QFont font("Arial", 14);

    // линии на поле
    QString *temp = new QString(100,'_');
    Llines[0] = new QLabel(*temp,this);
    Llines[0]->setFont(font);
    Llines[0]->setGeometry(99, 381,1002, 20);

    temp->clear();
    for (int i = 0; i < 50 ; i++) {
        temp->append('|');
        temp->append('\n');
    }
    Llines[1] = new QLabel(*temp,this);
    Llines[1]->setFont(font);
    Llines[1]->setGeometry(597,100,4,600);

    //остальное
    font.setFamily("Verdana");
    font.setPointSize(14);
    for ( int i = 0 ; i < 4 ; i++ ){
        Lbalance[i] = new QLabel( QString::number(i*100000) , this );
        Lbalance[i]->setFont(font);
        Lbalance[i]->setGeometry(222 + ( i % 2 * 801 ) , 136 + ( i / 2 * 300 ) , 300, 20);

        LtoEarn[i] = new QLabel( QString::number(i*100000) , this );
        LtoEarn[i]->setFont(font);
        LtoEarn[i]->setGeometry(222 + ( i % 2 * 801 ) , 162 + ( i / 2 * 300 ) , 100, 20);
    }
}

void MainWindow::windowsInit()
{
    wh = new WindowHelp( nullptr , Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    wl = new WindowLogs(nullptr , Qt::Window | Qt::WindowMinimizeButtonHint);
    ws = new WindowSettings(nullptr , Qt::Window | Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);
    start = new WindowStart(this , nullptr , Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
}

void MainWindow::playersInit()
{
    for (int i = 0; i < 4 ; i++ ){
        Lplayers[i] = new QLabel( this );
        Lplayers[i]->setGeometry( 5 + ( i % 2 * 50 ) , 5 + ( i / 2 * 50) , 40 , 40 );
        QString path = QCoreApplication::applicationDirPath();
        switch (i){
        case 0:
            path.append("\\resources\\blue.png");
            break;
        case 1:
            path.append("\\resources\\green.png");
            break;
        case 2:
            path.append("\\resources\\red.png");
            break;
        case 3:
            path.append("\\resources\\purple.png");
            break;
        }
        QPixmap pixmap(path);
        pixmap = pixmap.scaled(Lplayers[i]->size(), Qt::IgnoreAspectRatio);
        Lplayers[i]->setPixmap(pixmap);
    }
}

void MainWindow::timerInit()
{
    timer = new QTimer(this);
    timer->setInterval(30);
    connect( timer , SIGNAL( timeout() ) , this , SLOT( runforestrun() ) );
}

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

}

void MainWindow::forBuyButtons()
{

}

void MainWindow::forSellButtons()
{

}

void MainWindow::forDiceButton()
{
    game.players[game.currentPlayer]->position += game.throwDices();
    if (game.players[game.currentPlayer]->position >35) game.players[game.currentPlayer]->position -= 36;
    else if (game.players[game.currentPlayer]->position <0)game.players[game.currentPlayer]->position += 36;
    timer->start();
}

void MainWindow::runforestrun()
{
    QPoint p = makeCoords(game.players[game.currentPlayer]->position);
    QPoint add = addCoords(game.currentPlayer);

    if (Lplayers[game.currentPlayer]->pos() == p) {
        timer->stop();
        if (game.currentPlayer == 3) game.currentPlayer = 0;
        else game.currentPlayer++;
    }
    else{
        if ( std::abs(  game.players[game.currentPlayer]->position - (game.players[game.currentPlayer]->position - game.diceResult) ) <
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

void MainWindow::showMe()
{
    this->show();
    wl->show();
    this->activateWindow();
    start->close();
    delete start;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    wh->close();
    wl->close();
    ws->close();
    QWidget::closeEvent(event);
}
