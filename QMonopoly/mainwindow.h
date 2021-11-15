#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QFont>
#include <QPixmap>
#include <QPalette>

#include "game.h"
#include "windowhelp.h"
#include "windowlogs.h"
#include "windowsettings.h"
#include "windowstart.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Game game;

private:
    WindowHelp *wh;
    WindowSettings *ws;
    WindowLogs *wl;
    WindowStart *start;

    QPushButton *diceButton;
    QPushButton *helpButton;
    QPushButton *setsButton;
    QPushButton *playersButtons[4];
    QPushButton *buyButtons[4];
    QPushButton *sellButtons[4];
    QPushButton *squares[36];

    QLabel *Llines[2];
    QLabel *Lbalance[4];
    QLabel *LtoEarn[4];

    void buttonsInit();
    void labelsInit();
    void windowsInit();

private slots:
    void forHelpButton();
    void forSettingsButton();
    void forAnyButton();
    void forBuyButtons();
    void forSellButtons();
    void forDiceButton();
};
#endif // MAINWINDOW_H
