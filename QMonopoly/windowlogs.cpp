#include "windowlogs.h"

WindowLogs::WindowLogs(QWidget *parent, Qt::WindowFlags f) : QWidget(parent , f)
{
    this->setGeometry(1302,100, 300,800);
    this->setMaximumSize(QSize(300,800));
    this->setMinimumSize(QSize(300,800));
    setWindowTitle("История действий");

    logs = new QPlainTextEdit(this);
    logs->setGeometry(0,0,300,800);
    logs->setReadOnly(true);

    QString path = QCoreApplication::applicationDirPath();
    QPixmap iconPix( path.append( "\\resources\\logs.ico" ) );
    this->setWindowIcon( QIcon(iconPix) );
}

void WindowLogs::addLine(QString string, int count)
{
    countOf += count;
    string += logs->document()->toPlainText();

    if (countOf > 50){
        for (int i = 0 ; i < count ; i++){
            string = string.left( string.lastIndexOf('\n') );
        }
        countOf -= count;
    }

    logs->setPlainText(string);
}
