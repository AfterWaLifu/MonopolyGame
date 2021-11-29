#pragma once

#include <QWidget>
#include <QCoreApplication>
#include <QIcon>

class WindowSettings : public QWidget
{
    Q_OBJECT
public:
    explicit WindowSettings(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

signals:

};
