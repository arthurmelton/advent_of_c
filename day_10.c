#include <stdio.h>
#include <stdlib.h>

#define WIDTH 140
#define HEIGHT 140

#define BUFFER_SIZE WIDTH *(HEIGHT + 1) - 1

int part_one() {
	FILE *fptr = fopen("input", "r");

	if (!fptr) {
		printf("Failed to open \"input\".\n");
		return 1;
	}

	char *buffer = malloc(BUFFER_SIZE);

	if (!buffer) {
		printf("Failed to create the space for the file in memory\n");
		return 1;
	}

	fread(buffer, 1, BUFFER_SIZE, fptr);

	fclose(fptr);

	int index = 0;
	int direction = 0;
	int length = 0;

	for (int i = 0; i < BUFFER_SIZE; i++) {
		if (buffer[i] == 'S') {
			index = i;

			if (buffer[i - 1] == '-' || buffer[i - 1] == 'L' ||
				buffer[i - 1] == 'F') {
				direction = -1;
			} else if (buffer[i - WIDTH - 1] == '|' ||
					   buffer[i - WIDTH - 1] == '7' ||
					   buffer[i - WIDTH - 1] == 'F') {
				direction = -WIDTH - 1;
			} else if (buffer[i + 1] == '-' || buffer[i + 1] == '7' ||
					   buffer[i + 1] == 'J') {
				direction = +1;
			} else if (buffer[i + WIDTH + 1] == '|' ||
					   buffer[i + WIDTH + 1] == 'L' ||
					   buffer[i + WIDTH + 1] == 'J') {
				direction = +WIDTH + 1;
			}
			break;
		}
	}

	while (buffer[index] != 'S' || length == 0) {
		index += direction;

		if (direction == -1) {
			if (buffer[index] == '-') {
				direction = -1;
			} else if (buffer[index] == 'L') {
				direction = -WIDTH - 1;
			} else if (buffer[index] == 'F') {
				direction = +WIDTH + 1;
			}

		} else if (direction == -WIDTH - 1) {
			if (buffer[index] == '|') {
				direction = -WIDTH - 1;

			} else if (buffer[index] == '7') {
				direction = -1;
			} else if (buffer[index] == 'F') {
				direction = 1;
			}
		} else if (direction == 1) {
			if (buffer[index] == '-') {
				direction = 1;
			} else if (buffer[index] == '7') {
				direction = +WIDTH + 1;
			} else if (buffer[index] == 'J') {
				direction = -WIDTH - 1;
			}
		} else if (direction == WIDTH + 1) {
			if (buffer[index] == '|') {
				direction = WIDTH + 1;
			} else if (buffer[index] == 'L') {
				direction = 1;
			} else if (buffer[index] == 'J') {
				direction = -1;
			}
		}

		length++;
	}

	free(buffer);

	printf("Max distance: %d\n", length / 2);

	return 0;
}

int part_two() {
	FILE *fptr = fopen("input", "r");

	if (!fptr) {
		printf("Failed to open \"input\".\n");
		return 1;
	}

	char *buffer = malloc(BUFFER_SIZE);

	if (!buffer) {
		printf("Failed to create the space for the file in memory\n");
		return 1;
	}

	fread(buffer, 1, BUFFER_SIZE, fptr);

	fclose(fptr);

	int index = 0;
	int direction = 0;
	int length = 0;

	for (int i = 0; i < BUFFER_SIZE; i++) {
		if (buffer[i] == 'S') {
			index = i;

			if (buffer[i - 1] == '-' || buffer[i - 1] == 'L' ||
				buffer[i - 1] == 'F') {
				direction = -1;
			} else if (buffer[i - WIDTH - 1] == '|' ||
					   buffer[i - WIDTH - 1] == '7' ||
					   buffer[i - WIDTH - 1] == 'F') {
				direction = -WIDTH - 1;
			} else if (buffer[i + 1] == '-' || buffer[i + 1] == '7' ||
					   buffer[i + 1] == 'J') {
				direction = +1;
			} else if (buffer[i + WIDTH + 1] == '|' ||
					   buffer[i + WIDTH + 1] == 'L' ||
					   buffer[i + WIDTH + 1] == 'J') {
				direction = +WIDTH + 1;
			}
			break;
		}
	}

	int *positions = NULL;

	while (buffer[index] != 'S' || length == 0) {
		positions = realloc(positions, (length + 1) * sizeof(int));
		if (!positions) {
			printf("Failed to realloc\n");
			return 1;
		}

		positions[length] = index;

		index += direction;

		if (direction == -1) {
			if (buffer[index] == '-') {
				direction = -1;
			} else if (buffer[index] == 'L') {
				direction = -WIDTH - 1;
			} else if (buffer[index] == 'F') {
				direction = +WIDTH + 1;
			}

		} else if (direction == -WIDTH - 1) {
			if (buffer[index] == '|') {
				direction = -WIDTH - 1;

			} else if (buffer[index] == '7') {
				direction = -1;
			} else if (buffer[index] == 'F') {
				direction = 1;
			}
		} else if (direction == 1) {
			if (buffer[index] == '-') {
				direction = 1;
			} else if (buffer[index] == '7') {
				direction = +WIDTH + 1;
			} else if (buffer[index] == 'J') {
				direction = -WIDTH - 1;
			}
		} else if (direction == WIDTH + 1) {
			if (buffer[index] == '|') {
				direction = WIDTH + 1;
			} else if (buffer[index] == 'L') {
				direction = 1;
			} else if (buffer[index] == 'J') {
				direction = -1;
			}
		}

		length++;
	}

	int inside = 0;

	for (int i = 0; i < BUFFER_SIZE; i++) {
		int on_line = 0;
		for (int x = 0; x < length; x++) {
			if (positions[x] == i) {
				on_line = 1;
				break;
			}
		}

		if (!on_line) {
			int count_left = 0;
			int count_top = 0;

			int added_half = 0;
			for (int x = 0; x < i % (WIDTH + 1); x++) {
				if (buffer[i - x - 1] == '|' || buffer[i - x - 1] == 'F' ||
					buffer[i - x - 1] == 'J' || buffer[i - x - 1] == 'L' ||
					buffer[i - x - 1] == '7') {
					on_line = 0;
					for (int y = 0; y < length; y++) {
						if (positions[y] == i - x - 1) {
							on_line = 1;
							break;
						}
					}
					if (on_line) {
						if (buffer[i - x - 1] != '|') {
							if (!added_half) {
								added_half = buffer[i - x - 1];
							} else {
								int goes = 0;

								if (added_half == 'F' || added_half == '7') {
									goes++;
								} else {
									goes--;
								}

								if (buffer[i - x - 1] == 'F' ||
									buffer[i - x - 1] == '7') {
									goes++;
								} else {
									goes--;
								}

								if (goes == 0) {
									count_left++;
								}

								added_half = 0;
							}
						} else {
							count_left++;
						}
					}
				}
			}

			added_half = 0;

			for (int x = 0; x < i / (WIDTH + 1); x++) {
				if (buffer[i - ((WIDTH + 1) * (x + 1))] == '-' ||
					buffer[i - ((WIDTH + 1) * (x + 1))] == 'F' ||
					buffer[i - ((WIDTH + 1) * (x + 1))] == 'J' ||
					buffer[i - ((WIDTH + 1) * (x + 1))] == 'L' ||
					buffer[i - ((WIDTH + 1) * (x + 1))] == '7') {
					on_line = 0;
					for (int y = 0; y < length; y++) {
						if (positions[y] == i - ((WIDTH + 1) * (x + 1))) {
							on_line = 1;
							break;
						}
					}
					if (on_line) {
						if (buffer[i - ((WIDTH + 1) * (x + 1))] != '-') {
							if (!added_half) {
								added_half =
									buffer[i - ((WIDTH + 1) * (x + 1))];
							} else {
								int goes = 0;

								if (added_half == 'F' || added_half == 'L') {
									goes++;
								} else {
									goes--;
								}

								if (buffer[i - ((WIDTH + 1) * (x + 1))] ==
										'F' ||
									buffer[i - ((WIDTH + 1) * (x + 1))] ==
										'L') {
									goes++;
								} else {
									goes--;
								}

								if (goes == 0) {
									count_top++;
								}

								added_half = 0;
							}
						} else {
							count_top++;
						}
					}
				}
			}

			if (count_top % 2 == 1 && count_left % 2 == 1) {
				inside++;
			}
		}
	}

	printf("Inside: %d\n", inside);

	free(positions);
	free(buffer);

	return 0;
}

int main() { return part_one() || part_two(); }
