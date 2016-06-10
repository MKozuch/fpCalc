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

    // connect MainWindow signals to Calculator slots
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
    connect(this->ui->commaBtn, SIGNAL(clicked()), this->calc, SLOT(commaEntered()));
    connect(this->ui->clearBtn, SIGNAL(clicked()), this->calc, SLOT(clearTriggered()));
    connect(this->ui->fibBtn, SIGNAL(clicked()), this->calc, SLOT(fibClicked()));

    connect(this->ui->addBtn, SIGNAL(clicked()), &this->operationSignalMapper, SLOT(map()));
    connect(this->ui->subtractBtn, SIGNAL(clicked()), &this->operationSignalMapper, SLOT(map()));
    connect(this->ui->multiplyBtn, SIGNAL(clicked()), &this->operationSignalMapper, SLOT(map()));
    connect(this->ui->divideBtn, SIGNAL(clicked()), &this->operationSignalMapper, SLOT(map()));
    //connect(this->ui->fibBtn, SIGNAL(clicked()), &this->operationSignalMapper, SLOT(map()));

    this->operationSignalMapper.setMapping(this->ui->addBtn, Calculator::ADD);
    this->operationSignalMapper.setMapping(this->ui->subtractBtn, Calculator::SUBTRACT);
    this->operationSignalMapper.setMapping(this->ui->multiplyBtn, Calculator::MULTIPLY);
    this->operationSignalMapper.setMapping(this->ui->divideBtn, Calculator::DIVIDE);
    //this->operationSignalMapper.setMapping(this->ui->fibBtn, Calculator::FIB);
    connect(&this->operationSignalMapper, SIGNAL(mapped(int)), this->calc, SLOT(binaryOperatorClicked(int)));

    connect(this->ui->equalBtn, SIGNAL(clicked()), this->calc, SLOT(equalSignTriggered()));

    connect(this, SIGNAL(medianListReady(QList<double>)), this->calc, SLOT(medianTriggered(QList<double>)));

    // connect calculator signals to MainWindow slots
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

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, QString("About"), "fpCalc by: MKozuch");
}

void MainWindow::on_updateDisplay(float num)
{
    this->ui->display->display(num);
}

void MainWindow::on_calcError(QString errorMsg)
{
    this->ui->display->display(QString("Error"));
    QMessageBox::warning(this, QString("Error"), errorMsg);

}

void MainWindow::on_medianBtn_clicked()
{
    auto medianDialog = new MedianInputDialog(this);
    if (medianDialog->exec()){
        emit(this->medianListReady(medianDialog->values));
    }
    delete medianDialog;
}
