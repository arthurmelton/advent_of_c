#include <stdio.h>
#include <stdlib.h>

#define WIDTH 110
#define HEIGHT 110

int part_one() {
	FILE *fptr = fopen("input", "r");

	if (!fptr) {
		printf("Failed to open \"input\".\n");
		return 1;
	}

	char buffer[HEIGHT * (WIDTH + 1)];

	fread(buffer, 1, sizeof(buffer), fptr);

	fclose(fptr);

	int splitters_length = 0;
	int *splitters = NULL;

	int splitters_done = -1;

	int gone_through[HEIGHT * (WIDTH + 1)] = {[0 ... HEIGHT * (WIDTH + 1) - 1] =
												  0};

	int direction = 1;
	int position = 0;

	while (splitters_length << 1 != splitters_done) {
		if (position == -1) {
			position = splitters[splitters_done >> 1];
			if (buffer[position] == '-') {
				if (splitters_done % 2 == 0) {
					direction = -1;
				} else {
					direction = 1;
				}
			} else {
				if (splitters_done % 2 == 0) {
					direction = -(WIDTH + 1);
				} else {
					direction = WIDTH + 1;
				}
			}
			position += direction;
		}
		if (position < 0 || position > sizeof(buffer) ||
			buffer[position] == '\n') {
			splitters_done++;
			position = -1;
			continue;
		}
		gone_through[position] = 1;
		if (buffer[position] == '/') {
			if (direction == 1) {
				direction = -(WIDTH + 1);
			} else if (direction == -(WIDTH + 1)) {
				direction = 1;
			} else if (direction == -1) {
				direction = WIDTH + 1;
			} else if (direction == WIDTH + 1) {
				direction = -1;
			}
		} else if (buffer[position] == '\\') {
			if (direction == 1) {
				direction = WIDTH + 1;
			} else if (direction == WIDTH + 1) {
				direction = 1;
			} else if (direction == -1) {
				direction = -(WIDTH + 1);
			} else if (direction == -(WIDTH + 1)) {
				direction = -1;
			}
		} else if ((buffer[position] == '-' &&
					(direction == WIDTH + 1 || direction == -(WIDTH + 1))) ||
				   (buffer[position] == '|' &&
					(direction == 1 || direction == -1))) {
			splitters_done++;
			int new = 1;
			for (int i = 0; i < splitters_length; i++) {
				if (splitters[i] == position) {
					new = 0;
					break;
				}
			}

			if (new) {
				splitters_length++;
				splitters = realloc(splitters, splitters_length * sizeof(int));
				splitters[splitters_length - 1] = position;
			}

			position = -1;

			continue;
		}
		position += direction;
	}

	free(splitters);

	int total = 0;

	for (int i = 0; i < sizeof(gone_through) / sizeof(*gone_through); i++) {
		total += gone_through[i];
	}

	printf("total: %d\n", total);

	return 0;
}

int part_two() {
	FILE *fptr = fopen("input", "r");

	if (!fptr) {
		printf("Failed to open \"input\".\n");
		return 1;
	}

	char buffer[HEIGHT * (WIDTH + 1)];

	fread(buffer, 1, sizeof(buffer), fptr);

	fclose(fptr);

	int best = 0;

	for (int k = 0; k < 4; k++) {
		int go_by = WIDTH;
		if (k % 2 == 1) {
			go_by = HEIGHT;
		}
		for (int z = 0; z < go_by; z++) {
			int splitters_length = 0;
			int *splitters = NULL;

			int splitters_done = -1;

			int gone_through[HEIGHT * (WIDTH + 1)] = {
				[0 ... HEIGHT * (WIDTH + 1) - 1] = 0};

			int direction;
			int position;

			if (k == 0) {
				position = z;
				direction = WIDTH + 1;

			} else if (k == 1) {
				position = ((WIDTH + 1) * z) + WIDTH;
				direction = -1;

			} else if (k == 2) {
				position = HEIGHT * (WIDTH + 1) - z - 1;
				direction = -WIDTH - 1;
			} else {
				position = (WIDTH + 1) * z;
				direction = 1;
			}

			while (splitters_length << 1 != splitters_done) {
				if (position == -1) {
					position = splitters[splitters_done >> 1];
					if (buffer[position] == '-') {
						if (splitters_done % 2 == 0) {
							direction = -1;
						} else {
							direction = 1;
						}
					} else {
						if (splitters_done % 2 == 0) {
							direction = -(WIDTH + 1);
						} else {
							direction = WIDTH + 1;
						}
					}
					position += direction;
				}
				if (position < 0 || position >= sizeof(buffer) ||
					buffer[position] == '\n') {
					splitters_done++;
					position = -1;
					continue;
				}
				gone_through[position] = 1;
				if (buffer[position] == '/') {
					if (direction == 1) {
						direction = -(WIDTH + 1);
					} else if (direction == -(WIDTH + 1)) {
						direction = 1;
					} else if (direction == -1) {
						direction = WIDTH + 1;
					} else if (direction == WIDTH + 1) {
						direction = -1;
					}
				} else if (buffer[position] == '\\') {
					if (direction == 1) {
						direction = WIDTH + 1;
					} else if (direction == WIDTH + 1) {
						direction = 1;
					} else if (direction == -1) {
						direction = -(WIDTH + 1);
					} else if (direction == -(WIDTH + 1)) {
						direction = -1;
					}
				} else if ((buffer[position] == '-' &&
							(direction == WIDTH + 1 ||
							 direction == -(WIDTH + 1))) ||
						   (buffer[position] == '|' &&
							(direction == 1 || direction == -1))) {
					splitters_done++;
					int new = 1;
					for (int i = 0; i < splitters_length; i++) {
						if (splitters[i] == position) {
							new = 0;
							break;
						}
					}

					if (new) {
						splitters_length++;
						splitters =
							realloc(splitters, splitters_length * sizeof(int));
						splitters[splitters_length - 1] = position;
					}

					position = -1;

					continue;
				}
				position += direction;
			}

			free(splitters);

			int total = 0;

			for (int i = 0; i < sizeof(gone_through) / sizeof(*gone_through);
				 i++) {
				total += gone_through[i];
			}

			if (total > best) {
				best = total;
			}
		}
	}
	printf("Best: %d\n", best);

	return 0;
}

int main() { return part_one() || part_two(); }
