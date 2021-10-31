#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    this->setGeometry(10,100,1600,900);
    this->setMaximumSize(1600,900);
    this->setMinimumSize(1600,900);

    init();
}

MainWindow::~MainWindow()
{
    diceButton->~QPushButton();
    helpButton->~QPushButton();
    setsButton->~QPushButton();
}

void MainWindow::init()
{
    diceButton = new QPushButton("Бросить куб",this);
    diceButton->setGeometry( 700 , 400 , 200 , 50 );

    helpButton = new QPushButton("Помощь", this);
    helpButton->setGeometry( 700 , 450 , 100 , 50 );

    setsButton = new QPushButton("Настройки", this);
    setsButton->setGeometry( 800 , 450 , 100 , 50 );
}
