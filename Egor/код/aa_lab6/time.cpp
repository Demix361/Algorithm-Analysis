#include <iostream>
#include <string>
#include <cassert>
#include "test_runner.h"
#include "func.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <functional>
#include <chrono>

std::vector<int> get_rand_vector(int n) {
  std::vector<int> v(n);

  for (auto &elem : v) {
    elem = rand();
  }

  return v;
}

std::vector<int> get_sorted_vector(int n) {
  std::vector<int> v(n);

  for (int i = 0; i < n; ++i) {
    v[i] = i;
  }

  return v;
}

std::vector<int> get_reversed_vector(int n) {
  std::vector<int> v(n);

  for (int i = 0; i < n; ++i) {
    v[i] = n - i - 1;
  }

  return v;
}

#define NUM 1000
#define START 100
#define STEP  100
#define STOP  1000

void TestTime(std::function<void(std::vector<int>&)> sort, std::string file_name, int param = 0) {
  srand(static_cast<unsigned int>(time(0)));
  std::cout << std::endl << "--[ " << file_name << " ]--" << std::endl;

  ofstream fout(file_name);
  std::chrono::time_point<std::chrono::system_clock> start_time, end_time;

  std::function<std::vector<int>(int)> get_vector;

  switch (param) {
    case 0:
      get_vector = get_rand_vector;
      break;
    case 1:
      get_vector = get_sorted_vector;
      break;
    case 2:
      get_vector = get_reversed_vector;
      break;
  }

  for (int i = START; i <= STOP; i += STEP) {
      std::cout << "Cur_size = " << i << std::endl;
      fout << "SIZE { " << i << " } :" << std::endl;

      unsigned long long int elapsed_time = 0;

      for (int j = 0; j < NUM; ++j) {
        auto v = get_vector(i);

        start_time = std::chrono::system_clock::now();
        sort(v);
        end_time = std::chrono::system_clock::now();

        elapsed_time += std::chrono::duration_cast<std::chrono::nanoseconds>
        (end_time - start_time).count();
      }

      fout << ((long double)(elapsed_time) / NUM) << std::endl;

      std::cout << "Continue..." << std::endl;
  }

  fout.close();
}

//int main() {
//  std::cout << std::endl << "Start..." << std::endl;

//  std::vector<std::string> file_names = { "insertion_sort_time.txt",
//  "shell_sort_time.txt", "timsort_time.txt" };

//  std::vector<std::string> dir = { "time/1000_rand/", "time/1000_sorted/", "time/1000_reversed/" };

//  std::vector<std::function<void(std::vector<int>&)>> funcs = { insertion_sort, shell_sort, timsort };

//  for (int i = 1; i < static_cast<int>(dir.size()); ++i) {
//    for (int j = 0; j < static_cast<int>(file_names.size()); ++j) {
//      TestTime(funcs[j], dir[i] + file_names[j], i);
//    }
//  }

//  // TestTime(shell_sort, "NEW_SHELL.txt");
//  // TestTime(timsort, "NEW_TIM.txt");

//  // TestTime(insertion_sort, "check.txt", 1);
  

//  std::cout << std::endl << "All tests were run!" << std::endl;

//  return 0;
//}
