#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <QString>
#include <QList>

class Calculator : public QObject
{
    Q_OBJECT

public:
    explicit Calculator(QObject *parent = 0);
    enum CalcState {ERROR, ACCUMULATE, RESULT, HOLD};
    enum Operation {NOOP, ADD, SUBTRACT, MULTIPLY, DIVIDE, NEGATE, SQRT, FIB};
    void accumulate(int);

private:
    friend class TestOf_calculator;
    double yRegister;
    double xRegister;
    CalcState currentState;
    bool isOperandDecimal;
    bool yRegisterFull;
    enum Operation selectedOperation;
    void refreshDisp();
    void calculate();
    long fib(int);
    void xRegisterPush();
    QString generateLogMessage(double, double, Operation, double);
    QString generateLogMessage(double, Operation, double);
    template <typename T> T median(QList<T>);


signals:
    void resultReady();
    void display(float);
    void errorSignal(QString);
    void logSignal(QString);

public slots:
    void digitEntered(int);
    void commaEntered();
    void clearTriggered();
    void negateClicked();
    void sqrtClicked();
    void fibClicked();
//    void unaryOperatorClicked(UnaryOperations);
    void binaryOperatorClicked(int);
    void equalSignTriggered();
    void medianTriggered(QList<double>);

};

#endif // CALCULATOR_H
