#include "windowstart.h"

WindowStart::WindowStart(QWidget *Main, QWidget *parent, Qt::WindowFlags f) : QWidget(parent , f)
{
    this->setMaximumSize(QSize(300,190));
    this->setMinimumSize(QSize(300,190));
    setWindowTitle("QMonopoly");

    QString path = QCoreApplication::applicationDirPath();
    QPixmap iconPix( path.append( "\\resources\\start.png" ) );
    this->setWindowIcon( QIcon(iconPix) );

    letskekinggo = new QPushButton("Ok", this);
    connect( letskekinggo, SIGNAL(clicked()) , Main , SLOT(startThisGame()) );

    labels[0] = new QLabel("Количество игроков:" , this);
    labels[1] = new QLabel("Набор правил      :" , this);
    labels[2] = new QLabel("Начальный баланс  :" , this);
    labels[0]->move(20 , 20);
    labels[1]->move(20 , 65);
    labels[2]->move(20 , 110);

    players = new QSpinBox(this);
    players->setGeometry( 140 , 20 , 140 , 20 );
    players->setMaximum(4);
    players->setMinimum(2);
    players->setValue(4);


    rules[0] = new QRadioButton("Полные", this);
    rules[1] = new QRadioButton("Простые", this);
    rules[0]->move(140 , 55);
    rules[1]->move(140 , 75);
    rules[0]->setChecked(true);

    startMoney = new QSpinBox(this);
    startMoney->setGeometry( 140 , 110 , 140 , 20 );
    startMoney->setMaximum(10000);
    startMoney->setValue(300);

    letskekinggo->setGeometry(20 , 145 , 260 , 30);
}
