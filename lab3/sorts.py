from random import randint
from time import time


def bubble_sort(arr):
    n = len(arr)

    for i in range(n):
        for j in range(n - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]

    return arr


def bubble_barrier_sort(arr):
    n = len(arr)

    while True:
        bar = 0
        for i in range(n - 1):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                bar = i + 1
        n = bar
        if n <= 0:
            break

    return arr


def shaker_sort_old(arr):
    left = 0
    right = len(arr) - 1

    while left <= right:
        for i in range(left, right, 1):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
        right -= 1

        for i in range(right, left, -1):
            if arr[i - 1] > arr[i]:
                arr[i], arr[i - 1] = arr[i - 1], arr[i]
        left += 1

    return arr


def shaker_sort(arr):
    left = 0
    right = len(arr) - 1
    bar = left

    while left != right:
        for i in range(left, right, 1):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                bar = i
        right = bar

        for i in range(right, left, -1):
            if arr[i] < arr[i - 1]:
                arr[i], arr[i - 1] = arr[i - 1], arr[i]
                bar = i - 1
        left = bar

    return arr
