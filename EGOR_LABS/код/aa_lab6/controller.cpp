#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "total_search.h"
#include "aco.h"
#include "matrix.h"
#include "print.h"
#include "res.h"
#include "controller.h"

void controller() {
        int n = 0;

        do {
            std::cout << "Input number of vertices : ";
            std::cin >> n;

            if (std::cin.fail() || n <= 0 || n < N_MIN || n > N_MAX) {
                std::cin.clear();
                std::cin.ignore(32767,'\n');
                std::cout << "Incorrect input!" << std::endl;
                n = 0;
            }
        } while (n < N_MIN || n > N_MAX);

        std::cout << "Input distances : " << std::endl;
        Matrix dist(n, std::vector<double>(n, 0));

        for (int i = 0; i < n; ++i) {
            std::cout << "input " << i << " rows: ";
            for (int j = 0; j < n; ++j) {

                double tmp = -1;

                do {
                    std::cin >> tmp;

                    if (std::cin.fail() || (j != i && tmp <= 0) || (j == i && abs(tmp) > 0.001)) {
                        std::cin.clear();
                        std::cin.ignore(32767,'\n');
                        std::cout << "Incorrect input! \n input " << i << " rows: ";
                        j = 0;
                        tmp = -1;
                    }
                } while (tmp < 0);

                dist[i][j] = tmp;

            }

        }
        std::cout <<  std::endl;

        std::cout << "Matrix distances:\n";
        for (int i = 0; i < n; ++i) {

            for (int j = 0; j < n; ++j) {
                std::cout << dist[i][j] << " ";
            }
            std::cout << "\n";
        }

        std::vector<int> ts_way(n, -1);
        std::vector<int> aco_way(n, -1);

        int ts_len = total_search(dist, ts_way);

        std::cout <<  std::endl;
        std::cout << "TOTAL SEARCH" << std::endl;
        std::cout << "Way length : " << ts_len << std::endl;
        print_way(ts_way);
        std::cout <<  std::endl;

        int aco_len = aco(dist, aco_way);

        std::cout << "ACO" << std::endl;
        std::cout << "Way length : " << aco_len << std::endl;
        print_way(aco_way);
        std::cout <<  std::endl;
}
