#include "conveyor.h"
#include "elem.h"
#include <queue>
#include <string>
#include <iostream>
#include <thread>
#include <windows.h>

#define MAX_ELEM 1

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <climits>
#include <stack>
#include <random>
#include <fstream>
#include <mutex>

using namespace std;

long int max_elem;
std::string file_name = "log_conveyor.txt";
std::mutex m, m1, m2, m3;
std::vector<File_obj> log_vec;

std::string alf = "qwertyuiopasdfghjklzxcvbnm ";

void vec_init(std::vector<std::string> &vec, size_t m, size_t n) {
    for (size_t i = 0; i < m; i ++) {
        std::string str;
        for (size_t j = 0; j < n; j++) {
            size_t k = rand()%27;
            str += alf[k];
        }
        //std::cout << std::endl << str << std::endl;
        vec.push_back(str);
    }
}


long int encrypt( long int i, long int e, long int n)
{
    long long int result = 1;

    for ( long int j = 0; j < e; j++ )
    {
        result *= i;
        result %= n;
    }

    return result;
}


long int greatest_common_divisor(long int e, long int t)
{
    long int tmp;
    while (e > 0)
    {
        long int tmp = e;
        e = t % e;
        t = tmp;
    }

    return t;
}

long int calculate_e(long int t)
{
    // Выбирается целое число e ( 1 < e < t ) // взаимно простое со значением функции Эйлера (t)
    long int res = -1;
    long int e;

    for ( e = 2; e < t; e++ )
    {
        if (greatest_common_divisor(e, t) == 1)
        {
            res = e;
            break;
        }
    }

    return res;
}


long int calculate_d(long int e, long int t)
{
    // Вычисляется число d, мультипликативно обратное к числу e по модулю φ(n), то есть число, удовлетворяющее сравнению:
    //    d ⋅ e ≡ 1 (mod φ(n))

    long int d;
    long int k = 1;

    while (true)
    {
        k += t;

        if (!(k % e))
        {
            d = k / e;
            break;
        }
    }
    //std::cout << "d" << d;
    return d;

}


bool is_prime(long int prime)
{
    bool res = true;
    long int j = (long int)sqrt((long double)prime);

    for (long int i = 2; i <= j; i++)
    {
        if (!(prime % i))
        {
            res = false;
            break;
        }
    }

    return res;
}

void handler_1(Conv_obj &obj) {

    long long int p, q, n, t, e, d;
    p = obj.str.size();
    while (!is_prime(p)) {
        p++;

    }
    q = p + 1;
    while (!is_prime(q)) {
        q++;
    }
    p = 17;
    q = 257;
    //std::cout << q << " " << p << "\n";
    n = p * q;
    t = (p - 1) * (q - 1);
    e = calculate_e(t);
    d = calculate_d(e, t);
    //std::cout << "ed" << e << " " << d << "\n";

    obj.public_key.e = e;
    obj.public_key.n = n;
    obj.private_key.e = d;
    obj.private_key.n = n;
    Sleep(10);
}

void handler_2(Conv_obj &obj) {
    std::string &str = obj.str;
    for (size_t i = 0; i < str.size(); i++) {
        obj.vec.push_back(encrypt(int(str[i]), obj.public_key.e, obj.public_key.n));
        str[i] = obj.vec[i]  % alf.size() + 97;
    }
}

void handler_3(Conv_obj &obj) {
    std::string &str = obj.str;
    for (size_t i = 0; i < str.size(); i++) {
        str[i] = encrypt(obj.vec[i], obj.private_key.e, obj.private_key.n);
    }
}

void belt_1(std::queue<Conv_obj> &queue_1, std::queue<Conv_obj> &queue_2) {
    int count = 0;
    while (count < max_elem) {
        m1.lock();
        if (!queue_1.empty()) {
            Conv_obj cur_conv_obj = queue_1.front();
            queue_1.pop();

            File_obj cur_file_obj;
            cur_file_obj.index_str = cur_conv_obj.index;
            cur_file_obj.num_belt = 1;
            GetLocalTime(&cur_file_obj.t);
            cur_file_obj.state = 'S';

            m.lock();
            log_vec.push_back(cur_file_obj);
            m.unlock();

            handler_1(cur_conv_obj);

            m2.lock();
            queue_2.push(cur_conv_obj);
            m2.unlock();

            GetLocalTime(&cur_file_obj.t);
            cur_file_obj.state = 'F';

            m.lock();
            log_vec.push_back(cur_file_obj);
            m.unlock();

            count++;
        }
        m1.unlock();
    }

}


void belt_2(std::queue<Conv_obj> &queue_2, std::queue<Conv_obj> &queue_3) {
    int count = 0;
    while (count < max_elem) {
        m2.lock();
        if (!queue_2.empty()) {
            Conv_obj cur_conv_obj = queue_2.front();
            queue_2.pop();

            File_obj cur_file_obj;
            cur_file_obj.index_str = cur_conv_obj.index;
            cur_file_obj.num_belt = 2;
            GetLocalTime(&cur_file_obj.t);
            cur_file_obj.state = 'S';

            m.lock();
            log_vec.push_back(cur_file_obj);
            m.unlock();

            //std::cout << "source " << cur_conv_obj.str << "\n";
            handler_2(cur_conv_obj);
            //std::cout << "encrypt " << cur_conv_obj.str << "\n";

            m3.lock();
            queue_3.push(cur_conv_obj);
            m3.unlock();

            GetLocalTime(&cur_file_obj.t);
            cur_file_obj.state = 'F';

            m.lock();
            log_vec.push_back(cur_file_obj);
            m.unlock();

            count++;
        }
        m2.unlock();
    }

}


void belt_3(std::queue<Conv_obj> &queue_3) {
    int count = 0;
    while (count < max_elem) {
        m3.lock();
        if (!queue_3.empty()) {
            Conv_obj cur_conv_obj = queue_3.front();
            queue_3.pop();

            File_obj cur_file_obj;
            cur_file_obj.index_str = cur_conv_obj.index;
            cur_file_obj.num_belt = 3;
            GetLocalTime(&cur_file_obj.t);
            cur_file_obj.state = 'S';

            m.lock();
            log_vec.push_back(cur_file_obj);
            m.unlock();

            handler_3(cur_conv_obj);
            //std::cout << "decrypt " << cur_conv_obj.str << "\n";


            GetLocalTime(&cur_file_obj.t);
            cur_file_obj.state = 'F';

            m.lock();
            log_vec.push_back(cur_file_obj);
            m.unlock();

            count++;
        }
        m3.unlock();
    }

}

void write_res() {
    std::ofstream file;
        file.open(file_name);
        int w = 15;
        file << std::setw(20) << "№ operation" << std::setw(13)
            << "Belt" << std::setw(17)
            << "Number str" << std::setw(w)
            << "State" << std::setw(w)
            << "Time" << std::endl;
        for (int i = 0; i < int(log_vec.size()); ++i) {
            file << std::setw(w) << i + 1 << std::setw(w)
            << log_vec[i].num_belt << std::setw(w)
            << log_vec[i].index_str << std::setw(w)
            << log_vec[i].state << std::setw(w)
            << log_vec[i].t.wHour
            << ":" << log_vec[i].t.wMinute
            << ":" << log_vec[i].t.wSecond
            << "." << log_vec[i].t.wMilliseconds << std::endl;
        }
        file.close();
}

int enter_int(std::string message) {
    int number;

    char answer[256];
    cout << message;
    fgets(answer, sizeof(answer), stdin); // считываем строку

    while (sscanf(answer, "%d", &number) != 1 || number <= 0) {
        printf("Incorrect input. Try again: ");
        fgets(answer, sizeof(answer), stdin);
    }
    return number;
}

void conveyor() {
    max_elem = enter_int("Input number of string: ");
    int max_len = enter_int("Input max length string: ");
    std::cout << "Input file name: ";
    std::cin >> file_name;

    std::queue<Conv_obj> queue_1, queue_2, queue_3;
    std::vector<std::string> vec_str;
    std::vector<Conv_obj> vec_elem;
    vec_init(vec_str, max_elem, max_len);
    for (size_t i = 0; i < vec_str.size(); i++) {
        Conv_obj tmp;
        tmp.str = vec_str[i];
        tmp.index = i + 1;
        vec_elem.push_back(tmp);
    }

    for (size_t i = 0; i < vec_str.size(); i++) {
        queue_1.push(vec_elem[i]);
    }

    std::thread thread_1(belt_1, std::ref(queue_1), std::ref(queue_2));
    std::thread thread_2(belt_2, std::ref(queue_2), std::ref(queue_3));
    std::thread thread_3(belt_3, std::ref(queue_3));
    thread_1.join();
    thread_2.join();
    thread_3.join();
    std::cout << "END\n";
    write_res();

}
