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
#include <QTimer>

#include "game.h"
#include "windowhelp.h"
#include "windowlogs.h"
#include "windowsettings.h"
#include "windowstart.h"

class WindowStart;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Game* game;

private:
    WindowHelp *wh;
    WindowSettings *ws;
    WindowLogs *wl;
    WindowStart *start;

    QPushButton *diceButton;
    QPushButton *helpButton;
    QPushButton *setsButton;
    QPushButton *buyButtons[4];
    QPushButton *sellButtons[4];
    QPushButton *squares[36];

    QLabel *Lbalance[4];
    QLabel *LtoEarn[4];
    QLabel *Lplayers[4];

    QTextEdit *TplayersOwns[4];

    QTimer *timer;

    void buttonsInit();
    void labelsInit();
    void windowsInit();
    void playersInit();
    void timerInit();
    void buttonsEnable();
    void buttonsDisable();
    void tPlayersOwnsInit();

    QPoint makeCoords(int pos);
    QPoint addCoords(int p);

    void updFigureInfo();
    void checkForSpecialSquares();

    void updateSettings();

private slots:
    void forHelpButton();
    void forSettingsButton();
    void forAnyButton();
    void forBuyButtons();
    void forSellButtons();
    void move(int q = 0);
    void runforestrun();

public slots:
    void showMe();
protected:
    void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
