#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "total_search.h"
#include "aco.h"
#include "matrix.h"
#include "print.h"

int main() {
    /*int n = 0;

    do {
        cout << "Input number of vertices : ";
        cin >> n;

        if (cin.fail() || n <= 0) {
            cin.clear();
            cin.ignore(32767,'\n');
            cout << "Incorrect input!" << endl;
            n = 0;
        }
    } while (n < N_MIN || n > N_MAX);

    cout << "Input matrix of distances : " << endl;
    Matrix dist(n, vector<double>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double tmp = -1;

            do {
                cout << "[" << i + 1 << "][" << j + 1 << "] : ";
                cin >> tmp;

                if (cin.fail() || tmp < 0) {
                    cin.clear();
                    cin.ignore(32767,'\n');
                    cout << "Incorrect input!" << endl;
                    tmp = -1;
                }
            } while (tmp < 0);

            dist[i][j] = tmp;
        }
    }

    int start = -1;
    int end = -1;

    do {
        cout << "Input start vertex : ";
        cin >> start;

        if (cin.fail() || start < 1 || start > n) {
            cin.clear();
            cin.ignore(32767,'\n');
            cout << "Incorrect input!" << endl;
            start = -1;
        }
    } while (start < 1 || start > n);

    do {
        cout << "Input end vertex (except " << start << ") : ";
        cin >> end;

        if (cin.fail() || end < 1 || end > n || start == end) {
            cin.clear();
            cin.ignore(32767,'\n');
            cout << "Incorrect input!" << endl;
            end = -1;
        }
    } while (end < 1 || end > n || start == end);*/

    // Matrix dist0 = { { 0, 1, 2 },
    //                 { 3, 0, 4 },
    //                 { 5, 6, 0 } };

    // Matrix dist = { {  0, 5, 7, 10, 5 },
    //                 {  5, 0, 6,  2, 8 },
    //                 {  7, 6, 0,  8, 8 },
    //                 { 10, 2, 8,  0, 6 },
    //                 {  5, 8, 8,  6, 0 } };


    // 18
    // 1 -> 4 -> 3 -> 5 -> 2
    Matrix dist_1 = { { 0, 9, 8, 4, 10 },
                      { 6, 0, 4, 5, 7 },
                      { 5, 3, 0, 6, 2 },
                      { 1, 7, 2, 0, 5 },
                      { 2, 4, 5, 2, 0 } };
    
    // 13
    // 1 -> 2 -> 5 -> 4 -> 6 -> 3
    Matrix dist_2 = { { 0, 4, 4, 5, 4, 3 },
                      { 2, 0, 7, 1, 1, 6 },
                      { 2, 3, 0, 9, 4, 5 },
                      { 1, 3, 2, 0, 3, 1 },
                      { 7, 4, 1, 1, 0, 4 },
                      { 2, 3, 4, 7, 9, 0 } };
    
    // 38
    // 1 -> 6 -> 2 -> 4 -> 3 -> 5
    Matrix dist_3 = { { 0, 10, 5, 9, 16, 8 },
                      { 6, 0, 11, 8, 18, 19 },
                      { 7, 13, 0, 3, 4, 14 },
                      { 5, 9, 6, 0, 12, 17 },
                      { 5, 4, 11, 6, 0, 14 },
                      { 17, 7, 12, 13, 16, 0 } };
    
    Matrix dist_4 = { { 0, 9, 9, 1, 9, 9 },
                      { 9, 0, 9, 9, 1, 9 },
                      { 1, 9, 0, 9, 9, 9 },
                      { 9, 1, 9, 0, 9, 9 },
                      { 9, 9, 9, 9, 0, 1 },
                      { 9, 9, 1, 9, 9, 0 } };
    
    
    std::vector<int> way_(10, 0);
    
    // int start = 1, end = dist.size();

    // way_t way = aco(dist, --start, --end);

    // cout << "Way length : " << way.len << endl;
    // cout << "Way : " << way.vertex[0] + 1;
    // for (int i = 1; i < way.size; ++i) {
    //     cout << " -> " << way.vertex[i] + 1;
    // }

    // int min_len = aco0(dist, way_);

    // cout << endl << "Way length : " << min_len << endl;
    // cout << "Way : " << way_[0] + 1;
    // for (int i = 1; i < way_.size(); ++i) {
    //     cout << " -> " << way_[i] + 1;
    // }

    std::vector<Matrix> tmp = { dist_1, dist_2, dist_3, dist_4 };
    // vector<Matrix> tmp = { dist_1 };
    for (auto elem : tmp) {
        std::cout << "ACO: " << aco0(elem, way_) << std::endl;
        std::cout << "Way : " << way_[0] + 1;
        for (int i = 1; i < static_cast<int>(elem.size()); ++i) {
            std::cout << " -> " << way_[i] + 1;
        }

        std::cout << std::endl << "TOTAL: " << total_search(elem, way_) << std::endl;
        std::cout << "Way : " << way_[0] + 1;
        for (int i = 1; i < static_cast<int>(elem.size()); ++i) {
            std::cout << " -> " << way_[i] + 1;
        }
        std::cout << std::endl;
    }

    // cout << aco0(dist_1, way_) << endl;
    // cout << aco0(dist_2, way_) << endl;
    // cout << aco0(dist_3, way_) << endl;
    // int n = 10;

    // vector<int> starts(n);
    // for (int i = 0; i < n; ++i) {
    //     starts[i] = i;
    // }

    
    // random_device rd;
    // mt19937 g(rd());

    // for (int i = 1; i < 7; ++i) {
    //     shuffle(starts.begin(), starts.end(), g);
    //     copy(starts.begin(), starts.end(), std::ostream_iterator<int>(std::cout, " "));
    //     std::cout << "\n";
    // }

    return 0;
}
