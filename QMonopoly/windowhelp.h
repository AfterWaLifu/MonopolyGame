#pragma once

#include <QWidget>
#include <QLabel>

class WindowHelp : public QWidget
{
    Q_OBJECT
public:
    explicit WindowHelp(QWidget *parent = nullptr);

private:
    QLabel *help;

signals:

};

