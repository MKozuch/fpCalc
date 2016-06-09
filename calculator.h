#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>

class Calculator : public QObject
{
    Q_OBJECT

public:
    explicit Calculator(QObject *parent = 0);
    enum CalcState {ERROR, ACCUMULATE, RESULT, HOLD};
    enum Operation {NOOP, ADD, SUBTRACT, MULTIPLY, DIVIDE, NEGATE, SQRT, FIB};
    //enum UnaryOperations {NOOPERATION, NEGATE, SQRT, FIB};
    //enum BinaryOperation {ADD, SUBTRACT, MULTIPLY, DIVIDE};
    void accumulate(int);

private:
    double yRegister;
    double xRegister;
    CalcState currentState;
    bool isOperandDecimal;
    bool yRegisterFull;
    enum Operation selectedOperation;

    void calculate();
    double fib(int);


signals:
    void resultReady();
    void display(float);
    void errorSignal(QString);

public slots:
    void digitEntered(int);
    void commaEntered();
    void clearClicked();
    void negateClicked();
    void sqrtClicked();
//    void unaryOperatorClicked(UnaryOperations);
    void binaryOperatorClicked(int);


};

#endif // CALCULATOR_H
