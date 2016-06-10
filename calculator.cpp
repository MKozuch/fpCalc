#include "calculator.h"
#include <math.h>
#include <algorithm>

Calculator::Calculator(QObject *parent) : QObject(parent)
{
    this->clearTriggered();
    this->operationNameDict[ADD] = "Addition";
    this->operationNameDict[SUBTRACT] = "Subtraction";
    this->operationNameDict[MULTIPLY] = "Multiplication";
    this->operationNameDict[DIVIDE] = "Division";
    this->operationNameDict[NEGATE] = "Negation";
    this->operationNameDict[SQRT] = "Square root";
    this->operationNameDict[FIB] = "Fibonacci";
    this->operationNameDict[MEDIAN] = "Median";
}

void Calculator::accumulate(int digit)
{
    if(this->currentState == ACCUMULATE){
        static int decimalPlace = 0;
        digit = (this->xRegister >= 0) ? digit : -digit;
        if(!this->isOperandDecimal){
            this->xRegister *= 10;
            this->xRegister += digit;
            decimalPlace = 0;
        }
        else{
            decimalPlace += 1;
            this->xRegister += digit / std::pow(10, decimalPlace);
        }
    }
    else if(this->currentState == HOLD){
        this->xRegister = digit;
        this->currentState = ACCUMULATE;
    }
}

void Calculator::calculate(){
    switch(this->selectedOperation){
    case(ADD):
        xRegister = this->xRegister + this->yRegister;
        break;
    case(SUBTRACT):
        xRegister = this->yRegister - this->xRegister;
        break;
    case(MULTIPLY):
        xRegister = this->yRegister * this->xRegister;
        break;
    case(DIVIDE):
        xRegister = this->yRegister / this->xRegister;
        break;
    case(FIB):
        xRegister = this->fib(int(this->xRegister));
        break;
    default:
        break;
    }
    this->currentState = HOLD;
    this->selectedOperation = NOOP;
    this->yRegisterFull = false;
    this->refreshDisp();
}

void Calculator::digitEntered(int digit)
{
    this->accumulate(digit);
    this->refreshDisp();
}

void Calculator::commaEntered()
{
    this->isOperandDecimal=true;
}

void Calculator::clearTriggered()
{
    this->currentState = ACCUMULATE;
    this->xRegister = 0;
    this->yRegister = 0;
    this->yRegisterFull = false;
    this->isOperandDecimal = false;
    this->selectedOperation = NOOP;
    this->refreshDisp();
}

void Calculator::negateClicked()
{
    this->xRegister = -this->xRegister;
    this->refreshDisp();
}

void Calculator::sqrtClicked()
{
    if(this->xRegister<0) emit(this->errorSignal("Cannot sqrt a negative number"));
    else{
        this->xRegister = std::sqrt(this->xRegister);
        this->currentState = HOLD;
    }
    this->refreshDisp();
}

void Calculator::fibClicked()
{
    if(this->xRegister<0) emit(this->errorSignal("Cannot fib a negative number"));
    else if(this->xRegister - std::floor(this->xRegister)) emit(this->errorSignal("Cannot fib a non-integer"));
    else{
        this->xRegister = this->fib((int)xRegister);
        currentState = HOLD;
    }
    this->refreshDisp();
}

void Calculator::binaryOperatorClicked(int op)
{
    Operation operation = (Operation)op;
    this->selectedOperation = operation;
    if(this->yRegisterFull){
        //this->calculate();
    }
    else{
        this->xRegisterPush();
    }
    //this->refreshDisp();
}

void Calculator::equalSignTriggered()
{
    this->calculate();
    this->refreshDisp();
}

void Calculator::refreshDisp()
{
    emit(this->display(xRegister));
}

void Calculator::xRegisterPush()
{
    this->yRegister = this->xRegister;
    this->yRegisterFull = true;
    this->xRegister = 0;
    this->isOperandDecimal = false;
}

long Calculator::fib(int i){
    if(i==0) return 0;
    else if(i==1) return 1;
    else return fib(i-2)+fib(i-1);
}

void Calculator::medianTriggered(QList<double> valList)
{
    if(valList.length()==0) emit(this->errorSignal("Must be a non-zero length list"));
    else this->xRegister = median(valList);
    this->refreshDisp();
}

template <typename T> T Calculator::median(QList<T> argList)
{
    std::sort(argList.begin(), argList.end());
    auto len = argList.length();
    if (len == 0) return 0;
    else if(len%2 == 0) return((argList[len/2-1] + argList[(len/2)])/2);
    else return(argList[(len-1)/2]);
}

QString Calculator::generateLogMessage(double larg, double rarg, Operation operation, double result)
 {
    QString message = QString::number(larg);
    message.append(QString("; "));
    message.append(QString::number(rarg));
    message.append(QString("; "));
    message.append(this->operationNameDict[operation]);
    message.append(QString("; "));
    message.append(QString::number(result));
    message.append(QString("\n"));
    return message;
 }

QString Calculator::generateLogMessage(double arg, Operation operation, double result)
{
    QString message = QString::number(arg);
    message.append(QString("; "));
    message.append(this->operationNameDict[operation]);
    message.append(QString("; "));
    message.append(QString::number(result));
    message.append(QString("\n"));
    return message;
}
