#include "windowhelp.h"

WindowHelp::WindowHelp(QWidget *parent, Qt::WindowFlags f) : QWidget(parent , f)
{
    this->setGeometry(100,100, 500,500);
    this->setMaximumSize(QSize(500,500));
    this->setMinimumSize(QSize(500,500));
    setWindowTitle("Помощь");

    QString path = QCoreApplication::applicationDirPath();
    QPixmap iconPix( path.append( "\\resources\\help.ico" ) );
    this->setWindowIcon( QIcon(iconPix) );
}
