#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <QString>
#include <QList>
#include <QMap>

class Calculator : public QObject
{
    Q_OBJECT

public:
    explicit Calculator(QObject *parent = 0);
    enum CalcState {ERROR, ACCUMULATE, RESULT, HOLD};
    enum Operation {NOOP, ADD, SUBTRACT, MULTIPLY, DIVIDE, NEGATE, SQRT, FIB, MEDIAN};
    QMap<Operation, QString> operationNameDict;
    void accumulate(int);

private:
    friend class TestOf_calculator;
    double yRegister; // this variable holds left operand value
    double xRegister; // this variable holds display contents and right operand
    CalcState currentState;
    bool isOperandDecimal; // is true when variable in xRegister has decimal part
    bool yRegisterFull;
    enum Operation selectedOperation;
    void refreshDisp();
    void calculate();
    long fib(int);
    void xRegisterPush(); // push contents of register X to register Y, clear register X
    QString generateLogMessage(double, double, Operation, double);
    QString generateLogMessage(double, Operation, double);
    template <typename T> T median(QList<T>);

signals:
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
    void binaryOperatorClicked(int); // services all binary operations
    void equalSignTriggered();
    void medianTriggered(QList<double>);
};

#endif // CALCULATOR_H
