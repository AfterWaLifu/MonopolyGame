#include "windowsettings.h"

WindowSettings::WindowSettings(QWidget *parent, Qt::WindowFlags f) : QWidget(parent , f)
{
    this->setGeometry(200,200, 500,500);
    this->setMaximumSize(QSize(500,500));
    this->setMinimumSize(QSize(500,500));
    setWindowTitle("Настройки");
}
