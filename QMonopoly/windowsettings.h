#pragma once

#include <QWidget>
#include <QCoreApplication>
#include <QIcon>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QLayout>
#include <QSpinBox>
#include <QComboBox>
#include "settings.h"

class WindowSettings : public QWidget
{
    Q_OBJECT
public:
    explicit WindowSettings(QWidget* mw, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QWidget* motherWindow;

    QLabel* ltax;
    QLabel* lcir;
    QLabel* ldic;
    QLabel* lsts;

    QComboBox* jail;
    QComboBox* train;
    QComboBox* stock;
    QComboBox* lenin;
    QComboBox* social;
    QComboBox* worm;

    QRadioButton* dicesQ[2];

    QSpinBox* taxes;
    QSpinBox* circle;
    QSpinBox* startLave;

    QPushButton *apply;
    QPushButton *newGame;

private:
    void setUp();

signals:

};
