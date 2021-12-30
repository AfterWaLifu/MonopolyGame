#ifndef WINDOWSTART_H
#define WINDOWSTART_H

#include <QWidget>
#include <QPushButton>
#include <mainwindow.h>
#include <QCoreApplication>
#include <QIcon>

class WindowStart : public QWidget
{
    Q_OBJECT
public:
    explicit WindowStart(QWidget *main, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QLabel* labels[3];

    QPushButton *letskekinggo;

    QSpinBox* players;
    QRadioButton* rules[2];
    QSpinBox* startMoney;

signals:

};

#endif // WINDOWSTART_H
