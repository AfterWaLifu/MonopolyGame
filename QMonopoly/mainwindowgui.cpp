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

    QString path = QCoreApplication::applicationDirPath();

    this->setGeometry(100,100,1200,800);
    this->setMaximumSize(1200,800);
    this->setMinimumSize(1200,800);

    QPixmap iconPix( path.append( "\\resources\\QM.png" ) );
    this->setWindowIcon( QIcon(iconPix) );

    path = QCoreApplication::applicationDirPath();
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

    font.setPointSize(7);
    //кнопки по периметру
    for ( int i = 0 ; i < 12 ; i++ ){
        //горизонталь верх
        squares[i] = new QPushButton( game.map[i]->name ,this);
        squares[i]->setGeometry(i*100, 0, 100,100);
        squares[i]->setFont(font);
        connect(squares[i] , SIGNAL( clicked() ), this, SLOT( forAnyButton() ) );
        //горизонталь низ
        squares[i+18] = new QPushButton( game.map[i+18]->name , this);
        squares[i+18]->setGeometry(1100-i*100 , 700, 100,100);
        squares[i+18]->setFont(font);
        connect(squares[i+18] , SIGNAL( clicked() ), this, SLOT( forAnyButton() ) );
    }
    for ( int i = 12 ; i < 18 ; i++ ){
        //вертикаль право
        squares[i] = new QPushButton( game.map[i]->name , this);
        squares[i]->setGeometry(1100, (i-11)*100, 100,100);
        squares[i]->setFont(font);
        connect(squares[i] , SIGNAL( clicked() ), this, SLOT( forAnyButton() ) );
        //вертикаль лево
        squares[i+18] = new QPushButton( game.map[i+18]->name , this);
        squares[i+18]->setGeometry(0, 700-(i-11)*100, 100,100);
        squares[i+18]->setFont(font);
        connect(squares[i+18] , SIGNAL( clicked() ), this, SLOT( forAnyButton() ) );
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
            wl->addLine( temp + "\n\n" , 2 );
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
