#include "ArithmeticOperator.h"
#ifndef OPERATORGRID_H
#define OPERATORGRID_H


class OperatorGrid
{
    public:
        OperatorGrid(int rows,int cols);
        ~OperatorGrid();

        bool place_operator (ArithmeticOperator*);
        void printer();
       /* bool move_operator (int x,int y ;char direction,int move_by);
        void print_operators;

*/
    private:
        int MAX_OPERATOR_SIZE;
        int grid_rows;
        int grid_cols;
        char **grid ;
        int **tgrid;

        int num_operators;
        ArithmeticOperator *operators[];
};

#endif // OPERATORGRID_H
