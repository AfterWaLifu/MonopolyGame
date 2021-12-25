#include "windowhelp.h"

WindowHelp::WindowHelp(QWidget *parent, Qt::WindowFlags f) : QWidget(parent , f)
{
    this->setGeometry(100,100, 1109,637);
    this->setMaximumSize(QSize(1109,637));
    this->setMinimumSize(QSize(1109,637));
    setWindowTitle("Помощь");

    QString path = QCoreApplication::applicationDirPath();
    QPixmap pix( path.append( "\\resources\\help.ico" ) );
    this->setWindowIcon( QIcon(pix) );


    path = QCoreApplication::applicationDirPath();
    QPixmap heplPix(path.append("\\resources\\help.png"));

    hepl = new QLabel(this);
    hepl->setGeometry(0,0, 1109 , 637);
    hepl->setPixmap(heplPix);
}
