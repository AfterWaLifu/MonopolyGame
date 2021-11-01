#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QFont>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QPushButton *diceButton;
    QPushButton *helpButton;
    QPushButton *setsButton;
    QPushButton *buyButtons[4];
    QPushButton *sellButtons[4];
    QPushButton *squares[36];

    QLabel *Llines[2];
    QLabel *Lbalance[4];
    QLabel *LtoEarn[4];

    void buttonsInit();
    void labelsInit();
};
#endif // MAINWINDOW_H
