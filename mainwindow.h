#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>

#include "calculator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Calculator *calc;
    QSignalMapper numericBtnSignalMapper;
    QSignalMapper unaryOperationsSignalMapper;
    QSignalMapper binaryOperationsSignalMapper;


private slots:
    void on_actionExit_triggered();
    void on_updateDisplay(float);
    void on_calcError(QString);

signals:
    digitBtnClicked(int);
    commaBtnClicked();
};

#endif // MAINWINDOW_H
