#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    this->setGeometry(10,100,1200,800);
    this->setMaximumSize(1200,800);
    this->setMinimumSize(1200,800);

    labelsInit();
    buttonsInit();
}

MainWindow::~MainWindow()
{
    diceButton->~QPushButton();
    helpButton->~QPushButton();
    setsButton->~QPushButton();

    for (int i = 0; i < 36 ; i++){
        squares[i]->~QPushButton();
    }
    for (int i = 0; i < 4 ; i++ ){
        sellButtons[i]->~QPushButton();
        buyButtons[i]->~QPushButton();
        Lbalance[i]->~QLabel();
        LtoEarn[i]->~QLabel();
    }
    for (int i = 0 ; i < 2 ; i++ ){
        Llines[i]->~QLabel();
    }
}

void MainWindow::buttonsInit()
{
    QFont font("Verdana", 14);

    diceButton = new QPushButton("Бросить куб",this);
    diceButton->setGeometry( 500 , 350 , 200 , 50 );
    diceButton->setFont(font);

    font.setPointSize(12);

    helpButton = new QPushButton("Помощь", this);
    helpButton->setGeometry( 500 , 400 , 100 , 50 );
    helpButton->setFont(font);

    setsButton = new QPushButton("Настройки", this);
    setsButton->setGeometry( 600 , 400 , 100 , 50 );
    setsButton->setFont(font);

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

    //покупки продажки
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
        Lbalance[i] = new QLabel( QString::number(i) , this );
        Lbalance[i]->setFont(font);
        Lbalance[i]->setGeometry(180 + ( i % 2 * 850 ) , 140 + ( i / 2 * 300 ) , 300, 20);

        LtoEarn[i] = new QLabel( QString::number(i) , this );
        LtoEarn[i]->setFont(font);
        LtoEarn[i]->setGeometry(180 + ( i % 2 * 850 ) , 170 + ( i / 2 * 300 ) , 100, 20);
    }
}