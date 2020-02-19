#include "aco.h"
#include "print.h"

std::random_device rd;
std::mt19937 g(rd());

double probability(int to, int size, int n,
    const std::vector<int> &ant, const Matrix &pheromone, const Matrix &dist,
    double alpha, double betta) {
    for (int i = 0; i < size; ++i) {
        if (to == ant[i]) {
            return 0;
        }
    }

    double sum = 0.0;
    int from = ant[size - 1];

    for (int j = 0; j < n; ++j) {
        bool flag = true;

        for (int i = 0; i < size; ++i) {
            if (j == ant[i]) {
                flag = false;
            }
        }

        if (flag) {
            sum += pow(pheromone[from][j], alpha) * pow(dist[from][j], betta);
        }
    }

    return pow(pheromone[from][to], alpha) * pow(dist[from][to], betta) / sum;
}

double aco(Matrix matrix, std::vector<int> &way, double alpha, double rho, int t_max) {
    double betta = 1 - alpha;
    int n = matrix.size();
    int m = n;
    double min_len = -1;

    Matrix dist(n, std::vector<double>(n));
    Matrix pheromone(n, std::vector<double>(n, 1.0 / n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                dist[i][j] = 1.0 / matrix[i][j];
            }
        }
    }

    std::vector<std::vector<int>> ants(m, std::vector<int>(n, -1));
    std::vector<int> starts(n);
    for (int i = 0; i < n; ++i) {
        starts[i] = i;
    }
    
    // std::random_device rd;
    // std::mt19937 g(rd());
    std::shuffle(starts.begin(), starts.end(), g);
    for (int i = 0; i < m; ++i) {


        ants[i][0] = starts[i];
    }

    std::vector<double> len(m, 0);

    for (int t = 0; t < t_max; ++t) {
        for (int k = 0; k < m; ++k) {
            for (int i = 1; i < n; ++i) {
                int j_max = -1;
                double p_max = 0.0;
                
                for (int j = 0; j < n; ++j) {
                    if (ants[k][i - 1] != j) {
                        double p = probability(j, i, n, ants[k], pheromone, dist, alpha, betta);
                        if (p && p >= p_max) {
                            p_max = p;
                            j_max = j;
                        }
                    }
                }

                len[k] += matrix[ants[k][i - 1]][j_max];
                if (i == n - 1) {
                    len[k] += matrix[j_max][ants[k][0]];
                }

                ants[k][i] = j_max;
            }

            for (int i = 0; i < n; ++i) {
                int from = ants[k][i];
                int to = ants[k][(i + 1) % n];

                pheromone[from][to] += Q / len[k];
                pheromone[to][from] = pheromone[from][to];
            }

            if (len[k] < min_len || min_len < 0) {
                min_len = len[k];
                for (int i = 0; i < n; ++i) {
                    way[i] = ants[k][i];
                }
            }

            len[k] = 0;
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    pheromone[i][j] *= (1 - rho);
                }
            }
        }
    }

    return min_len;
}
