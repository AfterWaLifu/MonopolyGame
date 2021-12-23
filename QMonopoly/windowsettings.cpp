#include "windowsettings.h"

WindowSettings::WindowSettings(QWidget *parent, Qt::WindowFlags f) : QWidget(parent , f)
{
    this->setGeometry(800,100, 500,500);
    this->setMaximumSize(QSize(500,500));
    this->setMinimumSize(QSize(500,500));
    setWindowTitle("Настройки");
    QString path = QCoreApplication::applicationDirPath();
    QPixmap iconPix( path.append( "\\resources\\sets.png" ) );
    this->setWindowIcon( QIcon(iconPix) );
    setUp();
}

void WindowSettings::setUp()
{

}
