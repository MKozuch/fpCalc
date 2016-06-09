#include "calculator.h"
#include <math.h>

Calculator::Calculator(QObject *parent) : QObject(parent)
{
    this->yRegister = 0;
    this->xRegister = 0;
    this->currentState = ACCUMULATE;
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
    default:
        break;
    }
    this->currentState = HOLD;

}

void Calculator::digitEntered(int digit)
{
    this->accumulate(digit);
    emit(this->display(this->xRegister));
}

void Calculator::commaEntered()
{
    this->isOperandDecimal=true;
}

void Calculator::clearClicked()
{
    this->currentState = ACCUMULATE;
    this->xRegister = 0;
    this->yRegister = 0;
    this->yRegisterFull = false;
    this->isOperandDecimal = false;
    this->selectedOperation = NOOP;
    emit(this->display(0));
}

void Calculator::negateClicked()
{
    this->xRegister = -this->xRegister;
    emit(this->display(xRegister));
}

void Calculator::sqrtClicked()
{
    this->xRegister = std::sqrt(this->xRegister);
    this->currentState = HOLD;
    emit(this->display(xRegister));
}

void Calculator::binaryOperatorClicked(int op)
{
    Operation operation = (Operation)op;
    emit(this->errorSignal(QString("Warning: major fuckup")));
}
