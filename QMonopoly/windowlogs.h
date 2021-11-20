#pragma once

#include <QTextEdit>
#include <QWidget>

class WindowLogs : public QWidget
{
    Q_OBJECT
public:
    explicit WindowLogs(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QTextEdit *logs;

    void addLine(QString string);

signals:

};

