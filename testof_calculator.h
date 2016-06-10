#ifndef TESTOF_CALCULATOR_H
#define TESTOF_CALCULATOR_H

#include <QObject>
#include <QtTest/QtTest>

#include "calculator.h"

class TestOf_calculator : public QObject
{
    Q_OBJECT

private:
    Calculator calc;

private slots:
    void initTestCase();
    void testOf_fib();
    void cleanupTestCase();
};

#endif // TESTOF_CALCULATOR_H
