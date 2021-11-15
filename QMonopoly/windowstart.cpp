#include "windowstart.h"

WindowStart::WindowStart(QWidget *Main, QWidget *parent) : QWidget(parent)
{
    this->setGeometry(200,200, 500,500);
    setWindowTitle("Выберете начальные параметры");

    button = new QPushButton("Ok", this);
    connect( button, SIGNAL(clicked()) , Main , SLOT(showMe()) );
}
