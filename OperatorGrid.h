#include "ArithmeticOperator.h"
#ifndef OPERATORGRID_H
#define OPERATORGRID_H

class OperatorGrid
{
    public:
        OperatorGrid(int rows,int cols);
        ~OperatorGrid();

        bool place_operator (ArithmeticOperator*);
        bool copyplace_operator (ArithmeticOperator*,int number,int tempxcenter,int tempycenter,int move_by,int key,char direction);
        void printer();
        void Gridfixer( int number);
        bool move_operator (int x,int y ,char direction,int move_by);
        void print_operators();


    private:

        int grid_rows;
        int grid_cols;
        char **grid ;
        int **tgrid;

        int num_operators;
        ArithmeticOperator *operators[MAX_OPERATOR_SIZE];
};

#endif // OPERATORGRID_H
