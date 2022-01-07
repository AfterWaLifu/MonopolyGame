#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    windowsInit();

    start->show();
}

MainWindow::~MainWindow()
{

}

void MainWindow::buttonsInit()
{
    QFont *font = new QFont("Verdana", 14);

    diceButton = new QPushButton("Бросить куб",this);
    diceButton->setGeometry( 500 , 375 , 200 , 50 );
    diceButton->setFont(*font);
    connect( diceButton , SIGNAL( clicked() ) , this , SLOT( move() ) );

    font->setPointSize(12);

    helpButton = new QPushButton("Помощь", this);
    helpButton->setGeometry( 400 , 375 , 100 , 50 );
    helpButton->setFont(*font);
    connect(helpButton, SIGNAL(clicked()), this, SLOT(forHelpButton()));

    setsButton = new QPushButton("Настройки", this);
    setsButton->setGeometry( 700 , 375 , 100 , 50 );
    setsButton->setFont(*font);
    connect(setsButton, SIGNAL(clicked()), this, SLOT(forSettingsButton()));

    font->setPointSize(7);
    //кнопки по периметру
    for ( int i = 0 ; i < 12 ; i++ ){
        //горизонталь верх
        squares[i] = new QPushButton( game->map[i]->name ,this);
        squares[i]->setGeometry(i*100, 0, 100,100);
        squares[i]->setFont(*font);
        connect(squares[i] , SIGNAL( clicked() ), this, SLOT( forAnyButton() ) );
        //горизонталь низ
        squares[i+18] = new QPushButton( game->map[i+18]->name , this);
        squares[i+18]->setGeometry(1100-i*100 , 700, 100,100);
        squares[i+18]->setFont(*font);
        connect(squares[i+18] , SIGNAL( clicked() ), this, SLOT( forAnyButton() ) );
    }
    for ( int i = 12 ; i < 18 ; i++ ){
        //вертикаль право
        squares[i] = new QPushButton( game->map[i]->name , this);
        squares[i]->setGeometry(1100, (i-11)*100, 100,100);
        squares[i]->setFont(*font);
        connect(squares[i] , SIGNAL( clicked() ), this, SLOT( forAnyButton() ) );
        //вертикаль лево
        squares[i+18] = new QPushButton( game->map[i+18]->name , this);
        squares[i+18]->setGeometry(0, 700-(i-11)*100, 100,100);
        squares[i+18]->setFont(*font);
        connect(squares[i+18] , SIGNAL( clicked() ), this, SLOT( forAnyButton() ) );
    }

    font->setPointSize(14);

    //игроки покупки продажки
    for ( int i = 0 ; i < game->playersCount ; i++ ){
        buyButtons[i] = new QPushButton( "Купить" , this );
        buyButtons[i]->setGeometry( 110 + ( i % 2 * 780 ) , 210 + ( i / 2 * 300 ) , 200 , 80 );
        buyButtons[i]->setFont( *font );
        connect(buyButtons[i] , SIGNAL( clicked() ) , this , SLOT( forBuyButtons() ) );

        sellButtons[i] = new QPushButton( "Продать" , this );
        sellButtons[i]->setGeometry( 110 + ( i % 2 * 780 ) , 310 + ( i / 2 * 300 ) , 200 , 80 );
        sellButtons[i]->setFont( *font );
        connect(sellButtons[i] , SIGNAL( clicked() ) , this , SLOT( forSellButtons() ) );
    }

    delete font;
}

void MainWindow::labelsInit()
{
    QFont *font = new QFont();
    font->setFamily("Verdana");
    font->setPointSize(14);
    for ( int i = 0 ; i < game->playersCount ; i++ ){
        Lbalance[i] = new QLabel( QString::number(game->players[i]->getMoneyQ()) , this );
        Lbalance[i]->setFont(*font);
        Lbalance[i]->setGeometry(222 + ( i % 2 * 801 ) , 136 + ( i / 2 * 300 ) , 300, 20);

        LtoEarn[i] = new QLabel( QString::number(game->players[i]->toEarn + game->settings->moneyForCircle) , this );
        LtoEarn[i]->setFont(*font);
        LtoEarn[i]->setGeometry(222 + ( i % 2 * 801 ) , 162 + ( i / 2 * 300 ) , 100, 20);
    }
    delete font;
}

void MainWindow::windowsInit()
{
    wh = new WindowHelp( nullptr , Qt::Window | Qt::WindowMinimizeButtonHint);
    wl = new WindowLogs(nullptr , Qt::Window | Qt::WindowMinimizeButtonHint);
    ws = new WindowSettings(this , nullptr , Qt::Window | Qt::WindowMinimizeButtonHint);
    start = new WindowStart(this , nullptr , Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
}

void MainWindow::playersInit()
{
    for (int i = 0; i < game->playersCount ; i++ ){
        Lplayers[i] = new QLabel( this );
        Lplayers[i]->setGeometry( 5 + ( i % 2 * 50 ) , 5 + ( i / 2 * 50) , 40 , 40 );
        QString path = QCoreApplication::applicationDirPath();
        switch (i){
        case 0:
            path.append("\\resources\\players\\blue.png");
            break;
        case 1:
            path.append("\\resources\\players\\green.png");
            break;
        case 2:
            path.append("\\resources\\players\\red.png");
            break;
        case 3:
            path.append("\\resources\\players\\purple.png");
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
    timer->setInterval(20);
    connect( timer , SIGNAL( timeout() ) , this , SLOT( runforestrun() ) );
}

void MainWindow::tPlayersOwnsInit(){
    for (int i = 0 ; i < game->playersCount ; i++ ){
        TplayersOwns[i] = new QTextEdit(this);
        TplayersOwns[i]->setGeometry(330 + (i%2 * 275) ,110 + (i/2 * 320) ,265,260);
        TplayersOwns[i]->setPlainText("Список предприятий:\n");
        TplayersOwns[i]->setReadOnly(true);
    }
}

void MainWindow::startThisGame()
{
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

    start->hide();


    if (start->rules[1]->isChecked()){
        ws->jail->  setCurrentIndex(1);
        ws->train-> setCurrentIndex(1);
        ws->stock-> setCurrentIndex(1);
        ws->lenin-> setCurrentIndex(1);
        ws->social->setCurrentIndex(1);
        ws->worm->  setCurrentIndex(1);
        ws->dicesQ[0]->setChecked(true);
        ws->circle->setValue(500);
        ws->taxes->setValue(2);
    }
    ws->startLave->setValue(start->startMoney->value());
    game = new Game(start->players->value() , ws->startLave->value());

    buttonsInit();
    labelsInit();
    playersInit();
    tPlayersOwnsInit();
    timerInit();

    updateSettings();

    this->show();
    wl->show();
    this->activateWindow();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    wh->close();
    wl->close();
    ws->close();
    QWidget::closeEvent(event);
}
