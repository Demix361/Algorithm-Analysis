#include "controller.h"
#include "time_test.h"
#include "mul_test.h"
#include "mult_matrix.h"


int main(int argc, char *argv[])
{
    int size = 400;
    Matrix mtr_1(size, Vector(size, 0));
    Matrix mtr_2(size, Vector(size, 0));

    fill_mtr(mtr_1);
    fill_mtr(mtr_2);



    new_time_test(4, mtr_1, mtr_2);
    new_time_test(6, mtr_1, mtr_2);
    new_time_test(8, mtr_1, mtr_2);
    new_time_test(10, mtr_1, mtr_2);
    new_time_test(12, mtr_1, mtr_2);
    new_time_test(16, mtr_1, mtr_2);
    new_time_test(17, mtr_1, mtr_2);
    new_time_test(18, mtr_1, mtr_2);
    new_time_test(19, mtr_1, mtr_2);
    new_time_test(20, mtr_1, mtr_2);
    new_time_test(32, mtr_1, mtr_2);
    new_time_test(64, mtr_1, mtr_2);
    new_time_test(128, mtr_1, mtr_2);
    //controller();
    //mul_test();
    return 0;
}
