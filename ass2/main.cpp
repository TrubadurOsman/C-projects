#include <iostream>
#include "Operator.h"
#include "OperatorGrid.h"
#include "ArithmeticOperator.h"

using namespace std;

OperatorGrid ::OperatorGrid(int rows, int cols)
{
    MAX_OPERATOR_SIZE = 20;
    num_operators = 0;
    grid_rows = rows;
    grid_cols = cols;

    grid = new char *[rows];
    for (int i = 0; i < rows; i++)
    {
        grid[i] = new char[cols];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {

            grid[i][j] = '0';
        }
    }

    tgrid = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        tgrid[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {

            tgrid[i][j] = 0;
        }
    }
}
void OperatorGrid::printer()
{
    for (int i = 0; i < grid_rows; i++)
    {
        for (int j = 0; j < grid_cols; j++)
        {

            cout << grid[i][j];
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < grid_rows; i++)
    {
        for (int j = 0; j < grid_cols; j++)
        {

            cout << tgrid[i][j];
        }
        cout << endl;
    }
}
//gridfixer
void OperatorGrid::Gridfixer(int number)
{

    for (int i = 0; i < grid_rows; i++)
    {
        for (int j = 0; j < grid_cols; j++)
        {

            if (tgrid[i][j] == number)
                tgrid[i][j] = 0;
            if (tgrid[i][j] == 0)
                grid[i][j] = '0';
        }
    }
}

OperatorGrid::~OperatorGrid()
{

    for (int i = 0; i < grid_cols; ++i)
    {

        delete[] grid[i];
    }
    delete[] grid;
}
//BOOOOO
bool OperatorGrid::place_operator(ArithmeticOperator *A)
{
    num_operators += 1;
    operators[num_operators] = A;
    int bordererror = 0;
    int conflicterror = 0;

    int tempx = A->get_x() - 1;
    int tempy = A->get_y() - 1;
    int tempsize = A->get_size();

    if (A->get_sign() == '-')
    { //minus

        for (int i = 0; i < tempsize + 1; i++)
        {

            if (tempy + i + 1 <= grid_cols)
            { //sağa bakma
                if (tgrid[tempx][tempy + i] == 0)
                {
                    tgrid[tempx][tempy + i] = num_operators;
                    grid[tempx][tempy + i] = A->get_sign();
                }
                else if (tgrid[tempx][tempy + i] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }
            if (tempy - i + 1 > 0)
            { //sola bakma

                if (i == 0)
                    continue;
                else if (tgrid[tempx][tempy - i] == 0)
                {

                    tgrid[tempx][tempy - i] = num_operators;
                    grid[tempx][tempy - i] = A->get_sign();
                }
                else if (tgrid[tempx][tempy - i] != 0 || tgrid[tempx][tempy - i] != num_operators)
                {
                    conflicterror += 1;
                }
            }
            else
            {

                bordererror += 1;
            }
        }
    }
    else if (A->get_sign() == '/')
    { //divison

        for (int i = 0; i < tempsize + 1; i++)
        {
            if (tempy + i + 1 <= grid_cols && tempx - i + 1 > 0)
            { //sağ çapraz bakma
                if (tgrid[tempx - i][tempy + i] == 0)
                {
                    tgrid[tempx - i][tempy + i] = num_operators;
                    grid[tempx - i][tempy + i] = A->get_sign();
                }
                else if (tgrid[tempx - i][tempy + i] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }

            if (tempy - i + 1 > 0 && tempx + i + 1 <= grid_rows)
            { //sol çapraz bakma

                if (i == 0)
                    continue;
                else if (tgrid[tempx + i][tempy - i] == 0)
                {
                    tgrid[tempx + i][tempy - i] = num_operators;
                    grid[tempx + i][tempy - i] = A->get_sign();
                }
                else if (tgrid[tempx + i][tempy - i] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }
        }
    }
    else if (A->get_sign() == '+')
    { //plus

        for (int i = 0; i < tempsize + 1; i++)
        {
            if (tempy + 1 <= grid_cols && tempx - i + 1 > 0)
            { // yukarı  bakma
                if (tgrid[tempx - i][tempy] == 0)
                {
                    tgrid[tempx - i][tempy] = num_operators;
                    grid[tempx - i][tempy] = A->get_sign();
                }
                else if (tgrid[tempx - i][tempy] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }

            if (tempy - i + 1 > 0 && tempx + 1 > 0)
            { //  sol  bakma

                if (i == 0)
                    continue;

                else if (tgrid[tempx][tempy - i] == 0)
                {
                    tgrid[tempx][tempy - i] = num_operators;
                    grid[tempx][tempy - i] = A->get_sign();
                }
                else if (tgrid[tempx][tempy - i] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }

            if (tempy + 1 > 0 && tempx + i + 1 <= grid_rows)
            { //aşağı  bakma

                if (i == 0)
                    continue;
                else if (tgrid[tempx + i][tempy] == 0)
                {
                    tgrid[tempx + i][tempy] = num_operators;
                    grid[tempx + i][tempy] = A->get_sign();
                }
                else if (tgrid[tempx + i][tempy] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }

            if (tempy + i + 1 <= grid_cols && tempx + 1 <= grid_rows)
            { // sağ  bakma

                if (i == 0)
                    continue;
                else if (tgrid[tempx][tempy + i] == 0)
                {
                    tgrid[tempx][tempy + i] = num_operators;
                    grid[tempx][tempy + i] = A->get_sign();
                }
                else if (tgrid[tempx][tempy + i] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }
        }
    }
    //ÇARP
    else if (A->get_sign() == 'x')
    {
        for (int i = 0; i < tempsize + 1; i++)
        {
            if (tempy + i + 1 <= grid_cols && tempx - i + 1 > 0)
            { // yukarı sağ çapraz bakma
                if (tgrid[tempx - i][tempy + i] == 0)
                {
                    tgrid[tempx - i][tempy + i] = num_operators;
                    grid[tempx - i][tempy + i] = A->get_sign();
                }
                else if (tgrid[tempx - i][tempy + i] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }

            if (tempy - i + 1 >= 0 && tempx - i + 1 > 0)
            { // yukarı sol çapraz bakma

                if (i == 0)
                    continue;

                else if (tgrid[tempx - i][tempy - i] == 0)
                {
                    tgrid[tempx - i][tempy - i] = num_operators;
                    grid[tempx - i][tempy - i] = A->get_sign();
                }
                else if (tgrid[tempx - i][tempy - i] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }

            if (tempy - i + 1 > 0 && tempx + i + 1 <= grid_rows)
            { //aşağı sol çapraz bakma

                if (i == 0)
                    continue;
                else if (tgrid[tempx + i][tempy - i] == 0)
                {
                    tgrid[tempx + i][tempy - i] = num_operators;
                    grid[tempx + i][tempy - i] = A->get_sign();
                }
                else if (tgrid[tempx + i][tempy - i] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }

            if (tempy + i + 1 <= grid_cols && tempx + i + 1 <= grid_rows)
            { //aşağı sağ çapraz bakma

                if (i == 0)
                    continue;
                else if (tgrid[tempx + i][tempy + i] == 0)
                {
                    tgrid[tempx + i][tempy + i] = num_operators;
                    grid[tempx + i][tempy + i] = A->get_sign();
                }
                else if (tgrid[tempx + i][tempy + i] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }
        }
    }

    if (bordererror != 0 && conflicterror != 0)
    {
        cout<<"BORDER ERROR: Operator "<<A->get_sign()<<" with size "<<A->get_size()<<" can not be placed on ("<<tempx+1<<','<<tempy+1<<")."<<endl;
        cout<<"CONFLICT ERROR: Operator "<<A->get_sign()<<" with size "<<A->get_size()<<" can not be placed on ("<<tempx+1<<','<<tempy+1<<")."<<endl;
        this->Gridfixer(num_operators);
        num_operators -= 1;
        return false;
    }
    else if (bordererror != 0)
    {
        cout<<"BORDER ERROR: Operator "<<A->get_sign()<<" with size "<<A->get_size()<<" can not be placed on ("<<tempx+1<<','<<tempy+1<<")."<<endl;
        this->Gridfixer(num_operators);
        num_operators -= 1;
        return false;
    }
    else if (conflicterror != 0)
    {
        cout<<"CONFLICT ERROR: Operator "<<A->get_sign()<<" with size "<<A->get_size()<<" can not be placed on ("<<tempx+1<<','<<tempy+1<<")."<<endl;
        this->Gridfixer(num_operators);
        num_operators -= 1;
        return false;
    }
        else{

        cout<<"SUCCESS: Operator "<<A->get_sign()<<" with size "<<A->get_size()<<" is placed on ("<<tempx+1<<','<<tempy+1<<")."<<endl;
        return true;

    }



}
bool OperatorGrid::copyplace_operator(ArithmeticOperator *A,int number)
{


    int bordererror = 0;
    int conflicterror = 0;


    int tempx = A->get_x() - 1;
    int tempy = A->get_y() - 1;
    int tempsize = A->get_size();

    if (A->get_sign() == '-')
    { //minus

        for (int i = 0; i < tempsize + 1; i++)
        {

            if (tempy + i + 1 <= grid_cols)
            { //sağa bakma
                if (tgrid[tempx][tempy + i] == 0)
                {
                    tgrid[tempx][tempy + i] = number;
                    grid[tempx][tempy + i] = A->get_sign();
                }
                else if (tgrid[tempx][tempy + i] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }
            if (tempy - i + 1 > 0)
            { //sola bakma

                if (i == 0)
                    continue;
                else if (tgrid[tempx][tempy - i] == 0)
                {

                    tgrid[tempx][tempy - i] = number;
                    grid[tempx][tempy - i] = A->get_sign();
                }
                else if (tgrid[tempx][tempy - i] != 0 || tgrid[tempx][tempy - i] != number)
                {
                    conflicterror += 1;
                }
            }
            else
            {

                bordererror += 1;
            }
        }
    }
    else if (A->get_sign() == '/')
    { //divison

        for (int i = 0; i < tempsize + 1; i++)
        {
            if (tempy + i + 1 <= grid_cols && tempx - i + 1 > 0)
            { //sağ çapraz bakma
                if (tgrid[tempx - i][tempy + i] == 0)
                {
                    tgrid[tempx - i][tempy + i] = number;
                    grid[tempx - i][tempy + i] = A->get_sign();
                }
                else if (tgrid[tempx - i][tempy + i] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }

            if (tempy - i + 1 > 0 && tempx + i + 1 <= grid_rows)
            { //sol çapraz bakma

                if (i == 0)
                    continue;
                else if (tgrid[tempx + i][tempy - i] == 0)
                {
                    tgrid[tempx + i][tempy - i] = number;
                    grid[tempx + i][tempy - i] = A->get_sign();
                }
                else if (tgrid[tempx + i][tempy - i] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }
        }
    }
    else if (A->get_sign() == '+')
    { //plus

        for (int i = 0; i < tempsize + 1; i++)
        {
            if (tempy + 1 <= grid_cols && tempx - i + 1 > 0)
            { // yukarı  bakma    else{

                if (tgrid[tempx - i][tempy] == 0)
                {
                    tgrid[tempx - i][tempy] = number;
                    grid[tempx - i][tempy] = A->get_sign();
                }
                else if (tgrid[tempx - i][tempy] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }

            if (tempy - i + 1 > 0 && tempx + 1 > 0)
            { //  sol  bakma

                if (i == 0)
                    continue;

                else if (tgrid[tempx][tempy - i] == 0)
                {
                    tgrid[tempx][tempy - i] = number;
                    grid[tempx][tempy - i] = A->get_sign();
                }
                else if (tgrid[tempx][tempy - i] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }

            if (tempy + 1 > 0 && tempx + i + 1 <= grid_rows)
            { //aşağı  bakma

                if (i == 0)
                    continue;
                else if (tgrid[tempx + i][tempy] == 0)
                {
                    tgrid[tempx + i][tempy] = number;
                    grid[tempx + i][tempy] = A->get_sign();
                }
                else if (tgrid[tempx + i][tempy] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }

            if (tempy + i + 1 <= grid_cols && tempx + 1 <= grid_rows)
            { // sağ  bakma

                if (i == 0)
                    continue;
                else if (tgrid[tempx][tempy + i] == 0)
                {
                    tgrid[tempx][tempy + i] = number;
                    grid[tempx][tempy + i] = A->get_sign();
                }
                else if (tgrid[tempx][tempy + i] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }
        }
    }
    //ÇARP
    else if (A->get_sign() == 'x')
    {
        for (int i = 0; i < tempsize + 1; i++)
        {
            if (tempy + i + 1 <= grid_cols && tempx - i + 1 > 0)
            { // yukarı sağ çapraz bakma
                if (tgrid[tempx - i][tempy + i] == 0)
                {
                    tgrid[tempx - i][tempy + i] = number;
                    grid[tempx - i][tempy + i] = A->get_sign();
                }
                else if (tgrid[tempx - i][tempy + i] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }

            if (tempy - i + 1 >= 0 && tempx - i + 1 > 0)
            { // yukarı sol çapraz bakma

                if (i == 0)
                    continue;

                else if (tgrid[tempx - i][tempy - i] == 0)
                {
                    tgrid[tempx - i][tempy - i] = number;
                    grid[tempx - i][tempy - i] = A->get_sign();
                }
                else if (tgrid[tempx - i][tempy - i] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }

            if (tempy - i + 1 > 0 && tempx + i + 1 <= grid_rows)
            { //aşağı sol çapraz bakma

                if (i == 0)
                    continue;
                else if (tgrid[tempx + i][tempy - i] == 0)
                {
                    tgrid[tempx + i][tempy - i] = number;
                    grid[tempx + i][tempy - i] = A->get_sign();
                }
                else if (tgrid[tempx + i][tempy - i] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }

            if (tempy + i + 1 <= grid_cols && tempx + i + 1 <= grid_rows)
            { //aşağı sağ çapraz bakma

                if (i == 0)
                    continue;
                else if (tgrid[tempx + i][tempy + i] == 0)
                {
                    tgrid[tempx + i][tempy + i] = number;
                    grid[tempx + i][tempy + i] = A->get_sign();
                }
                else if (tgrid[tempx + i][tempy + i] != 0)
                {
                    conflicterror += 1;
                }
            }
            else
            {
                bordererror += 1;
            }
        }
    }

    if (bordererror != 0 && conflicterror != 0)
    {
        cout << "Move border+conflict error" << endl;
        this->Gridfixer(number);

        return false;
    }
    else if (bordererror != 0)
    {
        cout << "border error" << endl;
        this->Gridfixer(num_operators);

        return false;
    }
    else if (conflicterror != 0)
    {
        cout<<"CONFLICT ERROR: Operator "<<A->get_sign()<<" can not be moved from ";
        this->Gridfixer(num_operators);
        return false;
    }

        return true;

}
bool OperatorGrid::move_operator(int x, int y, char direction, int move_by)
{

    int n_operator = tgrid[x - 1][y - 1];
    int tempxcenter = operators[n_operator]->get_x();

    int tempycenter = operators[n_operator]->get_y();

    this->Gridfixer(n_operator);

    if (direction == 'U')
    {
        operators[n_operator]->set_x(tempxcenter - move_by);
        if (this->copyplace_operator(operators[n_operator],n_operator) == false)
        {

            operators[n_operator]->set_x(tempxcenter);
            this->copyplace_operator(operators[n_operator],n_operator);
        }
    }
    else if (direction == 'D')
    {
        operators[n_operator]->set_x(tempxcenter + move_by);
        if (this->place_operator(operators[n_operator]) == false)
        {
            n_operator -= 1;
            operators[n_operator]->set_x(tempxcenter);
            this->place_operator(operators[n_operator]);
        }
    }
    else if (direction == 'R')
    {
        operators[n_operator]->set_y(tempycenter + move_by);
        if (this->place_operator(operators[n_operator]) == false)
        {
            n_operator -= 1;
            operators[n_operator]->set_y(tempxcenter);
            this->place_operator(operators[n_operator]);
        }
    }
    else if (direction == 'L')
    {
        operators[n_operator]->set_y(tempycenter - move_by);
        if (this->place_operator(operators[n_operator]) == false)
        {
            n_operator -= 1;
            operators[n_operator]->set_y(tempxcenter);
            this->place_operator(operators[n_operator]);
        }
    }
}

//Operator Class
Operator ::Operator(int x, int y, int size)
{

    center_x = x;
    center_y = y;

    op_size = size;
}

void Operator::reset(int new_x, int new_y, int new_size)
{

    center_x = new_x;
    center_y = new_y;
    op_size = new_size;
}
//setters
void Operator::set_x(int new_x)
{
    center_x = new_x;
}
void Operator::set_y(int new_y)
{
    center_y = new_y;
}
void Operator::set_size(int new_size)
{
    op_size = new_size;
}

//getters
int Operator::get_x()
{
    return center_x;
}

int Operator::get_y()
{

    return center_y;
}

int Operator::get_size()
{

    return op_size;
}

//Arithmetic Operator Class
ArithmeticOperator::ArithmeticOperator(int x, int y, int size, char sign) : Operator(x, y, size)
{

    set_x(x);
    set_y(y);
    set_size(size);

    this->sign = sign;
}
char ArithmeticOperator::get_sign()
{

    return sign;
}

int main()
{

    OperatorGrid B(5, 5);

    ArithmeticOperator K(3, 3, 1, '-');
    ArithmeticOperator L(3, 3, 1, '+');

    B.place_operator(&L);
    B.place_operator(&K);
    //B.move_operator(3, 3, 'U', 1);

    B.printer();
}
