#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 100
#define HEIGHT 100

int part_one() {
	FILE *fptr = fopen("input", "r");
	if (!fptr) {
		printf("Failed to read the file \"input\".\n");
		return 1;
	}

	char *data = malloc((WIDTH + 1) * HEIGHT);

	if (!data) {
		printf("Failed to alloc space for file\n.");
		return 1;
	}

	fread(data, 1, (WIDTH + 1) * HEIGHT, fptr);

	fclose(fptr);

	int changed = 1;
	while (changed) {
		changed = 0;
		for (int y = 0; y < HEIGHT - 1; y++) {
			for (int x = 0; x < WIDTH; x++) {
				if (data[y * (WIDTH + 1) + x] == '.' &&
					data[(y + 1) * (WIDTH + 1) + x] == 'O') {
					data[y * (WIDTH + 1) + x] = 'O';
					data[(y + 1) * (WIDTH + 1) + x] = '.';
					changed = 1;
				}
			}
		}
	}

	int load = 0;

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (data[y * (WIDTH + 1) + x] == 'O') {
				load += WIDTH - y;
			}
		}
	}

    free(data);

	printf("load: %d\n", load);

	return 0;
}

#define NTH 1000000000

int part_two() {
	FILE *fptr = fopen("input", "r");
	if (!fptr) {
		printf("Failed to read the file \"input\".\n");
		return 1;
	}

	char *data = malloc((WIDTH + 1) * HEIGHT);

	if (!data) {
		printf("Failed to alloc space for file\n.");
		return 1;
	}

	fread(data, 1, (WIDTH + 1) * HEIGHT, fptr);

	fclose(fptr);

    int previous_length = 0;
    char *previous = NULL;

	for (int i = 0; i < NTH; i++) {
		for (int k = 0; k < 4; k++) {
			int changed = 1;
			while (changed) {
				changed = 0;
				for (int y = (k == 2); y < HEIGHT - (k == 0); y++) {
					for (int x = (k == 3); x < WIDTH - (k == 1); x++) {
						int check_with = y * (WIDTH + 1) + x;
						if (k == 0) {
							check_with += (WIDTH + 1);
						} else if (k == 1) {
							check_with++;
						} else if (k == 2) {
							check_with -= (WIDTH + 1);
						} else if (k == 3) {
							check_with--;
						}

						if (data[y * (WIDTH + 1) + x] == '.' &&
							data[check_with] == 'O') {
							data[y * (WIDTH + 1) + x] = 'O';
							data[check_with] = '.';
							changed = 1;
						}
					}
				}
			}
		}

        int found_match = 0;

        for (int k = 0; k < previous_length; k++) {
            if (memcmp(&previous[k * (WIDTH + 1) * HEIGHT], data, (WIDTH + 1) * HEIGHT) == 0) {
                found_match = 1;
                memcpy(data, &previous[(WIDTH + 1) * HEIGHT * ((NTH - k) % (previous_length - k) + k - 1)], (WIDTH + 1) * HEIGHT);
                break;
            }
        }

        if (found_match) {
            break;
        }

        previous_length++;
        previous = realloc(previous, previous_length * (WIDTH + 1) * HEIGHT);

        if (!previous) {
            printf("Failed to realloc space for past array.\n");
            return 1;
        }

        memcpy(&previous[(previous_length-1) * (WIDTH + 1) * HEIGHT], data, (WIDTH + 1) * HEIGHT);
	}

    free(previous);

	int load = 0;

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (data[y * (WIDTH + 1) + x] == 'O') {
				load += WIDTH - y;
			}
		}
	}

    free(data);

	printf("load: %d\n", load);

	return 0;
}

int main() { return part_one() || part_two(); }
