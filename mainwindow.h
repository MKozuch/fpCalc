#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QList>

#include "calculator.h"
#include "medianinputdialog.h"

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
    QSignalMapper operationSignalMapper;


private slots:
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    void on_updateDisplay(float);
    void on_calcError(QString);
    void on_medianBtn_clicked();

signals:
    void digitBtnClicked(int);
    void commaBtnClicked();
    void medianListReady(QList<double>);
};

#endif // MAINWINDOW_H
