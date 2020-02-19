#include <cstdlib>
#include <iostream>
#include <memory>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <chrono>
#include <string>
#include "matrix.h"
#include "vinograd.h"

using namespace std;
/*
int main()
{
    ifstream f1;
    f1.open("in_1.txt");
    Matrix matr1 = Matrix(f1);
    f1.close();
    f1.open("in_1.txt");
    Matrix matr2 = Matrix(f1);
    Matrix v = Vinograd(matr1, matr2);
    Matrix vp1 = Vinograd_Parallell1(matr1, matr2, 4);
    Matrix vp2 = Vinograd_Parallell2(matr1, matr2, 4);
    cout << matr1 <<"\n" <<matr2 <<"\nVinograd\n" << v <<"\nVinograd parallell 1\n" << vp1 <<"Vinograd parallell 2\n" << vp2;
    return 0;
}
*/

int main()
{
    auto t3 = std::chrono::high_resolution_clock::now();
    ifstream f1;
    ofstream f2, f3, f4, f5;
    f2.open("resultsc1.csv");
    f3.open("resultsn1.csv");
    f4.open("resultsc2.csv");
    f5.open("resultsn2.csv");

    std::string fname;
    for(int i = 800; i < 801; i += 100)
    {

        cout << "\n" << i << "\n";
        fname = "matr_" + to_string(i) + ".txt";
        f1.open(fname);
        Matrix matr1 = Matrix(f1);
        f1.close();
        f1.open(fname);
        Matrix matr2 = Matrix(f1);
        f1.close();
        fname = "matr_" + to_string(i + 1) + ".txt";
        f1.open(fname);
        Matrix matr3 = Matrix(f1);
        f1.close();
        f1.open(fname);
        Matrix matr4 = Matrix(f1);
        f1.close();

        auto t1 = std::chrono::high_resolution_clock::now();
//        for(int j = 0; j < 10; j++)
 //           Matrix v1 = Vinograd(matr1, matr2);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto t = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
/*       f2 << t<< "\t";
        t1 = std::chrono::high_resolution_clock::now();
        for(int j = 0; j < 10; j++)
            Matrix v2 = Vinograd(matr3, matr4);
        t2 = std::chrono::high_resolution_clock::now();
        t = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
        f3 << t<< "\t";*/
        for(int j = 1; j <= 16; j *= 2)
        {
            cout << " " << "j";
            t1 = std::chrono::high_resolution_clock::now();
            //for(int k = 0; k < 5; k++)
                Matrix v3 = Vinograd_Parallell1(matr1, matr2, j);
            t2 = std::chrono::high_resolution_clock::now();
            t = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
            f2 << t << "\t";
            f4 << t << "\t";
            cout << t << "\t";
            t1 = std::chrono::high_resolution_clock::now();
            //for(int k = 0; k < 5; k++)
                Matrix v4 = Vinograd_Parallell1(matr3, matr4, j);
            t2 = std::chrono::high_resolution_clock::now();
            t = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
            f3 << t<< "\t";
            f5 << t<< "\t";
            cout << t << "\t";
            t1 = std::chrono::high_resolution_clock::now();
            //for(int k = 0; k < 5; k++)
                Matrix v5 = Vinograd_Parallell2(matr1, matr2, j);
            t2 = std::chrono::high_resolution_clock::now();
            t = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
            f4 << t<< "\t";
            cout << t << "\t";
            t1 = std::chrono::high_resolution_clock::now();
            //for(int k = 0; k < 5; k++)
                Matrix v6 = Vinograd_Parallell2(matr3, matr4, j);
            t2 = std::chrono::high_resolution_clock::now();
            t = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
            f5 << t << "\t";
            cout << t << "\t";
        }
        f2 << "\n";
        f3 << "\n";
        f4 << "\n";
        f5 << "\n";
    }
    f2.close();
    f3.close();
    f4.close();
    f5.close();
    auto t4 = std::chrono::high_resolution_clock::now();
    cout << std::chrono::duration_cast<std::chrono::microseconds>( t3 - t4 ).count();
    return 0;
}

