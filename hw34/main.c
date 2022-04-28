#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(size_t **Array, size_t index1, size_t index2) {
	size_t *tmp = Array[index1];
	Array[index1] = Array[index2];
	Array[index2] = tmp;
}

void bubble_sort(size_t **Array, size_t length) {
	for (size_t i = 0; i < length; ++i)
		for (size_t j = 0; j < length - 1; ++j)
			if (Array[j][1] < Array[j + 1][1])
				swap(Array, j, j + 1);
}

void print_even_vertex_degree(size_t **Array, size_t length) {
	for (size_t i = 0; i < length; ++i)
		if (Array[i][1] % 2 == 0)
			printf("%ld\n", Array[i][0]);
}

int main(void) {
	FILE * file_with_matrix = NULL;
	size_t **vertex_degree = NULL;
	size_t **old_vertex_degree = NULL;
	size_t *current_vertex_degree = NULL;
	size_t max_vertex_count = 1;
	size_t current_vertex_count = 0;
	clock_t start_time;
	clock_t end_time;
	int flag = 1;
	char c;

	start_time = clock();

   	file_with_matrix = fopen("matrix.txt", "r");
	if (file_with_matrix == NULL) {
		printf("Can't open file for reading.\n");
		return 1;
	}

	vertex_degree = (size_t **) malloc(max_vertex_count * sizeof(size_t *));
	if (vertex_degree == NULL) {
		printf("Allocation error.\n");
		return 1;
	}

	while ((c = fgetc(file_with_matrix)) != EOF) {
		if (c == ' ')
			continue;

		if (flag) {
			/* {vertex_number, vertex_degree_count} */
			current_vertex_degree = (size_t *) malloc(2 * sizeof(size_t));
			if (current_vertex_degree == NULL) {
				printf("Allocation error.\n");
				return 1;
			}
			current_vertex_degree[0] = current_vertex_count + 1;
			flag = 0;
		}

		if (c == '1')
			++current_vertex_degree[1];

		if (c == '\n') {
			vertex_degree[current_vertex_count] = current_vertex_degree;
			++current_vertex_count;
			flag = 1;
		}

		if (current_vertex_count >= max_vertex_count) {
			max_vertex_count *= 2;
			old_vertex_degree = vertex_degree;

			vertex_degree = (size_t **) realloc(vertex_degree, max_vertex_count * sizeof(size_t));
			if (vertex_degree == NULL) {
				free(old_vertex_degree);
				printf("Allocation error.\n");
				return 1;
			}
		}
	}

	bubble_sort(vertex_degree, current_vertex_count);
	print_even_vertex_degree(vertex_degree, current_vertex_count);

	fclose(file_with_matrix);
	for (size_t i = 0; i < max_vertex_count; ++i)
		free(vertex_degree[i]);
	free(vertex_degree);

	end_time = clock();
	printf("Program running time: %lf second\n", (double) (end_time - start_time) / CLOCKS_PER_SEC);

	return 0;
}

