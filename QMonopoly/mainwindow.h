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

/*!
 * \brief The MainWindow класс основного окна программы
 */
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
    QPushButton *squares[36];
    QPushButton *buyButtons[4];
    QPushButton *sellButtons[4];

    /*!
     * \brief init Функция инициализации основного окна
     */
    void init();
};
#endif // MAINWINDOW_H
