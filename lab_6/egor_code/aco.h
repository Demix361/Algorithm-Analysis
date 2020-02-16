#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include "matrix.h"

#define ALPHA 0.5
#define RHO 0.5
#define T_MAX 300
#define Q 100

double aco(Matrix matrix, std::vector<int> &way,
    double alpha = ALPHA, double rho = RHO, int t_max = T_MAX);
double probability(int to, int size, int n,
    const std::vector<int> &ant, const Matrix &pheromone, const Matrix &dist,
    double alpha, double betta);
