#include <chrono>
#include <fstream>
#include <cstring>
#include <string>
#include "mult_matrix.h"

#define COUNT_CICLE 3
#define MAX_SIZE 1000


void fill_mtr(Matrix &mtr)
{
    size_t n = mtr.size();
    size_t m = mtr[0].size();

    for (size_t i = 0; i < n; i++)
    {
        for(size_t j = 0; j < m; j++)
        {
            mtr[i][j] = rand();
        }
    }
}


void write_to_file(std::ofstream &file, int size, double result)
{
    char str_size[6];
    char str_res[16];

    sprintf(str_size,"%d", size);
    sprintf(str_res,"%f", result);

    file << str_size << " " << str_res << endl;
}


void time_test()
{
    double result = 0;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::ofstream file;

    // Без потоков четные
    std::cout << "No threads even" << std::endl;
    file.open("time_no_th_even.txt", std::ios::out);

    for(int i = 100; i <= MAX_SIZE; i += 100)
    {
        cout << "matrix " << i << " x " << i << " ";
        Matrix mtr_1(i, Vector(i, 0));
        Matrix mtr_2(i, Vector(i, 0));
        result = 0;

        fill_mtr(mtr_1);
        fill_mtr(mtr_2);

        for (int j = 0; j < COUNT_CICLE; j++)
        {
            Matrix mtr_res(i, Vector(i, 0));

            start = std::chrono::system_clock::now();
            mul_vinograd(mtr_1, mtr_2, mtr_res);
            end = std::chrono::system_clock::now();

            result += std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
        }
        result /= COUNT_CICLE;
        write_to_file(file, i, result);
        cout << result << " ms" << endl;
    }
    file << std::endl;
    file.close();

    // Без потоков нечетные
    std::cout << "No threads odd" << std::endl;
    file.open("time_no_th_odd.txt", std::ios::out);

    for(int i = 101; i <= MAX_SIZE + 1; i += 100)
    {
        cout << "matrix " << i << " x " << i << " ";
        Matrix mtr_1(i, Vector(i, 0));
        Matrix mtr_2(i, Vector(i, 0));
        result = 0;

        fill_mtr(mtr_1);
        fill_mtr(mtr_2);

        for (int j = 0; j < COUNT_CICLE; j++)
        {
            Matrix mtr_res(i, Vector(i, 0));

            start = std::chrono::system_clock::now();
            mul_vinograd(mtr_1, mtr_2, mtr_res);
            end = std::chrono::system_clock::now();

            result += std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
        }

        result /= COUNT_CICLE;
        write_to_file(file, i, result);
        cout << result << " ms" << endl;
    }
    file << std::endl;
    file.close();

    // Многопоточные тесты
    for (int k = 1; k <= 32; k *= 2)
    {
        // Многопоточные четные
        cout << k << " threads even" << endl;

        char fname_even[30] = "time_";
        char k_str[6];
        sprintf(k_str, "%d", k);
        strcat(fname_even, k_str);
        strcat(fname_even, "_th_even.txt");

        file.open(fname_even, std::ios::out);

        for(int i = 100; i <= MAX_SIZE; i += 100)
        {
            cout << "matrix " << i << " x " << i << " ";
            Matrix mtr_1(i, Vector(i, 0));
            Matrix mtr_2(i, Vector(i, 0));
            result = 0;

            fill_mtr(mtr_1);
            fill_mtr(mtr_2);

            for (int j = 0; j < COUNT_CICLE; j++)
            {
                Matrix mtr_res(i, Vector(i, 0));

                start = std::chrono::system_clock::now();
                mul_vinograd_threads(k, mtr_1, mtr_2, mtr_res);
                end = std::chrono::system_clock::now();

                result += std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
            }

            result /= COUNT_CICLE;
            write_to_file(file, i, result);
            cout << result << " ms" << endl;
        }

        file << std::endl;
        file.close();

        // Многопоточные нечетные
        cout << k << " threads odd" << endl;

        char fname_odd[30] = "time_";
        strcat(fname_odd, k_str);
        strcat(fname_odd, "_th_odd.txt");

        file.open(fname_odd, std::ios::out);

        for(int i = 101; i <= MAX_SIZE + 1; i += 100)
        {
            cout << "matrix " << i << " x " << i << " ";
            Matrix mtr_1(i, Vector(i, 0));
            Matrix mtr_2(i, Vector(i, 0));
            result = 0;

            fill_mtr(mtr_1);
            fill_mtr(mtr_2);

            for (int j = 0; j < COUNT_CICLE; j++)
            {
                Matrix mtr_res(i, Vector(i, 0));

                start = std::chrono::system_clock::now();
                mul_vinograd_threads(k, mtr_1, mtr_2, mtr_res);
                end = std::chrono::system_clock::now();

                result += std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
            }

            result /= COUNT_CICLE;
            write_to_file(file, i, result);
            cout << result << " ms" << endl;
        }

        file << std::endl;
        file.close();

    }
    std::cout << "DONE!";
}
