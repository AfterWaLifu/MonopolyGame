#pragma once

#include <QPlainTextEdit>
#include <QWidget>

class WindowLogs : public QWidget
{
    Q_OBJECT
public:
    explicit WindowLogs(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QPlainTextEdit *logs;
    int countOf;

    void addLine(QString string, int count);

signals:

};

