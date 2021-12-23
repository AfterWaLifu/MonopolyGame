#include "windowsettings.h"

WindowSettings::WindowSettings(QWidget *parent, Qt::WindowFlags f) : QWidget(parent , f)
{
    this->setGeometry(900,100, 400,240);
    this->setMaximumSize(QSize(400,240));
    this->setMinimumSize(QSize(400,240));
    setWindowTitle("Настройки");
    QString path = QCoreApplication::applicationDirPath();
    QPixmap iconPix( path.append( "\\resources\\sets.png" ) );
    this->setWindowIcon( QIcon(iconPix) );
    setUp();
}

void WindowSettings::applySettings()
{

}

void WindowSettings::setUp()
{
    sets = new Settings();

    jail     = new QComboBox(this);
    train    = new QComboBox(this);
    stock    = new QComboBox(this);
    lenin    = new QComboBox(this);
    social   = new QComboBox(this);
    worm     = new QComboBox(this);
    dicesQ[0]   = new QRadioButton("1",this);
    dicesQ[1]   = new QRadioButton("2",this);

    taxes   = new QSpinBox(this);
    circle  = new QSpinBox(this);

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
    stock->addItem("Пропуск хода");
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

    QLabel* ltax = new QLabel("Налоговая, %:", this);
    QLabel* lcir = new QLabel("Бонус за круг:", this);
    QLabel* ldic = new QLabel("Количество кубиков:", this);
    ltax->move(20,130);
    lcir->move(210,130);
    ldic->move(20,165);

    taxes->setGeometry(110, 130 , 80 , 20);
    circle->setGeometry(290, 130 , 90 , 20);
    circle->setMaximum(1000);

    dicesQ[0]->move(220,165);
    dicesQ[1]->move(350,165);

    apply->setGeometry(20 , 200 , 170 , 20);
    newGame->setGeometry(210 , 200 , 170 , 20);

}
