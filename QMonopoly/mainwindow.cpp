#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    this->setGeometry(10,100,1200,800);
    this->setMaximumSize(1200,800);
    this->setMinimumSize(1200,800);

    init();
}

MainWindow::~MainWindow()
{
    diceButton->~QPushButton();
    helpButton->~QPushButton();
    setsButton->~QPushButton();

    for (int i = 0; i < 36 ; i++){
        squares[i]->~QPushButton();
    }
}

void MainWindow::init()
{
    QFont font("Verdana", 12);

    diceButton = new QPushButton("Бросить куб",this);
    diceButton->setGeometry( 500 , 350 , 200 , 50 );
    diceButton->setFont(font);

    helpButton = new QPushButton("Помощь", this);
    helpButton->setGeometry( 500 , 400 , 100 , 50 );
    helpButton->setFont(font);

    setsButton = new QPushButton("Настройки", this);
    setsButton->setGeometry( 600 , 400 , 100 , 50 );
    setsButton->setFont(font);

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
}
