#include <iostream>
#include "test_runner.h"
#include "func.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <functional>

void _TestSorted_(std::function<void(std::vector<int>&)> sort) {
  {
    std::vector<int> arr = { 1, 2, 3, 4, 5 };
    std::vector<int> res = { 1, 2, 3, 4, 5 };

    sort(arr);

    ASSERT_EQUAL(arr, res);
  }

  {
    std::vector<int> arr = { -5, -4, -3, -2, -1 };
    std::vector<int> res = { -5, -4, -3, -2, -1 };

    sort(arr);

    ASSERT_EQUAL(arr, res);
  }

  {
    std::vector<int> arr = { -5, -4, 0, 1, 2, 3 };
    std::vector<int> res = { -5, -4, 0, 1, 2, 3 };

    sort(arr);

    ASSERT_EQUAL(arr, res);
  }
}

void _TestReverseSorted_(std::function<void(std::vector<int>&)> sort) {
  {
    std::vector<int> arr = { 5, 4, 3, 2, 1 };
    std::vector<int> res = { 1, 2, 3, 4, 5 };

    sort(arr);

    ASSERT_EQUAL(arr, res);
  }

  {
    std::vector<int> arr = { -1, -2, -3, -4, -5 };
    std::vector<int> res = { -5, -4, -3, -2, -1 };

    sort(arr);

    ASSERT_EQUAL(arr, res);
  }

  {
    std::vector<int> arr = { 3, 2, 1, 0, -4, -5 };
    std::vector<int> res = { -5, -4, 0, 1, 2, 3 };

    sort(arr);

    ASSERT_EQUAL(arr, res);
  }
}

void _TestPartSorted_(std::function<void(std::vector<int>&)> sort) {
  {
    std::vector<int> arr = { 4, 5, 1, 2, 3 };
    std::vector<int> res = { 1, 2, 3, 4, 5 };

    sort(arr);

    ASSERT_EQUAL(arr, res);
  }

  {
    std::vector<int> arr = { -5, -2, -1, -4, -3 };
    std::vector<int> res = { -5, -4, -3, -2, -1 };

    sort(arr);

    ASSERT_EQUAL(arr, res);
  }

  {
    std::vector<int> arr = { 0, 1, -5, -4, 2, 3 };
    std::vector<int> res = { -5, -4, 0, 1, 2, 3 };

    sort(arr);

    ASSERT_EQUAL(arr, res);
  }
}

void _TestEqual_(std::function<void(std::vector<int>&)> sort) {
  {
    std::vector<int> arr = { 1, 1, 1, 1, 1 };
    std::vector<int> res = { 1, 1, 1, 1, 1 };

    sort(arr);

    ASSERT_EQUAL(arr, res);
  }

  {
    std::vector<int> arr = { -1, -1, -1, -1, -1 };
    std::vector<int> res = { -1, -1, -1, -1, -1 };

    sort(arr);

    ASSERT_EQUAL(arr, res);
  }

  {
    std::vector<int> arr = { 0, 0, 0, 0, 0 };
    std::vector<int> res = { 0, 0, 0, 0, 0 };

    sort(arr);

    ASSERT_EQUAL(arr, res);
  }
}

void _TestRepeat_(std::function<void(std::vector<int>&)> sort) {
  {
    std::vector<int> arr = { 5, 2, 3, 1, 1, 3, 4, 5 };
    std::vector<int> res = { 1, 1, 2, 3, 3, 4, 5, 5 };

    sort(arr);

    ASSERT_EQUAL(arr, res);
  }

  {
    std::vector<int> arr = { -5, 2, 3, 1, -1, 3, 4, 1, -5, 2, 2 };
    std::vector<int> res = { -5, -5, -1, 1, 1, 2, 2, 2, 3, 3, 4 };

    sort(arr);

    ASSERT_EQUAL(arr, res);
  }

  {
    std::vector<int> arr = { -5, 2, 3, 1, -1, 0, 3, 4, 1, 0, -5, 2, 2, 0 };
    std::vector<int> res = { -5, -5, -1, 0, 0, 0, 1, 1, 2, 2, 2, 3, 3, 4 };

    sort(arr);

    ASSERT_EQUAL(arr, res);
  }
}

void TestInsertionSort() {
  TestRunner tr;

  TEST_NAME;

  auto TestSorted = []() { _TestSorted_(insertion_sort); };
  auto TestReverseSorted = []() { _TestReverseSorted_(insertion_sort); };
  auto TestPartSorted = []() { _TestPartSorted_(insertion_sort); };
  auto TestEqual = []() { _TestEqual_(insertion_sort); };
  auto TestRepeat = []() { _TestRepeat_(insertion_sort); };

  RUN_TEST(tr, TestSorted);
  RUN_TEST(tr, TestReverseSorted);
  RUN_TEST(tr, TestPartSorted);
  RUN_TEST(tr, TestEqual);
  RUN_TEST(tr, TestRepeat);
}

void TestShellSort() {
  TestRunner tr;

  TEST_NAME;

  auto TestSorted = []() { _TestSorted_(shell_sort); };
  auto TestReverseSorted = []() { _TestReverseSorted_(shell_sort); };
  auto TestPartSorted = []() { _TestPartSorted_(shell_sort); };
  auto TestEqual = []() { _TestEqual_(shell_sort); };
  auto TestRepeat = []() { _TestRepeat_(shell_sort); };

  RUN_TEST(tr, TestSorted);
  RUN_TEST(tr, TestReverseSorted);
  RUN_TEST(tr, TestPartSorted);
  RUN_TEST(tr, TestEqual);
  RUN_TEST(tr, TestRepeat);
}

void TestTimSort() {
  TestRunner tr;

  TEST_NAME;

  auto TestSorted = []() { _TestSorted_(timsort); };
  auto TestReverseSorted = []() { _TestReverseSorted_(timsort); };
  auto TestPartSorted = []() { _TestPartSorted_(timsort); };
  auto TestEqual = []() { _TestEqual_(timsort); };
  auto TestRepeat = []() { _TestRepeat_(timsort); };

  RUN_TEST(tr, TestSorted);
  RUN_TEST(tr, TestReverseSorted);
  RUN_TEST(tr, TestPartSorted);
  RUN_TEST(tr, TestEqual);
  RUN_TEST(tr, TestRepeat);
}

//int main() {
//  std::cout << std::endl << "Start..." << std::endl;

//  TestInsertionSort();
//  TestShellSort();
//  TestTimSort();

//  std::cout << std::endl << "All tests were run!" << std::endl;

//  return 0;
//}
