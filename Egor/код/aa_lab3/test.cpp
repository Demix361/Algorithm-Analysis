#include "sort.h"
#include "controller.h"
#define COUNT_TESTS 11

std::vector<Vector> source_arr = {{1},
                                  {2, 1},
                                  {1, 2, 3, 4, 5},
                                  {5, 4, 3, 2, 1},
                                  {2, 2, 2},
                                  {5, 2, 3, 4, 1},
                                  {-5, -2, -3, -4, -1},
                                  {-5, 4, -3, 2, -1, 0},
                                  {1, 1, 3, 6, 1, 5, 9, 3},
                                  {3.98, 0, 4.1, -2.34, 10.876, 3.99, -8},
                                  {1000, -2000, 3000, 0, 5000, -9000, -5000}};



std::vector<Vector> answer_arr = {{1},
                              {1, 2},
                              {1, 2, 3, 4, 5},
                              {1, 2, 3, 4, 5},
                              {2, 2, 2},
                              {1, 2, 3, 4, 5},
                              {-5, -4, -3, -2, -1},
                              {-5, -3, -1, 0, 2, 4},
                              {1, 1, 1, 3, 3, 5, 6, 9},
                              {-8, -2.34, 0, 3.98, 3.99, 4.1, 10.876},
                              {-9000, -5000, -2000, 0, 1000, 3000, 5000}};

bool is_equal(Vector &arr_1, Vector &arr_2) {
    size_t n = arr_1.size();
    for (size_t i = 0; i < n; i++) {
        if (arr_1[i] != arr_2[i])
            return false;
    }
    return true;
}

void test()
{
    int count_success = 0;
    int prev_suc = 0;
    for(int i = 0; i < COUNT_TESTS; i++) {
        print_arr(source_arr[i], "Source array:\n");
        Vector res_arr(source_arr[i].size(), 0);
        prev_suc = count_success;
        {
            for (int j = 0; j < source_arr[i].size(); j++)
                res_arr[j] = source_arr[i][j];
            bubble_sort(res_arr);
            if (is_equal(res_arr, answer_arr[i]))
                count_success++;
            print_arr(res_arr, "Result of bubble sort:\n");
        }

        {
            for (int j = 0; j < source_arr[i].size(); j++)
                res_arr[j] = source_arr[i][j];
            merge_sort(res_arr);
            if (is_equal(res_arr, answer_arr[i]))
                count_success++;
            print_arr(res_arr, "Result of merge sort:\n");

        }

        {
            for (int j = 0; j < source_arr[i].size(); j++)
                res_arr[j] = source_arr[i][j];
            quick_sort(res_arr);
            if (is_equal(res_arr, answer_arr[i]))
                count_success++;
            print_arr(res_arr, "Result of quick sort:\n");

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
