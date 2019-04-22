#include <iostream>
#define MAX_OPERATOR_SIZE 500
#include "Operator.h"
#include "OperatorGrid.h"
#include "ArithmeticOperator.h"

using namespace std;



OperatorGrid ::OperatorGrid(int rows, int cols)//constructor for operatorgrid
{


    num_operators = 0;
    grid_rows = rows;
    grid_cols = cols;

    tgrid = new int *[rows];// I have used a second matrix to store index of operators
    grid = new char *[rows];

    for (int i = 0; i < rows; i++)
    {
        grid[i] = new char[cols];
        tgrid[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++)//all points are 0
    {
        for (int j = 0; j < cols; j++)
        {

            grid[i][j] = '0';
            tgrid[i][j] = 0;
        }
    }



}
void OperatorGrid::printer()//helper method to check grid visually
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

            cout << tgrid[i][j]<<" ";
        }
        cout << endl;
    }
}
//gridfixer
void OperatorGrid::Gridfixer(int number)//Helper method to fix grid.
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
//printer
void OperatorGrid::print_operators()
{
        for (int i = 1; i <= num_operators; i++){
            cout<<"ARITHMETIC_OPERATOR["<<operators[i]->get_sign()<<"],CENTER_LOCATION["<<operators[i]->get_x()<<','<<operators[i]->get_y()<<"],SIZE["<<operators[i]->get_size()<<']'<<endl;
        }

}

OperatorGrid::~OperatorGrid()//Destructor
{

    for (int i = 0; i < grid_cols; ++i)
    {
        delete[] tgrid[i];
        delete[] grid[i];
    }
    for (int i = 1; i <= num_operators; ++i)
    {
        delete[] operators[i];

    }
    delete[] grid;
    delete[] tgrid;
    cout<<"DESTRUCTOR: GIVE BACK["<<grid_rows<<','<<grid_cols<<"] chars."<<endl;
    cout<<"DESTRUCTOR: GIVE BACK["<<num_operators<<"] operators.";
}

bool OperatorGrid::place_operator(ArithmeticOperator *A)
{
    num_operators += 1;
    operators[num_operators] = A;
    int bordererror = 0; //used error accumulation .
    int conflicterror = 0;

    int tempx = A->get_x() - 1;
    int tempy = A->get_y() - 1; //storing centers in order to not to call functions everytime
    int tempsize = A->get_size();

    if (A->get_sign() == '-')//minus operation
    {

        for (int i = 0; i < tempsize + 1; i++)
        {

            if (tempy + i + 1 <= grid_cols &&tempx  + 1 <= grid_rows && tempx+1 >0)//checking the right side
            {
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
            if (tempy - i + 1 > 0 &&tempx  + 1 <= grid_rows&&tempx+1 >0)
            { //checking the left side

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
            { //checking right upper side
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
            { //checking left upper side

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
            { // //checking  upper side
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
            { // //checking left side

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
            { ////checking lower side

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
            { // //checking right side

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
    //Cross
    else if (A->get_sign() == 'x')
    {
        for (int i = 0; i < tempsize + 1; i++)
        {
            if (tempy + i + 1 <= grid_cols && tempx - i + 1 > 0)
            { // right upper diagonal
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
            { // left upper diagonal

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
            { //left lower diagonal

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
            { //right lower diagonal

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

    if (bordererror != 0 && conflicterror != 0)// error checking
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
bool OperatorGrid::copyplace_operator(ArithmeticOperator *A,int number,int tempxcenter,int tempycenter,int move_by,int key,char direction)// it is the same function with the place_operator but since the error handling part is diffrent I had to change few things in error accumulation
{
    int b=0;
    int a=0;


    if(direction=='R'){ // in order to  store new coordinates.

    b =tempycenter+move_by;
    a=tempxcenter;



    }
    else if(direction=='L'){

     b =tempycenter-move_by;
     a=tempxcenter;

    }
    else if(direction=='U'){

   b =tempycenter;
   a=tempxcenter-move_by;

    }
    else if(direction=='D'){

   b =tempycenter;
   a=tempxcenter+move_by;

    }


    int bordererror = 0;
    int conflicterror = 0;


    int tempx = A->get_x() - 1;
    int tempy = A->get_y() - 1;
    int tempsize = A->get_size();

    if (A->get_sign() == '-') //this if else part is totaly same with the place_operator
    { //minus

        for (int i = 0; i < tempsize + 1; i++)
        {

            if (tempy + i + 1 <= grid_cols &&  tempx+ 1 <= grid_rows &&tempx+1 >0)
            {
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
            if (tempy - i + 1 > 0&&tempx  + 1 <= grid_rows &&tempx+1 >0 )
            {

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
            {
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
            {

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
            {

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
            {

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
            {

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
    //Cross
    else if (A->get_sign() == 'x')
    {
        for (int i = 0; i < tempsize + 1; i++)
        {
            if (tempy + i + 1 <= grid_cols && tempx - i + 1 > 0)
            {
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
            {

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
            {

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
            {

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

    if (bordererror != 0 && conflicterror != 0)// error handling with the data of previous centers
    {
        cout << "BORDER ERROR: "<<A->get_sign()<<" can not be moved from ("<<tempxcenter<<','<<tempycenter<< ") to (" <<a<<","<<b<<")."<<endl;
        cout<<"CONFLICT ERROR: "<<A->get_sign()<<" can not be moved from ("<<tempxcenter<<','<<tempycenter<< ") to (" <<a<<","<<b<<")."<<endl;

        this->Gridfixer(number);

        return false;
    }
    else if (bordererror != 0)
    {
        cout << "BORDER ERROR: "<<A->get_sign()<<" can not be moved from ("<<tempxcenter<<','<<tempycenter<< ") to (" <<a<<","<<b<<")."<<endl;
        this->Gridfixer(number);

        return false;
    }
    else if (conflicterror != 0)
    {
        cout<<"CONFLICT ERROR: "<<A->get_sign()<<" can not be moved from ("<<tempxcenter<<','<<tempycenter<< ") to (" <<a<<","<<b<<")."<<endl;
        this->Gridfixer(number);
        return false;
    }
    else if(key==0){


    cout<<"SUCCESS: "<< A->get_sign()<<" moved from ("<< tempxcenter<<','<<tempycenter<< ") to (" <<a<<","<<b<<")."<<endl;

    }


        return true;

}
bool OperatorGrid::move_operator(int x, int y, char direction, int move_by)//move function
{
    int key = 0;// it is a switch for error handling
    int n_operator = tgrid[x - 1][y - 1];//finding the center with second array
    int tempxcenter = operators[n_operator]->get_x();//previous coordinates

    int tempycenter = operators[n_operator]->get_y();

    this->Gridfixer(n_operator);//previous coordinates deleted.

    if (direction == 'U')
    {
        operators[n_operator]->set_x(tempxcenter - move_by);//new x
        if (this->copyplace_operator(operators[n_operator],n_operator,tempxcenter,tempycenter,move_by,key,direction) == false)//try to place new coordinates.
        {
            key+=1;
            operators[n_operator]->set_x(tempxcenter);
            this->copyplace_operator(operators[n_operator],n_operator,tempxcenter,tempycenter,move_by,key,direction);//places into old center
            return false;

        }
    }
    else if (direction == 'D')
    {
        operators[n_operator]->set_x(tempxcenter + move_by);
        if (this->copyplace_operator(operators[n_operator],n_operator,tempxcenter,tempycenter,move_by,key,direction) == false)//try to place new coordinates.
        {
            key+=1;
            operators[n_operator]->set_x(tempxcenter);

            this->copyplace_operator(operators[n_operator],n_operator,tempxcenter,tempycenter,move_by,key,direction);//places into old center
            return false;
        }
    }
    else if (direction == 'R')
    {
        operators[n_operator]->set_y(tempycenter + move_by);
        if (this->copyplace_operator(operators[n_operator],n_operator,tempxcenter,tempycenter,move_by,key,direction) == false)//try to place new coordinates.
        {
            key+=1;
            operators[n_operator]->set_y(tempycenter);
            this->copyplace_operator(operators[n_operator],n_operator,tempxcenter,tempycenter,move_by,key,direction);//places into old center
            return false;
        }
    }
    else if (direction == 'L')
    {
        operators[n_operator]->set_y(tempycenter - move_by);
        if (this->copyplace_operator(operators[n_operator],n_operator,tempxcenter,tempycenter,move_by,key,direction)== false)//try to place new coordinates.
        {
            key+=1;
            operators[n_operator]->set_y(tempycenter);
           this->copyplace_operator(operators[n_operator],n_operator,tempxcenter,tempycenter,move_by,key,direction);//places into old center
           return false;
        }
    }
    return true ;
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
    if(sign=='x'||sign=='+'||sign=='/'||sign=='-'){

        this->sign = sign;
    }
    else{
        cout<<"SIGN parameter is invalid!"<<endl;
    }


}
char ArithmeticOperator::get_sign()
{

    return sign;
}

int main()
{

     OperatorGrid og(10,10);
    ArithmeticOperator *ao1 = new ArithmeticOperator(2,2,1,'/');
    ArithmeticOperator *ao2 = new ArithmeticOperator(3,3,1,'+');
    ArithmeticOperator *ao3 = new ArithmeticOperator(3,6,2,'x');
    ArithmeticOperator *ao4 = new ArithmeticOperator(3,8,1,'-');
    ArithmeticOperator *ao5 = new ArithmeticOperator(5,5,1,'/');
    ArithmeticOperator *ao6 = new ArithmeticOperator(6,8,2,'/');
    ArithmeticOperator *ao7 = new ArithmeticOperator(7,3,2,'+');
    ArithmeticOperator *ao8 = new ArithmeticOperator(7,9,1,'+');
    ArithmeticOperator *ao9 = new ArithmeticOperator(9,7,2,'-');
    ArithmeticOperator *ao10 = new ArithmeticOperator(10,6,4,'-');
    ArithmeticOperator *ao11 = new ArithmeticOperator(1,2,1,'x');
    ArithmeticOperator *ao12 = new ArithmeticOperator(6,5,2,'x');
    ArithmeticOperator *ao13 = new ArithmeticOperator(1,10,1,'x');
    ArithmeticOperator *ao14 = new ArithmeticOperator(9,4,2,'+');
    ArithmeticOperator *ao15 = new ArithmeticOperator(2,10,1,'+');
    ArithmeticOperator *ao16 = new ArithmeticOperator(5,6,1,'-');
    ArithmeticOperator *ao17 = new ArithmeticOperator(6,10,1,'-');
    ArithmeticOperator *ao18 = new ArithmeticOperator(2,8,2,'/');
    ArithmeticOperator *ao19 = new ArithmeticOperator(5,2,1,'/');
    ArithmeticOperator *ao20 = new ArithmeticOperator(9,1,1,'/');

    og.place_operator(ao1);
    og.place_operator(ao2);
    og.place_operator(ao3);
    og.place_operator(ao4);
    og.place_operator(ao5);
    og.place_operator(ao6);
    og.place_operator(ao7);
    og.place_operator(ao8);
    og.place_operator(ao9);
    og.place_operator(ao10);
    og.place_operator(ao11); //border-conf
    og.place_operator(ao12); //conf
    og.place_operator(ao13); //border
    og.place_operator(ao14); //border-conf
    og.place_operator(ao15); //border
    og.place_operator(ao16); //conf
    og.place_operator(ao17); //border-conf
    og.place_operator(ao18); //border-conf
    og.place_operator(ao19); //conf
    og.place_operator(ao20); //border

    og.move_operator(3, 1, 'R', 4);
    og.move_operator(3, 8, 'R', 1);
    og.move_operator(4, 6, 'D', 3);
    og.move_operator(7, 2, 'L', 2);//border
    og.move_operator(7, 7, 'R', 1);//border-conf
    og.move_operator(9, 8, 'L', 1);//conf
    //og.printer();
    og.move_operator(10, 4, 'U', 17);//border

    return 0;
}
