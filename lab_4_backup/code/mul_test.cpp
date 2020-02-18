#include "mult_matrix.h"
#include "controller.h"
#define COUNT_TESTS 10


bool is_equal(Matrix &mtr_1, Matrix &mtr_2)
{
    size_t n = mtr_1.size();
    size_t m = mtr_1[0].size();

    for (size_t i = 0; i < n; i++)
    {
        for(size_t j = 0; j < m; j++)
        {
            if (mtr_1[i][j] != mtr_2[i][j])
                return false;
        }
    }

    return true;
}


void mul_test()
{
    std::vector<Matrix> mtr_1 = {{{2}},

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

    std::vector<Matrix> mtr_2 = {{{3}},

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

    std::vector<Matrix> mtr_ans {{{6}},

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

    int count_success = 0;
    int passed;

    for(int i = 0; i < COUNT_TESTS; i++)
    {
        passed = 0;
        print_mtr(mtr_1[i], "Matrix 1:\n");
        print_mtr(mtr_2[i], "Matrix 2:\n");

        Matrix mtr_res(mtr_1[i].size(), Vector(mtr_2[i][0].size(), 0));

        mul_vinograd(mtr_1[i], mtr_2[i], mtr_res);

        if (is_equal(mtr_res, mtr_ans[i]))
        {
            count_success++;
            passed = 1;
        }

        print_mtr(mtr_res, "Result:\n");

        if (passed == 1)
            std::cout << "[TEST PASSED]" << std::endl;
        else
            std::cout << "[TEST FAILED]" << std::endl;
        
        std::cout << "\n";
    }

    std::cout << "No threading tests. Passed: " << count_success << "/" << COUNT_TESTS << "\n\n" << std::endl;

    for(int k = 1; k <= 128; k *= 2)
    {
        count_success = 0;

        for(int i = 0; i < COUNT_TESTS; i++)
        {
            Matrix mtr_res(mtr_1[i].size(), Vector(mtr_2[i][0].size(), 0));
            mul_vinograd_threads(k, mtr_1[i], mtr_2[i], mtr_res);

            if (is_equal(mtr_res, mtr_ans[i]))
                count_success++;
        }

        std::cout << k << " thread(s) tests. Passed: " << count_success << "/" << COUNT_TESTS << std::endl;
    }
}
