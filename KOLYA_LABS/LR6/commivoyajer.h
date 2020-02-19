#ifndef COMMIVOYAJER_H
#define COMMIVOYAJER_H

#include "matrix.h"
#include <list>
#include <vector>
#include <cstdlib>
#include <random>
#include <ctime>

struct ant
{
    std::vector<int> route;
    std::vector<bool> visited;
    double sum_route;
};

double exhaustive_search(Matrix &m);
double search_for_node(Matrix &m, std::vector<bool> visited, std::list<int> path);
double ant_alg(Matrix &m, double alpha, double beta, double Q, double ro, int max_time);

#endif // COMMIVOYAJER_H
