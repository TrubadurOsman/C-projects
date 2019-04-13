#include <iostream>
#include "Operator.h"
#include "OperatorGrid.h"
#include "ArithmeticOperator.h"

using namespace std ;

OperatorGrid ::OperatorGrid(int rows,int cols){
    MAX_OPERATOR_SIZE=20;
    num_operators=0;
    grid_rows = rows;
    grid_cols =cols;

    grid = new char*[rows];
    for(int i =0;i<rows ;i++){
        grid[i]=new char[cols];
    }

    for(int i =0;i<rows ;i++){
        for(int j=0;j<cols;j++){

        grid[i][j]='0';

        }
    }

    tgrid= new int*[rows];
    for(int i =0;i<rows ;i++){
        tgrid[i]=new int[cols];
    }

    for(int i =0;i<rows ;i++){
        for(int j=0;j<cols;j++){

        tgrid[i][j]=0;

        }
    }





}
void OperatorGrid::printer(){
for(int i =0;i<grid_rows ;i++){
    for(int j=0;j<grid_cols;j++){

    cout<<grid[i][j];
    }
    cout<<endl;
}
cout<<endl;
for(int i =0;i<grid_rows ;i++){
    for(int j=0;j<grid_cols;j++){

    cout<<tgrid[i][j];
    }
    cout<<endl;
}



}

OperatorGrid::~OperatorGrid(){

for (int i = 0; i < grid_cols; ++i){

delete[] grid[i];
}
delete [] grid;

}
//BOOOOO
bool OperatorGrid::place_operator( ArithmeticOperator *A){
    num_operators+=1;
    operators[num_operators]=A;


    int tempx =  A->get_x()-1;
    int tempy =A->get_y()-1;
    int tempsize = A->get_size();



if(A->get_sign()=='-'){ //minus

    grid[tempx][tempy]= A->get_sign();
    tgrid[tempx][tempy]=num_operators;




    for(int i = tempsize ; 0<i;i--){

    if((tempy+i+1>grid_cols||tempy-i+1<0) && (tgrid[tempx][tempy+i]!=0 ||tgrid[tempx][tempy-i]!=0)){
        cout<<"border error+conflict"<<endl;
        grid[tempx][tempy]='0';
        tgrid[tempx][tempy]=0;

        return false;
    }

    grid[tempx][tempy+i]= A->get_sign();
    grid[tempx][tempy-i]= A->get_sign();
    tgrid[tempx][tempy+i]= num_operators;
    tgrid[tempx][tempy-i]= num_operators;

    }


    return true;
    }
else if(A->get_sign()=='/'){//divison

    /*if(tempy+tempsize+1>grid_cols || tempy-tempsize+1<0||tempx+tempsize+1>grid_rows||tempx-tempsize+1<0){
        cout<<"Border error"<<endl;
        return false ;

    }*/

    grid[tempx][tempy]= A->get_sign();
    tgrid[tempx][tempy]=num_operators;


    for(int i = A->get_size() ; 0<i;i--){

    grid[tempx-i][tempy+i]= A->get_sign();
    grid[tempx+i][tempy-i]= A->get_sign();

    tgrid[tempx-i][tempy+i]= num_operators;
    tgrid[tempx+i][tempy-i]= num_operators;


    }
    }
else if(A->get_sign()=='+'){//plus
    if(tempy+tempsize+1>grid_cols || tempy-tempsize+1<0||tempx+tempsize+1>grid_rows||tempx-tempsize+1<0){
        cout<<"Border error"<<endl;
        return false ;

    }

    grid[A->get_x()-1][A->get_y()-1]= A->get_sign();
    tgrid[tempx][tempy]=num_operators;

    for(int i = A->get_size() ; 0<i;i--){

    grid[tempx][tempy+i]= A->get_sign();
    grid[tempx][tempy-i]= A->get_sign();
    grid[tempx+i][tempy]= A->get_sign();
    grid[tempx-i][tempy]= A->get_sign();

    tgrid[tempx][tempy+i]= num_operators;
    tgrid[tempx][tempy-i]= num_operators;
    tgrid[tempx+i][tempy]= num_operators;
    tgrid[tempx-i][tempy]= num_operators;

    }
    }
//ÇARP
else if(A->get_sign()=='x'){
    if(tempy+tempsize+1>grid_cols || tempy-tempsize+1<0||tempx+tempsize+1>grid_rows||tempx-tempsize+1<0){
        cout<<"Border error"<<endl;
        return false ;

    }

    grid[tempx][tempy]= A->get_sign();
    tgrid[tempx][tempy]=num_operators;

    for(int i = A->get_size() ; 0<i;i--){

    grid[tempx+i][tempy+i]= A->get_sign();
    grid[tempx-i][tempy+i]= A->get_sign();
    grid[tempx+i][tempy-i]= A->get_sign();
    grid[tempx-i][tempy-i]= A->get_sign();

    tgrid[tempx+i][tempy+i]= num_operators;
    tgrid[tempx-i][tempy+i]= num_operators;
    tgrid[tempx+i][tempy-i]= num_operators;
    tgrid[tempx-i][tempy-i]= num_operators;


    }

}






return true;

}


//Operator Class
Operator ::Operator(int x ,int y ,int size){

center_x=x;
center_y=y;

op_size=size;



}

void Operator::reset(int new_x,int new_y ,int new_size){

center_x=new_x;
center_y= new_y;
op_size=new_size;
}
//setters
void Operator::set_x(int new_x){
center_x=new_x;

}
void Operator::set_y(int new_y){
center_y=new_y;

}
void Operator::set_size(int new_size){
op_size=new_size;

}

//getters
int Operator::get_x(){

return center_x;
}

int Operator::get_y(){

return center_y;
}

int Operator::get_size(){

return op_size;
}

//Arithmetic Operator Class
ArithmeticOperator:: ArithmeticOperator(int x,int y,int size ,char sign):Operator(x,y,size){

set_x(x);
set_y(y);
set_size(size);

this->sign=sign;


}
char ArithmeticOperator::get_sign(){

return sign;
}


int main(){

OperatorGrid B(10,10);


ArithmeticOperator A(4,4,2,'x');
ArithmeticOperator K(5,4,2,'-');
ArithmeticOperator *Y=&A;

B.place_operator(Y);

B.place_operator(&K);
B.printer();



}


