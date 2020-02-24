#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "matrix.h"
#include "commivoyajer.h"
/*
int main()
{
    double r = 0, r1 = 0;

    for(int i = 3; i < 11; i++)
    {
        std::string fname = std::string("matr_");
        fname += std::to_string(i);
        fname += std::string("10.txt");
        std::ifstream f(fname);
        Matrix matr = Matrix(f);
        clock_t start, stop, start1, stop1;
        start = clock();
        exhaustive_search(matr);
        stop = clock();
        start1 = clock();
        ant_alg(matr, 2, 3,5, 0.2, 3);
        stop1 = clock();
        std::ofstream log("log1.txt", std::ios_base::app);
        log << i << "\t" << stop1 - start1 << "\t" << stop - start <<"\n";

    }
    return 0;
}
*/
int main()
{
    double r = 0;

    for(int i = 3; i < 11; i++)
    {
        double alpha = 0, beta = 0, ro = 0, t_max = 5;
        double alpha1 = 0, beta1 = 0, ro1 = 0, t_max1 = 5;
        double minv = 0;
        std::string fname = std::string("matr_");
        fname += std::to_string(i);
        fname += std::string("10.txt");
        std::ifstream f(fname);
        Matrix matr = Matrix(f);
        r = exhaustive_search(matr);
        int max_c = 0;
        int c = 0;


        bool flag = false;




        for(t_max = 1;t_max < 20; t_max++)
        {



                c = 0;
                for(beta = 1;beta < 11; beta++)
                    {

                    for(alpha = 1;alpha < 11; alpha++)
                    {
                        for(ro = 0.1;ro < 1 - 0.01; ro += 0.1)
                    {
                        double cv = ant_alg(matr,alpha,beta,5,ro,t_max);
                        //std::cout << i << "\t" << alpha << "\t" << beta << "\t" << ro << "\t" << t_max << "\t" << cv << "\t" << r <<"\n";
                        if((!flag) || (cv < minv))
                        {
                            //minv = cv;
                            //alpha1 = alpha;
                            //beta1 = beta;
                            //ro1 = ro;
                            //t_max1 = t_max;
                            flag = true;
                       }
                       if(cv == r)
                           c++;
                    }

                }
            }
            if(c > max_c)
            {
                alpha1 = alpha;
                beta1 = beta;
                ro1 = ro;
                t_max1 = t_max;
                std::cout << c <<"\t" << max_c <<"\n";
                max_c = c;
            }
        }
        std::ofstream log("log.txt", std::ios_base::app);
        log << i << "\t"<< alpha1 << "\t" << beta1 << "\t" << ro1 << "\t" << t_max1 << "\t" << minv << "\t" << r <<"\n";
    }
    return 0;
}

