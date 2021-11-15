#ifndef WINDOWSTART_H
#define WINDOWSTART_H

#include <QWidget>
#include <QPushButton>
#include <mainwindow.h>

class WindowStart : public QWidget
{
    Q_OBJECT
public:
    explicit WindowStart(QWidget *main, QWidget *parent = nullptr);

    QPushButton *button;

signals:

};

#endif // WINDOWSTART_H
