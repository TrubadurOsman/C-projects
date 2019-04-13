#ifndef OPERATOR_H
#define OPERATOR_H


class Operator
{
    public:
        Operator(int x,int y ,int size);

        void reset(int new_x,int new_y, int new_size);

        void set_x(int new_x);
        int get_x();

        void set_y(int new_y);
        int get_y();


        void set_size(int new_size);
        int get_size();



    private:
        int center_x;
        int center_y;
        int op_size;
};


#endif // OPERATOR_H
