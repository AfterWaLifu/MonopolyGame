#include "windowstart.h"

WindowStart::WindowStart(QWidget *Main, QWidget *parent, Qt::WindowFlags f) : QWidget(parent , f)
{
    this->setGeometry(200,200, 300,160);
    this->setMaximumSize(QSize(300,160));
    this->setMinimumSize(QSize(300,160));
    setWindowTitle("Выберете начальные параметры");

    QString path = QCoreApplication::applicationDirPath();
    QPixmap iconPix( path.append( "\\resources\\start.png" ) );
    this->setWindowIcon( QIcon(iconPix) );

    letskekinggo = new QPushButton("Ok", this);
    connect( letskekinggo, SIGNAL(clicked()) , Main , SLOT(startThisGame()) );

    QLabel* labels[2];
    labels[0] = new QLabel("Количество игроков:",this);
    labels[1] = new QLabel("Набор правил      :",this);
    labels[0]->move(20 , 20);
    labels[1]->move(20 , 65);

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

    letskekinggo->setGeometry(20 , 110 , 260 , 30);
}
