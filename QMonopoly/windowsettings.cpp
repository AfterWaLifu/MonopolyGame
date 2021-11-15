#include "windowsettings.h"

WindowSettings::WindowSettings(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(200,200, 500,500);
    setWindowTitle("Настройки");
}
