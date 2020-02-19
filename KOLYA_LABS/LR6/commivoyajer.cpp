#include "commivoyajer.h"


double exhaustive_search(Matrix &m)
{
    int n = m.GetN();
    std::vector<bool> visited;
    std::vector<double> paths;
    std::list<int> path;
    for(int i = 0; i < n; i++)
        visited.push_back(false);
    for(int i = 0; i < n; i++)
    {
        visited[i] = true;
        path.push_back(i);
        paths.push_back(search_for_node(m, visited, path));
        path.pop_back();
        visited[i] = false;
    }
    double res = paths[0];
    for(int i = 0; i < n; i++)
        res = std::min(res, paths[i]);
    return res;
}

double search_for_node(Matrix &m, std::vector<bool> visited, std::list<int> path)
{
    int &cur_node = path.back();
    double p;
    double res;
    bool flag = false;
    if (path.size() ==(unsigned int) m.GetN())
    {
        int first = path.front();
        int last = path.back();
        return m[last][first];
    }
    for(unsigned int i = 0; i < visited.size(); i++)
    {
        if (!visited[i])
        {
            p = m[cur_node][i];
            visited[i] = true;
            path.push_back(i);
            p += search_for_node(m, visited, path);
            if (!flag)
            {
                res = p;
                flag = true;
            }
            else
                res = std::min(res, p);
            visited[i] = false;
            path.pop_back();
        }
    }
    return res;
}

double ant_alg(Matrix &m, double alpha, double beta, double Q, double ro, int max_time)
{
    double res;
    unsigned int n = m.GetN();
    Matrix pheromones = Matrix(n, n, 0.1);
    std::vector<ant> ants;
    //std::vector<int> routes;
    for(int t = 0; t < max_time; t++)
    {
        ants.clear();
        for(unsigned int i = 0; i < n; i++)
        {
            ant cur_ant;
            cur_ant.route.push_back(i);
            cur_ant.sum_route = 0;
            for(unsigned int j = 0; j < n; j++)
                cur_ant.visited.push_back((j == i) ? true : false);
            ants.push_back(cur_ant);
        }
        for (int i = 0; i < n; i++)
        {
            Matrix pheromones_iter(n, n, 0);
            for(unsigned int j = 0; j < ants.size(); j++)
            {
                double sum_chance = 0, chance = 0;
                bool flag = false;
                ant cur_ant = ants[j];
                int cur_city = cur_ant.route.back();
                for(unsigned int k = 0; k < n; k++)
                {
                    if (cur_ant.visited[k] == false)
                    {
                        sum_chance += pow(pheromones[cur_city][k], alpha) * pow(1/(m[cur_city][k]), beta);
                        flag = true;
                    }
                }
                if (flag)
                {
                    srand(time(NULL));
                    float x = (rand()%1000)/((double)1000);
                    unsigned int k = 0;
                    for(; (x > 0) && (k < n); k++)
                    {
                        if (cur_ant.visited[k] == false)
                        {
                            chance = pow(pheromones[cur_city][k], alpha) * pow(1/(m[cur_city][k]), beta);
                            chance /= sum_chance;
                            x -= chance;
                        }
                    }
                    k--;
                    ants[j].route.push_back(k);
                    ants[j].visited[k] = true;
                    ants[j].sum_route += m[cur_city][k];
                    pheromones_iter[cur_city][k] += Q/(m[cur_city][k]);
                }
            }
            for(unsigned int ii = 0; ii < n; ii++)
                for(unsigned int j = 0; j < n; j++)
                    pheromones[ii][j] = (1 - ro) * pheromones[ii][j] + pheromones_iter[ii][j];
        }

        res = ants[0].sum_route + m[ants[0].route.back()][ants[0].route.front()];
        for(auto iter = ants.cbegin(); iter != ants.cend(); ++iter)
        {
            res = std::min(res, iter->sum_route + m[iter->route.back()][iter->route.front()]);
        }
    }
    return res;
}
