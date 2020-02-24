#include <algorithm>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <math.h>
#include <stdlib.h>
#include <vector>

//#define MAX_CITY 10
extern int MAX_CITY = 10;
#define MAX_L 15
#define MIN_L 1

#define ALPHA 0.62
#define BETHA (1 - ALPHA)
#define RO 0.25
#define QU (MAX_CITY * MAX_L/2)

template <class t>
t** create_mat(int m, int n)
{
    t** mat = new t* [m];

    for (int i = 0; i < m; ++i)
        mat[i] = new t[n];

    return mat;
}

int** create_cities(bool one = false)
{
    int** res = create_mat<int>(MAX_CITY, MAX_CITY);

    srand(time(nullptr));
    for (int i = 0; i < MAX_CITY; ++i)
    {
        res[i][i] = 0;
        for (int j = i + 1; j < MAX_CITY; ++j)
        {
            int value;
            if (!one)
                value = (rand() % MAX_L + MIN_L);
            else
                value = 1;

            res[i][j] = value;
            res[j][i] = value;
        }
    }

    return res;
}

struct Ant
{
public:
    Ant(int i):
        start_city(i), cur_city(i), Lk(0)
    {
        route = new int[MAX_CITY];
        Jk = new float[MAX_CITY];
    }

    void show_route()
    {
        for (int i = 0; i < MAX_CITY; ++i)
            printf("%d\t", route[i]);
    }

    bool city_passed(int c)
    {
        for (int i = 0; i < MAX_CITY; ++i)
            if (c == route[i])
                return true;
        return false;
    }

    int start_city;
    int cur_city;
    int Lk;

    int* route;
    float* Jk;
};

class Solver
{
public:
    int ss = 0;

    Solver():
        min_length(0), min_length_full(0)
    {
        min_path = new int[MAX_CITY];
        cities = create_mat<int>(MAX_CITY, MAX_CITY);
        fill_cities();
    }

    void muravei(float a, float r, int tm, bool output = true)
    {
        alfa=a;
        betha=1 - a;
        ro=r;
        tmax=tm;
        create_colony();

        float** vision = create_mat<float>(MAX_CITY, MAX_CITY);
        for (int i = 0; i < MAX_CITY; ++i)
        {
            for (int j = i; j < MAX_CITY; ++j)
            {
                if (i != j)
                {
                    vision[i][j] = (float)1/cities[i][j];
                    vision[j][i] = vision[i][j];
                }
                else
                {
                    vision[i][j] = 0;
                }
            }
        }

        float** substance = create_mat<float>(MAX_CITY, MAX_CITY);
        for (int i = 0; i < MAX_CITY; ++i)
        {
            for (int j = 0; j < MAX_CITY; ++j)
            {
                substance[i][j] = 0.5;
            }
        }

        float** weight = create_mat<float>(MAX_CITY, MAX_CITY);
        recalc_weight(weight, substance, vision);

        float** delta_substance = create_mat<float>(MAX_CITY, MAX_CITY);
        for (int i = 0; i < MAX_CITY; ++i)
        {
            for (int j = 0; j < MAX_CITY; ++j)
            {
                delta_substance[i][j] = 0;
            }
        }

        min_length = std::numeric_limits<int>::max();

        for (int t = 0; t < tmax; ++t)
        {
            for (unsigned int i = 0; i < MAX_CITY; ++i)
            {
                set_ant(ants_colony[i]);
                move_ant(ants_colony[i], weight, substance, QU);
            }

            int best = -1;
            for (unsigned int i = 0; i < MAX_CITY; i++)
                if (ants_colony[i]->Lk < min_length)
                {
                    best = i;
                    min_length = ants_colony[i]->Lk;
                }

            if (best != -1)
                copy_array<int*, int*>(min_path, ants_colony[best]->route);

            recalc_substance(substance, delta_substance);
            recalc_weight(weight, substance, vision);
        }

        min_length += cities[min_path[MAX_CITY-1]][min_path[0]];

        if (output)
        {
            std::cout << "\nMuravey:\n";
            get_result<int*>(min_path, min_length);
        }
    }

    void perebor(bool output = true)
    {
        std::pair <int, std::vector<int>> res = this->absolute_find();
        min_path_full = res.second;
        min_length_full = res.first;

        if (output)
        {
            std::cout << "\nFull perebor:\n";
            get_result<std::vector<int>>(min_path_full, min_length_full);
        }
    }

    std::pair <int, std::vector<int>> absolute_find()
    {
        int n = MAX_CITY;
        std::vector<bool> visited(n, 0);
        std::vector<int> cur_path;
        std::vector<int> min_path;
        int cur_len = 0;
        int min_path_len = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            cur_path.clear();
            cur_path.push_back(i);
            fill(visited.begin(), visited.end(), 0);
            visited[i] = 1;
            cur_len = 0;
            absolute(min_path, min_path_len, cur_path, visited, cur_len);
        }
        return std::pair<int, std::vector<int>>(min_path_len, min_path);
    }

    void absolute(std::vector<int> &min_path, int &min_d, std::vector<int> &cur_path, std::vector<bool> &visited, int &cur_len)
    {
        size_t M = MAX_CITY;
        if (cur_path.size() == M)
        {
            ss++;
            int tmp = cities[cur_path.back()][cur_path[0]];
            if (cur_len + tmp < min_d)
            {
                min_path = cur_path;
                min_d = cur_len + tmp;
            }
            return;
        }
        for (size_t i = 0; i < M; i++)
        {
            if (!visited[i])
            {
               int tmp = cities[cur_path.back()][i];
               if (cur_len + tmp > min_d)
                   continue;
               cur_len += tmp;
               cur_path.push_back(i);
               visited[i] = 1;
               absolute(min_path, min_d, cur_path, visited, cur_len);
               visited[i] = 0;
               cur_path.pop_back();
               cur_len -= tmp;
            }
        }
    }

    int** get_cities()
    {
        return cities;
    }

    void set_cities(int** city)
    {
        if (city != cities)
        {
            clear_cities();
            cities = city;
        }
    }

    int get_lenght_full()
    {
        return min_length_full;
    }

    int get_lenght()
    {
        return min_length;
    }

private:
    int tmax;
    int** cities;
    int min_length;
    int min_length_full;
    float alfa, betha, ro;

    int* min_path;
    std::vector<Ant*> ants_colony;
    std::vector<int> min_path_full;

    template <class left, class right>
    void copy_array(left &dst, right frm)
    {
        for (int i = 0; i < MAX_CITY; ++i)
            dst[i] = frm[i];
    }

    template <class type>
    void get_result(type path, int length)
    {
        std::cout << "Found way: ";
        for (unsigned int i = 0; i < MAX_CITY; ++i)
        {
            printf("%d\t", path[i]);
        }
        std::cout << '\n' << "Found length: " << length << "\n\n";
    }

    void create_colony()
    {
        for (int i = 0; i < MAX_CITY; i++)
        {
            Ant* ant = new Ant(i);
            ants_colony.push_back(ant);
        }
    }

    void set_ant(Ant* &ant)
    {
        int start = ant->start_city;
        ant->cur_city = start;
        ant->Lk = 0;
        for (int i = 0; i < MAX_CITY; i++)
        {
            ant->route[i] = -1;
            ant->Jk[i] = 1;
        }

        ant->route[0] = start;
        ant->Jk[start] = 0;
    }

    int choose_next(float* prob)
    {
        int i = 0;
        srand(time(nullptr));
        float r = (float)(rand())/RAND_MAX;

        if (r == 0.)
        {
            while (prob[i++] <= 0);
            return --i;
        }

        while (r > 0)
            r -= prob[i++];

        return --i;

    }

    int length_of_route(int* route)
    {
        int length = 0;
        for (int i = 0; i < MAX_CITY - 1; i++)
            length += cities[route[i]][route[i + 1]];

        return length;
    }

    void move_ant(Ant* &ant, float** weight, float** &delta_substance, int q)
    {
        int i = 1;
        float* prob = new float[MAX_CITY];
        while (i < MAX_CITY)
        {
            double sumWeight = 0;
            for (int j = 0; j < MAX_CITY; j++)
                sumWeight += weight[ant->cur_city][j] * ant->Jk[j];

            for (int j = 0; j < MAX_CITY; j++)
            {
                if (ant->city_passed(j))
                {
                    prob[j] = 0;
                }
                else
                {
                    prob[j] = (float)weight[ant->cur_city][j] / sumWeight * ant->Jk[j];
                }
            }

            int next = choose_next(prob);
            ant->cur_city = next;
            ant->Jk[next] = 0;
            ant->route[i++] = next;
        }

        ant->Lk = length_of_route(ant->route);
        add_substance(delta_substance, ant->route, ant->Lk, q);
    }

    void add_substance(float** &delta_substance, int* route, float lk, float q)
    {
        float d_substance = (float) q/lk;
        for (int i = 0; i < MAX_CITY - 1; i++)
            delta_substance[route[i]][route[i + 1]] += d_substance;
    }

    void recalc_weight(float** &mat, float **substance, float **vision)
    {
        for (int i = 0; i < MAX_CITY; ++i)
        {
            for (int j = 0; j < MAX_CITY; ++j)
            {
                mat[i][j] = pow(substance[i][j], alfa) * pow(vision[i][j], betha);
            }
        }
    }

    void recalc_substance(float** &substance, float** &delta_substance)
    {
        for (int i = 0; i < MAX_CITY; ++i)
        {
            for (int j = 0; j < MAX_CITY; ++j)
            {
                substance[i][j] = substance[i][j] * (1 - ro) + delta_substance[i][j];
                delta_substance[i][j] = 0;
            }
        }
    }

    bool contains( std::vector<int>& Vec, const int& Element )
    {
        if (std::find(Vec.begin(), Vec.end(), Element) != Vec.end())
            return true;

        return false;
    }

    void find_min_in_line(int &current_city, int &min)
    {
        int tmp_current = current_city;

        for (int j = 0; j < MAX_CITY; j++)
        {
            if (this->cities[current_city][j] and min > this->cities[current_city][j] and not contains(min_path_full, j))
            {
                min = this->cities[current_city][j];
                tmp_current = j;
            }
        }
        current_city = tmp_current;
    }

    void fill_cities()
    {
        srand(time(nullptr));
        for (int i = 0; i < MAX_CITY; ++i)
        {
            cities[i][i] = 0;
            for (int j = i + 1; j < MAX_CITY; ++j)
            {
                int value = (rand() % MAX_L + MIN_L);
                cities[i][j] = value;
                cities[j][i] = value;
            }
        }
    }

    void clear_cities()
    {
        if (cities)
        {
            for (int i = 0; i < MAX_CITY; i++)
                if (cities[i])
                    delete cities[i];

            delete[] cities;
        }
    }
};

class Test
{
public:
    Test(Solver* b):
        base(b), time(0)
    {

    }

    void test_time()
    {
        base->perebor();
        std::vector<int>tt = {10, 50, 100, 200};
        for (float alpha = 0; alpha <= 1; alpha += 0.25)
        {
            for (float roo = 0; roo <= 1; roo += 0.25)
            {
                for (int t_time = 0; t_time < tt.size(); ++t_time)
                {
                    auto start = std::chrono::high_resolution_clock::now();
                    base->muravei(alpha, roo, tt[t_time]);
                    auto end = std::chrono::high_resolution_clock::now();
                    set_time(end-start);
                    printf("\nAlfa is %.2f, Ro is %.2f, Life time is %d, diff is %f", alpha, roo, tt[t_time], (float)base->get_lenght()/(float)base->get_lenght_full());
                    get_time();
                }
            }
        }
    }

    void test_muravei_vs_perebor()
    {
        for (int i = 2; i < 11; ++i)
        {
            MAX_CITY = i;
            int** mat = create_cities();
            MAX_CITY -= 1;
            this->base->set_cities(mat);
            MAX_CITY += 1;

            auto start = std::chrono::high_resolution_clock::now();
            base->muravei(ALPHA, RO, 10, false);
            auto end = std::chrono::high_resolution_clock::now();
            set_time(end-start);
            printf("\nMuravei %d", i);
            get_time();

            start = std::chrono::high_resolution_clock::now();
            base->perebor(false);
            end = std::chrono::high_resolution_clock::now();
            set_time(end-start);
            printf("\nFull %d", i);
            get_time();
        }
    }

    void set_time(auto nsecs)
    {
        this->time = std::chrono::duration_cast<std::chrono::nanoseconds>(nsecs).count();
    }

    void add_time(auto nsecs)
    {
        this->time += std::chrono::duration_cast<std::chrono::nanoseconds>(nsecs).count();
    }

    void get_time()
    {
        std::cout << '\n' << this->time << '\n';
    }

private:
    Solver* base;
    unsigned long time;
};

std::ostream& operator<< (std::ostream &out, Solver *mat)
{
    int** to_print = mat->get_cities();
    for (unsigned int i = 0; i < MAX_CITY; ++i)
    {
        for (unsigned int j = 0; j < MAX_CITY; ++j)
        {
            out << to_print[i][j] << '\t';
        }
        out << '\n';
    }
    out << '\n';

    return out;
}

int main()
{
    int** test_mat = create_cities();

    Solver *test = new Solver(); //1
    test->set_cities(test_mat);
    std::cout << test << '\n';
    //test->muravei(ALPHA, RO, 10); //2
    //test->perebor(); //3

    Test *time = new Test(test);
    time->test_time();
    time->test_muravei_vs_perebor();

    return 0;
}
