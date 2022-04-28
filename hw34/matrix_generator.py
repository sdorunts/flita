#!/usr/bin/env python3

from random import randint
import numpy as np

# Считывание из консоли данных, по которым будет происходить генерация
N = int(input("Введите количество вершин: ")) 
M = int(input("Введите общее количество связей: "))

# Создание матрицы N x M, где по строкам будут записаны
# каждый столбец конечной матрицы. Т.е. matrix - 
# транспонированная конечная матрица
matrix = []

for i in range(M):
    # Строка изначально заполнена лишь нулями. Нужно добавить 2 единицы
    matrix.append(['0' for j in range(N)])

    # С помощью рандома выбираем индексы элементов, значение которых
    # станет равно единице
    ind_1, ind_2 = randint(0, N-1), randint(0, N-1)

    # Если индексы совпали, то меняем второй индекс до тех пор,
    # пока они не станут разными
    while (ind_2 == ind_1):
        ind_2 = randint(0, N-1)
    
    # Присваивание единиц элементам с определёнными ранее индексами
    matrix[i][ind_1], matrix[i][ind_2] = '1', '1'

# Объединение символов в строку 
for i in range(M):
    matrix[i] = ''.join(matrix[i])

# Сортировка по убыванию
matrix.sort(reverse=True)

for i in range(M):
    matrix[i] = [int(sym) for sym in matrix[i]]

# Транспонирование матрицы
transpose_matrix = list(np.transpose(np.array(matrix)))
lines = []
for i in range(N):
    transpose_matrix[i] = [str(sym) for sym in transpose_matrix[i]]
    lines.append(' '.join(transpose_matrix[i]))

# Запись строк матрицы в файл
file_with_matrix = open("matrix.txt", "w")
for i in range(N):
    file_with_matrix.write(lines[i] + '\n')

file_with_matrix.close()

