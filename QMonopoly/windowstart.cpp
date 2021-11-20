#include "windowstart.h"

WindowStart::WindowStart(QWidget *Main, QWidget *parent, Qt::WindowFlags f) : QWidget(parent , f)
{
    this->setGeometry(200,200, 500,500);
    this->setMaximumSize(QSize(500,500));
    this->setMinimumSize(QSize(500,500));
    setWindowTitle("Выберете начальные параметры");

    button = new QPushButton("Ok", this);
    connect( button, SIGNAL(clicked()) , Main , SLOT(showMe()) );
}
