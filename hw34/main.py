#!/usr/bin/env python3

import os
import argparse
import matplotlib.pyplot as plt
import numpy as np

# Подготовка аргументов командной строки
parser = argparse.ArgumentParser()
parser.add_argument("--count_of_different_tests", required=True, type=int)
parser.add_argument("--count_of_identical_tests", required=True, type=int)

# Массив с аргументами командной строки
args = parser.parse_args()

count_of_different_tests = args.count_of_different_tests 
count_of_identical_tests = args.count_of_identical_tests

# Компиляция файла с кодом программы
os.system('cc main.c -o main')

# Удаление файла, в котором содержится время работы программ
os.system('rm running_time.txt')

count_of_vertex = 10
count_of_all_degree = 10

abscissa_coordinates = []

for i in range(count_of_different_tests):
    os.system(f'./matrix_generator.py --count_of_vertex={count_of_vertex} --count_of_all_degree={count_of_all_degree}')

    for j in range(count_of_identical_tests):
        os.system('./main')

    abscissa_coordinates.append(count_of_vertex * count_of_all_degree)
    count_of_vertex *= 2
    count_of_all_degree *= 2

file_with_time_of_running = open("running_time.txt", "r")

run_time = [float(current_time[:-1]) for current_time in file_with_time_of_running.readlines()]
ordinate_coordinates = []
border = 0

for i in range(count_of_different_tests):
    average_value_of_identical_tests = np.average(run_time[border:border + count_of_identical_tests])
    ordinate_coordinates.append(average_value_of_identical_tests)
    border += count_of_identical_tests

file_with_time_of_running.close()

plt.grid()
plt.plot(abscissa_coordinates, ordinate_coordinates)
plt.show()

