#include "testof_calculator.h"

void TestOf_calculator::testOf_fib()
{
    int fibos[] = {0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181};
    for(int i=0; i<20; ++i){
        QVERIFY(this->calc.fib(i) == fibos[i]);
    }
}

QTEST_MAIN(TestOf_calculator)
//#include "testof_fib.moc"
