#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <limits>
#include <chrono>
#include "matrix.h"
#include "total_search.h"
#include "aco.h"
#include "print.h"

#define MAX_N 100
#define MIN_N 1
#define STEP 10

Matrix get_rand_matrix(int n) {
    // std::srand(std::time(0));

    Matrix dist(n, std::vector<double>(n, 0));
    // std::cout << "Matrix dist = {" << std::endl;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                int tmp = (std::abs(std::rand() % (MAX_N - MIN_N)) + MIN_N) * STEP; // (std::rand() % 10) * 10;
                dist[i][j] = 0 == tmp ? 10 : tmp;
            }
        }
        // std::cout << "    { ";
        // for (int j = 0; j < n - 1; ++j) {
        //     std::cout << dist[i][j] << ", ";
        // }
        // if (i != n - 1) {
        //     std::cout << dist[i][n - 1] << " }, " << std::endl;
        // } else {
        //     std::cout << dist[i][n - 1] << " } " << std::endl;
        // }
    }
    // std::cout << "}; " << std::endl << std::endl;

    return dist;
}

void research_test(std::string file_name, int np) {
    std::cout << std::endl << "--[ " << file_name << " ]--" << std::endl;
    std::ofstream fout(file_name);
    std::srand(std::time(0));

    int n = np;
    int size = 5;
    std::vector<Matrix> data(size);
    for (int i = 0; i < size; ++i) {
        data[i] = get_rand_matrix(n);
    }

    std::vector<double> ans(size, -1);
    std::vector<int> ts_way(n, -1);
    for (int i = 0; i < size; ++i) {
        ans[i] = total_search(data[i], ts_way);
    }

    std::vector<int> aco_way(n, -1);
    const int num = 5;
    const double eps = 1e-3;

    double aco_len = -1;
    const int w = 9;

    fout << std::setw(w)
    << "alpha" << std::setw(w)
    << "rho" << std::setw(w)
    << "t" << std::setw(w)
    << "total" << std::setw(w)
    << "aco_min" << std::setw(w)
    << "aco_max" << std::endl;

    for (int i = 0; i < size; ++i) {

        fout << "{ DATA " << i + 1 << " }" << std::endl;
        std::cout << i + 1 << std::endl;

        for (double alpha = 0; (alpha - 1) <= eps; alpha += 0.1) {  // alpha e [0; 1]
            for (double rho = 0.1; (rho - 1) < eps; rho += 0.1) {   // pho e [0; 1)
                int step = 10;
                for (int t = 10; t <= 200; t += step) {
                    // if (200 == t) {
                    //     step = 50;
                    // }

                    double aco_min = std::numeric_limits<double>::max();
                    double aco_max = std::numeric_limits<double>::min();

                    for (int j = 0; j < num; ++j) {
                        aco_len = aco(data[i], aco_way, alpha, rho, t);
                        aco_min = std::min(aco_len, aco_min);
                        aco_max = std::max(aco_len, aco_max);
                    }

                    fout << std::setw(w)
                    << alpha << std::setw(w)
                    << rho << std::setw(w)
                    << t << std::setw(w)
                    << ans[i] << std::setw(w)
                    << aco_min << std::setw(w)
                    << aco_max << std::endl;

                    // if (aco_min == ans[i] && aco_max == ans[i]) {
                    //     t = 1000;
                    // }
                }
            }
        }
    }

    fout.close();
}

void time_test(int np = 10) {
    std::srand(std::time(0));

    std::chrono::time_point<std::chrono::system_clock> st, et, sa, ea;

    int n = np;
    int size = 5;
    Matrix data(n);
    std::vector<int> ts_way(n, -1);
    std::vector<int> aco_way(n, -1);
    for (int i = 0; i < size; ++i) {
        std::cout << i + 1 << std::endl;
        data = get_rand_matrix(n);

        unsigned long long int t1 = 0, t2;

        for (int j = 0; j < 2 * size; ++j) {

            st = std::chrono::system_clock::now();
            total_search(data, ts_way);
            et = std::chrono::system_clock::now();

            sa = std::chrono::system_clock::now();
            aco(data, ts_way);
            ea = std::chrono::system_clock::now();

            t1 += std::chrono::duration_cast<std::chrono::nanoseconds>
            (et - st).count();

            t2 += std::chrono::duration_cast<std::chrono::nanoseconds>
            (ea - sa).count();
        }

        std::cout << "TS  : " << ((long double)(t1) / size) << std::endl;
        std::cout << "ACO : " << ((long double)(t2) / size) << std::endl;
    }
}

int research_() {
    //research_test("RES_1.txt", 5);
    //research_test("RES_10x10.txt", 10);
//    research_test("RES_3.txt", 15);
//    research_test("RES_10x10_10_1000_10.txt", 10);
//    research_test("RES_5x5_10_1000_10.txt", 5);
    time_test();

    return 0;
}
