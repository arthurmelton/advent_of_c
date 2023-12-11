#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 140
#define HEIGHT 140

int part_one() {
	FILE *fptr = fopen("input", "r");

	if (!fptr) {
		printf("Failed to open \"input\".\n");
		return 1;
	}

	char inital_read[(WIDTH + 1) * HEIGHT];

	fread(inital_read, 1, sizeof(inital_read), fptr);

	fclose(fptr);

	int increase_vertical_count = 0;
	int *increase_vertical = NULL;

	int increase_horizontal_count = 0;
	int *increase_horizontal = NULL;

	for (int i = 0; i < WIDTH; i++) {
		int all_zero = 1;
		for (int x = 0; x < HEIGHT; x++) {
			if (inital_read[(WIDTH + 1) * x + i] == '#') {
				all_zero = 0;
				break;
			}
		}

		if (all_zero) {
			increase_vertical_count++;
			increase_vertical = realloc(increase_vertical,
										increase_vertical_count * sizeof(int));
			increase_vertical[increase_vertical_count - 1] =
				i + increase_vertical_count - 1;
		}
	}

	for (int i = 0; i < HEIGHT; i++) {
		int all_zero = 1;
		for (int x = 0; x < WIDTH; x++) {
			if (inital_read[(WIDTH + 1) * i + x] == '#') {
				all_zero = 0;
				break;
			}
		}

		if (all_zero) {
			increase_horizontal_count++;
			increase_horizontal = realloc(
				increase_horizontal, increase_horizontal_count * sizeof(int));
			increase_horizontal[increase_horizontal_count - 1] =
				i + increase_horizontal_count - 1;
		}
	}

	int new_width = WIDTH + increase_vertical_count;
	int new_height = HEIGHT + increase_horizontal_count;

	char *new_feild = malloc((new_width + 1) * new_height);

	if (!new_feild) {
		printf("Erroring mallocing.\n");
		return 1;
	}

	int increased_horizontal = 0;

	for (int y = 0; y < new_height; y++) {
		int do_increase = 0;
		for (int i = 0; i < increase_horizontal_count; i++) {
			if (increase_horizontal[i] == y) {
				do_increase = 1;
				break;
			}
		}

		if (do_increase) {
			increased_horizontal++;
			for (int i = 0; i < new_width; i++) {
				new_feild[y * new_width + i] = '.';
			}
			continue;
		}

		int increased_vertical = 0;

		for (int x = 0; x < new_width; x++) {
			int increased = 0;
			for (int i = 0; i < increase_vertical_count; i++) {
				if (increase_vertical[i] == x) {
					increased_vertical++;
					new_feild[y * new_width + x] = '.';
					increased = 1;
					break;
				}
			}
			if (increased) {
				continue;
			}
			new_feild[y * new_width + x] =
				inital_read[(y - increased_horizontal) * (WIDTH + 1) +
							(x - increased_vertical)];
		}
	}

	int galaxy_count = 0;
	int *galaxies = NULL;

	for (int y = 0; y < new_height; y++) {
		for (int x = 0; x < new_width; x++) {
			if (new_feild[y * new_width + x] == '#') {
				galaxy_count++;
				galaxies = realloc(galaxies, galaxy_count * sizeof(int) * 2);
				galaxies[(galaxy_count - 1) * 2] = x;
				galaxies[(galaxy_count - 1) * 2 + 1] = y;
			}
		}
	}

	int lengths = 0;

	for (int i = 0; i < galaxy_count; i++) {
		for (int x = 0; x < galaxy_count; x++) {
			lengths += abs(galaxies[i * 2] - galaxies[x * 2]) +
					   abs(galaxies[i * 2 + 1] - galaxies[x * 2 + 1]);
		}
	}

	printf("%d\n", lengths >> 1);

	free(increase_vertical);
	free(increase_horizontal);

	return 0;
}

#define INCREASE_BY 999999

int part_two() {
	FILE *fptr = fopen("input", "r");

	if (!fptr) {
		printf("Failed to open \"input\".\n");
		return 1;
	}

	char inital_read[(WIDTH + 1) * HEIGHT];

	fread(inital_read, 1, sizeof(inital_read), fptr);

	fclose(fptr);

	int increase_vertical_count = 0;
	int *increase_vertical = NULL;

	int increase_horizontal_count = 0;
	int *increase_horizontal = NULL;

	for (int i = 0; i < WIDTH; i++) {
		int all_zero = 1;
		for (int x = 0; x < HEIGHT; x++) {
			if (inital_read[(WIDTH + 1) * x + i] == '#') {
				all_zero = 0;
				break;
			}
		}

		if (all_zero) {
			increase_vertical_count++;
			increase_vertical = realloc(increase_vertical,
										increase_vertical_count * sizeof(int));
			increase_vertical[increase_vertical_count - 1] = i;
		}
	}

	for (int i = 0; i < HEIGHT; i++) {
		int all_zero = 1;
		for (int x = 0; x < WIDTH; x++) {
			if (inital_read[(WIDTH + 1) * i + x] == '#') {
				all_zero = 0;
				break;
			}
		}

		if (all_zero) {
			increase_horizontal_count++;
			increase_horizontal = realloc(
				increase_horizontal, increase_horizontal_count * sizeof(int));
			increase_horizontal[increase_horizontal_count - 1] = i;
		}
	}

	int galaxy_count = 0;
	int *galaxies = NULL;

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (inital_read[(WIDTH + 1) * y + x] == '#') {
				galaxy_count++;
				galaxies = realloc(galaxies, galaxy_count * sizeof(int) * 2);

				int galaxy_x = x;
				for (int i = 0; i < increase_vertical_count; i++) {
					if (x > increase_vertical[i]) {
						galaxy_x += INCREASE_BY;
					}
				}

				int galaxy_y = y;
				for (int i = 0; i < increase_horizontal_count; i++) {
					if (y > increase_horizontal[i]) {
						galaxy_y += INCREASE_BY;
					}
				}

				galaxies[(galaxy_count - 1) * 2] = galaxy_x;
				galaxies[(galaxy_count - 1) * 2 + 1] = galaxy_y;
			}
		}
	}

	uint64_t lengths = 0;

	for (int i = 0; i < galaxy_count; i++) {
		for (int x = 0; x < galaxy_count; x++) {
			lengths += abs(galaxies[i * 2] - galaxies[x * 2]) +
					   abs(galaxies[i * 2 + 1] - galaxies[x * 2 + 1]);
		}
	}

	printf("%ld\n", lengths >> 1);

	free(increase_vertical);
	free(increase_horizontal);

	return 0;
}

int main() { return part_one() || part_two(); }
