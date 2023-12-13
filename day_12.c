#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_LENGTH 22861

int main() {
	FILE *fptr = fopen("input", "r");

	if (!fptr) {
		printf("Failed to open file \"input\".\n");
		return 1;
	}

	char data[FILE_LENGTH];

	fread(data, 1, FILE_LENGTH, fptr);

	fclose(fptr);

	int stage = 0;

	int current_line_length = 0;
	char *current_line = NULL;

	int number_index = 0;
	int *numbers = NULL;

	int current_number = 0;

	int total = 0;

	for (int i = 0; i < FILE_LENGTH; i++) {
		if (data[i] != ' ' && data[i] != '\n') {
			if (stage == 0) {
				current_line_length++;
				current_line = realloc(current_line, current_line_length);
				if (!current_line) {
					printf("Failled to realloc current line.\n");
					return 1;
				}
				current_line[current_line_length - 1] = data[i];
			} else {
				if (data[i] == ',') {
					number_index++;
					numbers = realloc(numbers, number_index * sizeof(int));
					if (!numbers) {
						printf("Failled to realloc numbers.\n");
						return 1;
					}
					numbers[number_index - 1] = current_number;
					current_number = 0;
				} else {
					current_number *= 10;
					current_number += data[i] - 48;
				}
			}
		} else {
			if (stage == 1) {
				number_index++;
				numbers = realloc(numbers, number_index * sizeof(int));
				numbers[number_index - 1] = current_number;
				current_number = 0;

				int question_count = 0;

				for (int x = 0; x < current_line_length; x++) {
					if (current_line[x] == '?') {
						question_count++;
					}
				}

				int solutions = 0;

				char *new_text = malloc(current_line_length);
				if (!new_text) {
					printf("Failled to alloc new text.\n");
					return 1;
				}

				int *nums = malloc(number_index * sizeof(int));
				if (!nums) {
					printf("Failled to alloc nums.\n");
					return 1;
				}

				for (int x = 0; x < 1 << question_count; x++) {
					int index = 0;

					for (int y = 0; y < current_line_length; y++) {
						if (current_line[y] == '?') {
							if (x & (1 << index)) {
								new_text[y] = '#';
							} else {
								new_text[y] = '.';
							}
							index++;
						} else {
							new_text[y] = current_line[y];
						}
					}

					int failed = 0;

					int current_num = 0;
					int num_count = 0;

					for (int y = 0; y < current_line_length; y++) {
						if (y > 0 && new_text[y] == '.' &&
							new_text[y - 1] == '#') {
							if (num_count > number_index) {
								failed = 1;
								break;
							}
							nums[num_count] = current_num;
							num_count++;
							current_num = 0;
						} else if (new_text[y] == '#') {
							current_num++;
						}
					}

					if (current_num > 0) {
						if (num_count > number_index - 1) {
							failed = 1;
						} else {
							nums[num_count] = current_num;
							num_count++;
						}
					}

					if (!failed && num_count == number_index) {
						int equal = 1;
						for (int y = 0; y < num_count; y++) {
							if (nums[y] != numbers[y]) {
								equal = 0;
								break;
							}
						}

						solutions += equal;
					}
				}

				free(nums);
				free(new_text);

				free(current_line);
				current_line = NULL;

				free(numbers);
				numbers = NULL;

				number_index = 0;

				current_line_length = 0;

				total += solutions;
			}

			stage = (stage + 1) % 2;
		}
	}

	printf("Total: %d\n", total);

	return 0;
}
