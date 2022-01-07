#include "windowsettings.h"

WindowSettings::WindowSettings(QWidget* mw, QWidget *parent, Qt::WindowFlags f) : QWidget(parent , f)
{
    motherWindow = mw;
    this->setGeometry(650,100, 650,285);
    this->setMaximumSize(QSize(650,285));
    this->setMinimumSize(QSize(650,285));
    setWindowTitle("Настройки");
    QString path = QCoreApplication::applicationDirPath();
    QPixmap iconPix( path.append( "\\resources\\sets.png" ) );
    this->setWindowIcon( QIcon(iconPix) );
    setUp();
}

void WindowSettings::setUp()
{
    jail     = new QComboBox(this);
    train    = new QComboBox(this);
    stock    = new QComboBox(this);
    lenin    = new QComboBox(this);
    social   = new QComboBox(this);
    worm     = new QComboBox(this);
    dicesQ[0]   = new QRadioButton("1",this);
    dicesQ[1]   = new QRadioButton("2",this);

    taxes       = new QSpinBox(this);
    circle      = new QSpinBox(this);
    startLave   = new QSpinBox(this);

    apply   = new QPushButton("Принять",this);
    newGame = new QPushButton("Новая игра",this);

    jail->addItem("Тюрьма");
    jail->addItem("Штраф");
    jail->addItem("Повторный бросок");
    jail->addItem("Ничего");
    jail->setGeometry(20,15,170,20);

    train->addItem("Ж/д Вокзал, 3 станции");
    train->addItem("+1, +2 и +3 вместо станций");
    train->addItem("Повторный бросок");
    train->addItem("Ничего");
    train->setGeometry(210,15,170,20);

    stock->addItem("Биржа 3d6 против PC");
    stock->addItem("Пропуск хода х2");
    stock->addItem("Ничего");
    stock->setGeometry(20 , 50 , 170 , 20);

    lenin->addItem("Революция (потеря пр.)");
    lenin->addItem("Штраф (цена дорогого пр.)");
    lenin->addItem("Ничего");
    lenin->setGeometry(210 , 50 , 170 , 20);

    social->addItem("Соц. банк/казна");
    social->addItem("Отдать/взять валюты");
    social->addItem("Ничего");
    social->setGeometry(20 , 85 , 170 , 20);

    worm->addItem("Червоточина");
    worm->addItem("6 шагов назад");
    worm->addItem("Ничего");
    worm->setGeometry(210 , 85 , 170 , 20);

    ltax = new QLabel("Налоговая, %:", this);
    lcir = new QLabel("Бонус за круг:", this);
    lsts = new QLabel("Стартовая сумма:" , this);
    ldic = new QLabel("Количество кубиков:", this);
    ltax->move(20,130);
    lcir->move(210,130);
    lsts->move(20,165);
    ldic->move(20,200);

    taxes->setGeometry(110, 130 , 80 , 20);
    taxes->setValue(7);
    circle->setGeometry(290, 130 , 90 , 20);
    circle->setMaximum(1000);
    circle->setValue(100);
    startLave->setGeometry(210,165 , 170 , 20);
    startLave->setMaximum(10000);
    startLave->setValue(300);

    dicesQ[0]->move(220,200);
    dicesQ[1]->move(350,200);
    dicesQ[1]->setChecked(true);

    apply->setGeometry(20 , 245 , 170 , 20);
    connect( apply , SIGNAL(clicked()) , motherWindow , SLOT( updateSettings() ) );
    newGame->setGeometry(210 , 245 , 170 , 20);
    connect( newGame , SIGNAL(clicked()) , motherWindow , SLOT(startNewGame()));

    availableSkins[0] = "blue.png";
    availableSkins[1] = "green.png";
    availableSkins[2] = "red.png";
    availableSkins[3] = "purple.png";
    availableSkins[4] = "M1.png";
    availableSkins[5] = "M2.png";
    availableSkins[6] = "M3.png";
    availableSkins[7] = "M4.png";
    availableSkins[8] = "Boss0.png";
    availableSkins[9] = "Boss1.png";
    availableSkins[10] ="Boss2.png";
    availableSkins[11] ="Boss3.png";
    availableSkins[12] ="Boss4.png";

    choosenSkins[0] = 0;
    choosenSkins[1] = 1;
    choosenSkins[2] = 2;
    choosenSkins[3] = 3;

    choosingPlayer = new QComboBox(this);
    choosingPlayer->setGeometry( 430 , 15 , 160 , 25 );
    choosingPlayer->addItem("Игрок 1");
    choosingPlayer->addItem("Игрок 2");
    choosingPlayer->addItem("Игрок 3");
    choosingPlayer->addItem("Игрок 4");
    choosingPlayer->setCurrentIndex(0);
    connect( choosingPlayer , SIGNAL(  ) , this , SLOT( changedChoosingPlayer() ) ) ;

    for (int i = 0 ; i < 13 ; i++ ){
        skins[i] = new QPushButton(this);
        skins[i]->setAutoFillBackground(true);
        skins[i]->setGeometry( 430 + ((i%4)*40) , 55 + ((i/4)*40) , 40 , 40 );
        connect( skins[i] , SIGNAL( clicked() ) , motherWindow , SLOT( updateSkin() ) ) ;
        QString path = QCoreApplication::applicationDirPath();
        path.append( "\\resources\\players\\" + availableSkins[i] );
        QPixmap pix(path);
        skins[i]->setIcon( pix );
    }
}
