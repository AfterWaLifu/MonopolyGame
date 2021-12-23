#pragma once

#include <QWidget>
#include <QCoreApplication>
#include <QIcon>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QSpinBox>
#include <QComboBox>
#include "settings.h"

class WindowSettings : public QWidget
{
    Q_OBJECT
public:
    explicit WindowSettings(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    Settings *sets;

private:

    QComboBox* jail;
    QComboBox* train;
    QComboBox* stock;
    QComboBox* lenin;
    QComboBox* social;
    QComboBox* worm;
    QComboBox* dicesQ;

    QSpinBox* taxes;
    QSpinBox* circle;

    QPushButton *apply;
    QPushButton *newGame;

    void setUp();

signals:

};
