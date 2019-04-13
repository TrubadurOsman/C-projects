#include "Operator.h"

#ifndef ARITHMETICOPERATOR_H
#define ARITHMETICOPERATOR_H


class ArithmeticOperator:public Operator
{
    public:
        ArithmeticOperator(int x,int y ,int size,char sign);

        char get_sign();

    private:
     char sign ;
};

#endif // ARITHMETICOPERATOR_H
