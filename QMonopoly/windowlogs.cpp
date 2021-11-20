#include "windowlogs.h"

WindowLogs::WindowLogs(QWidget *parent, Qt::WindowFlags f) : QWidget(parent , f)
{
    this->setGeometry(1302,100, 300,800);
    this->setMaximumSize(QSize(300,800));
    this->setMinimumSize(QSize(300,800));
    setWindowTitle("История действий");

    logs = new QTextEdit(this);
    logs->setGeometry(0,0,300,800);
}

void WindowLogs::addLine(QString string)
{

}
