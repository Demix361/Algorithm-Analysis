#include "mult_matrix.h"
#include "controller.h"
#define COUNT_TESTS 10

std::vector<Matrix> matr_1 = {{{2}},

                              {{1, 2},
                               {3, 4}},

                              {{1, 2},
                               {3, 4}},

                              {{1, 2},
                               {3, 4}},

                              {{1, 2},
                               {3, 4}},

                              {{1, 2, 3},
                               {4, 5, 6},
                               {7, 8, 9}},

                              {{1, 2, 3},
                               {4, 5, 6},
                               {7, 8, 9}},

                              {{1, 2, 3},
                               {4, 5, 6}},

                              {{1, 2, 3, 4},
                               {5, 6, 7, 8}},

                              {{1000, 2000, 3000},
                               {4000, 5000, 6000},
                               {7000, 8000, 9000}}};


std::vector<Matrix> matr_2 = {{{3}},

                              {{1, 0},
                               {0, 1}},

                              {{0, 0},
                               {0, 0}},

                              {{1, 2},
                               {3, 4}},

                              {{-1, -2},
                               {-3, -4}},

                              {{1, 2, 3},
                               {4, 5, 6},
                               {7, 8, 9}},

                              {{-1, -2, -3},
                               {-4, -5, -6},
                               {-7, -8, -9}},

                              {{1, 2},
                               {3, 4},
                               {5, 6}},

                              {{1, 2},
                               {3, 4},
                               {5, 6},
                               {7, 8}},

                              {{1000, 2000, 3000},
                               {4000, 5000, 6000},
                               {7000, 8000, 9000}}};


std::vector<Matrix> answer_matr {{{6}},

                                 {{1, 2},
                                  {3, 4}},

                                 {{0, 0},
                                  {0, 0}},

                                 {{7, 10},
                                  {15, 22}},

                                 {{-7, -10},
                                  {-15, -22}},

                                 {{30, 36, 42},
                                  {66, 81, 96},
                                  {102, 126, 150}},

                                 {{-30, -36, -42},
                                  {-66, -81, -96},
                                  {-102, -126, -150}},

                                 {{22,	28},
                                  {49, 64}},

                                 {{50, 60},
                                  {114, 140}},

                                 {{30000000, 36000000, 42000000},
                                  {66000000, 81000000, 96000000},
                                  {102000000, 126000000, 150000000}}};


bool is_equal(Matrix &matr_1, Matrix &matr_2) {
    size_t n = matr_1.size();
    size_t m = matr_1[0].size();
    for (size_t i = 0; i < n; i++) {
        for(size_t j = 0; j < m; j++) {
            if (matr_1[i][j] != matr_2[i][j])
                return false;
        }
    }
    return true;
}

void test()
{
    int count_success = 0;
    int prev_suc = 0;
    for(int i = 0; i < COUNT_TESTS; i++) {
        print_matr(matr_1[i], "Matr 1:\n");
        print_matr(matr_2[i], "Matr 2:\n");
        prev_suc = count_success;
        {
            Matrix res_matr(matr_1[i].size(), Vector(matr_2[i][0].size(), 0));
            mult_matrix_std(matr_1[i], matr_2[i], res_matr);
            if (is_equal(res_matr, answer_matr[i]))
                count_success++;
            print_matr(res_matr, "Result of multiplication of standard:\n");
    
        }

        {
           Matrix res_matr(matr_1[i].size(), Vector(matr_2[i][0].size(), 0));
            mult_matrix_vinograd(matr_1[i], matr_2[i], res_matr);
            if (is_equal(res_matr, answer_matr[i]))
                count_success++;
            print_matr(res_matr, "Result of multiplication by Vinograd:\n");
        }



        {
            Matrix res_matr(matr_1[i].size(), Vector(matr_2[i][0].size(), 0));
            mult_matrix_vinograd_optimiz(matr_1[i], matr_2[i], res_matr);
            if (is_equal(res_matr, answer_matr[i]))
                count_success++;  
            print_matr(res_matr, "Result of multiplication by Vinograd is optimized:\n");
        }

        if (prev_suc == count_success - 3)
            std::cout << "TEST OK" << std::endl;
        else
            std::cout << "TEST FAILED" << std::endl;
        
        std::cout << "\n\n";




    }
    std::cout << "Tests success: " << count_success << "/" << COUNT_TESTS*3 << std::endl;

}
//int main() {
//   test();
//   return 0;
//}
