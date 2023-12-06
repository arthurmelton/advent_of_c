#include <stdint.h>
#include <stdio.h>

#define TESTS 4

int part_one() {
	FILE *fptr;

	fptr = fopen("input", "r");

	if (fptr == 0) {
		printf("Failed to open file \"input\".\n");
		return 1;
	}

	int times[TESTS] = {0};
	int distances[TESTS] = {0};

	int current_number = 0;
	int index = 0;

	char buffer[1024] = {0};

	int read;

	while ((read = fread(buffer, 1, sizeof(buffer), fptr))) {
		for (int i = 0; i < read; i++) {
			uint8_t num = buffer[i] - 48;

			if (num < 10) {
				current_number *= 10;
				current_number += num;
			} else {
				if (current_number) {
					if (index < TESTS) {
						times[index] = current_number;
					} else {
						distances[index - TESTS] = current_number;
					}
					index++;
				}
				current_number = 0;
			}
		}
	}

	fclose(fptr);

	int total = 1;

	for (int i = 0; i < TESTS; i++) {
		int count = 0;
		for (int x = 0; x < times[i]; x++) {
			if ((times[i] - x) * x > distances[i]) {
				count++;
			}
		}
		total *= count;
	}

	printf("Total: %d\n", total);

	return 0;
}

int part_two() {
	FILE *fptr;

	fptr = fopen("input", "r");

	if (fptr == 0) {
		printf("Failed to open file \"input\".\n");
		return 1;
	}

	uint64_t time = 0;
	uint64_t distance = 0;

	uint64_t current_number = 0;
	int index = 0;

	char buffer[1024] = {0};

	int read;

	while ((read = fread(buffer, 1, sizeof(buffer), fptr))) {
		for (int i = 0; i < read; i++) {
			uint8_t num = buffer[i] - 48;

			if (num < 10) {
				current_number *= 10;
				current_number += num;
			} else if (buffer[i] == '\n') {
				if (current_number) {
					if (index < 1) {
						time = current_number;
					} else {
						distance = current_number;
					}
					index++;
				}
				current_number = 0;
			}
		}
	}

	fclose(fptr);

	int count = 0;
	for (int x = 0; x < time; x++) {
		if ((time - x) * x > distance) {
			count++;
		}
	}

	return 0;
}

int main() {
	if (part_one() || part_two()) {
		return 1;
	}
	return 0;
}
