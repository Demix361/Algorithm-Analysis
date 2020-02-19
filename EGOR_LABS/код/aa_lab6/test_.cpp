#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include "matrix.h"
#include "total_search.h"
#include "aco.h"
#include "print.h"

Matrix get_rand_matrix(int n);

//void research_test(std::string file_name) {
//    std::cout << std::endl << "--[ " << file_name << " ]--" << std::endl;

//    std::ofstream fout(file_name);

//    int n = 10;
//    // Matrix dist = { { 0, 98, 96, 79, 96, 62, 7, 31, 8, 23 },
//    //                 { 80, 0, 8, 85, 8, 5, 83, 61, 16, 99 },
//    //                 { 67, 6, 0, 3, 19, 9, 58, 91, 21, 41 },
//    //                 { 15, 57, 74, 0, 70, 47, 82, 75, 54, 81 },
//    //                 { 10, 48, 86, 40, 0, 36, 98, 12, 32, 86 },
//    //                 { 27, 75, 3, 17, 43, 0, 25, 2, 84, 61 },
//    //                 { 98, 23, 2, 54, 44, 37, 0, 98, 13, 17 },
//    //                 { 94, 6, 55, 12, 1, 30, 57, 0, 31, 100 },
//    //                 { 66, 96, 21, 71, 2, 62, 72, 66, 0, 66 },
//    //                 { 30, 93, 39, 61, 94, 50, 64, 1, 79, 0 }
//    // };
//    // Matrix dist = { { 0, 71, 6, 68, 30, 18, 62, 1, 81, 81 },
//    //                 { 87, 0, 30, 80, 51, 1, 76, 25, 68, 54 },
//    //                 { 87, 5, 0, 59, 73, 87, 71, 63, 92, 33 },
//    //                 { 27, 71, 14, 0, 13, 64, 47, 48, 66, 93 },
//    //                 { 34, 62, 57, 63, 0, 13, 28, 99, 100, 4 },
//    //                 { 77, 10, 42, 59, 99, 0, 68, 79, 72, 28 },
//    //                 { 61, 71, 32, 6, 62, 42, 0, 38, 78, 38 },
//    //                 { 16, 39, 26, 70, 98, 94, 46, 0, 63, 79 },
//    //                 { 32, 55, 90, 48, 92, 63, 20, 51, 0, 3 },
//    //                 { 16, 79, 30, 50, 21, 65, 78, 58, 93, 0 }
//    // };

//    int num = 5;
//    std::vector<int> check(2090);
//    for (int i = 0; i < num; ++i) {
//        std::cout << "i = " << i << std::endl;
//        Matrix dist = get_rand_matrix(n);

//        std::vector<int> ts_way(n, -1);
//        int ts_len = total_search(dist, ts_way);

//        std::vector<int> aco_way(n, -1);
//        // bool res = false;

//        int k = 0;
//        for (double alpha = 0; alpha <= 1; alpha += 0.1) {  // alpha e [0; 1]
//            std::cout << "alpha = " << alpha << std::endl;
//            for (double rho = 0.1; rho < 1; rho += 0.1) {   // pho e [0; 1)
//                std::cout << "rho = " << rho << std::endl;
//                for (int t = 50; t < 1000; t += 50, ++k) {
//                    // std::cout << alpha << " " << rho << " " << t << " ";
//                    // fout << alpha << " " << rho << " " << t << " ";
//                    if (aco(dist, aco_way, alpha, rho, t) == ts_len) {
//                        ++check[k]; }
//                    //     res = true;
//                    // } else {
//                    //     res = false;
//                    // }

//                    // std::cout << res << std::endl;
//                    // fout << res << std::endl;
//                }
//            }
//        }
//    }

//    int k = 0;
//    bool res = false;
//    for (double alpha = 0; alpha <= 1; alpha += 0.1) {  // alpha e [0; 1]
//        for (double rho = 0.1; rho < 1; rho += 0.1) {   // pho e [0; 1)
//            for (int t = 50; t < 1000; t += 50, ++k) {
//                // std::cout << alpha << " " << rho << " " << t << " ";
//                fout << alpha << " " << rho << " " << t << " ";
//                if (check[k] > num / 2) {
//                    res = true;
//                } else {
//                    res = false;
//                }

//                // std::cout << res << std::endl;
//                fout << res << std::endl;
//            }
//        }
//    }

//    fout.close();
//}

//Matrix get_rand_matrix(int n) {
//    // if (n <= N_MIN) {
//    //     return Matrix(n, std::vector<double>(n, -1));
//    // }

//    std::srand(std::time(0));

//    Matrix dist(n, std::vector<double>(n, 0));

//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            if (i != j) {
//                int tmp = 1 + std::rand() % 100;
//                dist[i][j] = 0 == tmp ? 1 : tmp;
                
//                // std::cout << "( " << i + 1 << " -> " << j + 1 << " ) : ";
//                // std::cout << dist[i][j] << std::endl;
//            }
//        }
//    }

//    // for (int i = 0; i < n; ++i) {
//    //     std::cout << "{ ";
//    //     for (int j = 0; j < n; ++j) {
//    //         if (j == n - 1) {
//    //             std::cout << dist[i][j];
//    //         } else {
//    //             std::cout << dist[i][j] << ", ";
//    //         }
//    //     }
//    //     std::cout << " },";
//    //     std::cout << std::endl;
//    // }

//    return dist;
//}

void test() {
    int n = 5;

    for (int i = 3; i <= 10; ++i) {
        // std::cout << "check_1" << std::endl;
        Matrix dist = get_rand_matrix(i);
        std::vector<int> ts_way(n, -1);
        std::vector<int> aco_way(n, -1);
        // std::cout << "check_2" << std::endl;

        int ts_len = total_search(dist, ts_way);
        // std::cout << "check_3" << std::endl;
        int aco_len = aco(dist, aco_way);
        std::cout << aco_len << std::endl;
        // std::cout << "check_4" << std::endl;

        std::cout << "n = " << i << std::endl;
        std::cout << (ts_len == aco_len ? "OK" : "FAIL") << std::endl;
        board();
    }
    std::cout << "END" << std::endl;
}

//int main() {
//    research_test("research.txt");
//    // int n = 10;
//    // Matrix dist = get_rand_matrix(10);
//    //     Matrix dist = { { 0, 71, 6, 68, 30, 18, 62, 1, 81, 81 },
//    //                 { 87, 0, 30, 80, 51, 1, 76, 25, 68, 54 },
//    //                 { 87, 5, 0, 59, 73, 87, 71, 63, 92, 33 },
//    //                 { 27, 71, 14, 0, 13, 64, 47, 48, 66, 93 },
//    //                 { 34, 62, 57, 63, 0, 13, 28, 99, 100, 4 },
//    //                 { 77, 10, 42, 59, 99, 0, 68, 79, 72, 28 },
//    //                 { 61, 71, 32, 6, 62, 42, 0, 38, 78, 38 },
//    //                 { 16, 39, 26, 70, 98, 94, 46, 0, 63, 79 },
//    //                 { 32, 55, 90, 48, 92, 63, 20, 51, 0, 3 },
//    //                 { 16, 79, 30, 50, 21, 65, 78, 58, 93, 0 }
//    // };

//    // Matrix dist = { { 0, 31, 83, 36, 80, 32, 50, 67, 31, 74 },
//    //                 { 59, 0, 66, 35, 45, 49, 53, 5, 100, 78 },
//    //                 { 49, 95, 0, 41, 95, 5, 84, 55, 42, 77 },
//    //                 { 40, 69, 12, 0, 17, 77, 46, 86, 42, 63 },
//    //                 { 7, 18, 41, 50, 0, 40, 47, 96, 62, 30 },
//    //                 { 38, 53, 26, 4, 98, 0, 79, 45, 1, 23 },
//    //                 { 23, 33, 6, 72, 8, 8, 0, 97, 90, 79 },
//    //                 { 37, 5, 93, 94, 62, 86, 100, 0, 58, 83 },
//    //                 { 75, 22, 62, 16, 82, 18, 38, 51, 0, 32 },
//    //                 { 83, 88, 44, 46, 16, 41, 20, 3, 62, 0 }
//    // };

//    // std::vector<int> ts_way(n, -1);
//    // std::vector<int> aco_way(n, -1);

//    // int ts_len = total_search(dist, ts_way);
//    // std::cout << "TOTAL : " << ts_len << std::endl;
//    // print_way(ts_way);
//    // int aco_len = aco(dist, aco_way, 0.5, 0.5, 50);
//    // std::cout << "ACO 1 : " << aco_len << std::endl;
//    // print_way(aco_way);
//    // std::cout << (ts_len == aco_len ? "OK" : "FAIL") << std::endl;

//    // aco_len = aco(dist, aco_way, 0.5, 0.5, 1000);
//    // std::cout << "ACO 2 : " << aco_len << std::endl;
//    // print_way(aco_way);
//    // std::cout << (ts_len == aco_len ? "OK" : "FAIL") << std::endl;


//    return 0;
//}
