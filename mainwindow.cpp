#include <QApplication>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "calculator.h"

#include <QString>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->calc = new Calculator(this);

    //this->ui->display->display(QString("Error"));

    QWidget *digitBtnArr[] = {this->ui->digit0Btn,
                             this->ui->digit1Btn,
                             this->ui->digit2Btn,
                             this->ui->digit3Btn,
                             this->ui->digit4Btn,
                             this->ui->digit5Btn,
                             this->ui->digit6Btn,
                             this->ui->digit7Btn,
                             this->ui->digit8Btn,
                             this->ui->digit9Btn};
    for(int i=0; i<10; ++i){
        connect(digitBtnArr[i], SIGNAL(clicked()), &this->numericBtnSignalMapper, SLOT(map()));
        this->numericBtnSignalMapper.setMapping(digitBtnArr[i], i);
    }
    connect(&this->numericBtnSignalMapper, SIGNAL(mapped(int)), this->calc, SLOT(digitEntered(int)));

    connect(this->ui->negativeBtn, SIGNAL(clicked()), this->calc, SLOT(negateClicked()));
    connect(this->ui->sqrtBtn, SIGNAL(clicked()), this->calc, SLOT(sqrtClicked()));
    connect(this->ui->commaBtn, SIGNAL(clicked()), this->calc, SLOT(commaClicked()));
    connect(this->ui->clearBtn, SIGNAL(clicked()), this->calc, SLOT(clearClicked()));

    connect(this->ui->addBtn, SIGNAL(clicked()), &this->binaryOperationsSignalMapper, SLOT(map()));
    connect(this->ui->subtractBtn, SIGNAL(clicked()), &this->binaryOperationsSignalMapper, SLOT(map()));
    connect(this->ui->multiplyBtn, SIGNAL(clicked()), &this->binaryOperationsSignalMapper, SLOT(map()));
    connect(this->ui->divideBtn, SIGNAL(clicked()), &this->binaryOperationsSignalMapper, SLOT(map()));

    this->binaryOperationsSignalMapper.setMapping(this->ui->addBtn, Calculator::ADD);
    this->binaryOperationsSignalMapper.setMapping(this->ui->subtractBtn, Calculator::SUBTRACT);
    this->binaryOperationsSignalMapper.setMapping(this->ui->multiplyBtn, Calculator::MULTIPLY);
    this->binaryOperationsSignalMapper.setMapping(this->ui->divideBtn, Calculator::DIVIDE);
    connect(&this->binaryOperationsSignalMapper, SIGNAL(mapped(int)),
            this->calc, SLOT(binaryOperatorClicked(int)));


    connect(this->calc, SIGNAL(display(float)), this, SLOT(on_updateDisplay(float)));
    connect(this->calc, SIGNAL(errorSignal(QString)), this, SLOT(on_calcError(QString)));
}


MainWindow::~MainWindow()
{
    delete ui;
    delete calc;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_updateDisplay(float kk)
{
    this->ui->display->display(kk);
}

void MainWindow::on_calcError(QString errorMsg)
{
    this->ui->display->display(QString("Error"));
    QMessageBox::warning(this, QString("Error"), errorMsg);

}

