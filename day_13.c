#include <stdio.h>
#include <stdlib.h>

int part_one() {
	FILE *fptr = fopen("input", "r");

	if (!fptr) {
		printf("Failed to open \"input\".\n");
		return 1;
	}

	fseek(fptr, 0L, SEEK_END);
	int file_size = ftell(fptr);
	rewind(fptr);

	char *data = malloc(file_size);

	if (!data) {
		printf("Failed to alloc enough to read file into memory.\n");
		return 1;
	}

	fread(data, 1, file_size, fptr);

	int score = 0;

	int index = 0;

	while (index != file_size) {
		int width = 0;
		int height = 0;

		while (data[index + width] != '\n') {
			width++;
		}

		while (data[index + height * (width + 1)] != '\n') {
			height++;
		}

		int is_horizontal = 0;
		for (int y = 0; y < height; y++) {
			int is_equal = 1;
			for (int x = 0; x < width; x++) {
				if (data[index + y * (width + 1) + x] !=
					data[index + (y + 1) * (width + 1) + x]) {
					is_equal = 0;
					break;
				}
			}

			if (is_equal) {
				int is_fully_equal = 1;

				for (int i = y; i >= 0; i--) {
					int check_with = y - i + (y + 1);
					if (check_with > height - 1) {
						break;
					}

					for (int x = 0; x < width; x++) {
						if (data[index + i * (width + 1) + x] !=
							data[index + check_with * (width + 1) + x]) {
							is_fully_equal = 0;
							break;
						}
					}
				}

				if (is_fully_equal) {
					score += (y + 1) * 100;
					is_horizontal = 1;
					break;
				}
			}
		}
		if (!is_horizontal) {
			for (int x = 0; x < width; x++) {
				int is_equal = 1;
				for (int y = 0; y < height; y++) {
					if (data[index + y * (width + 1) + x] !=
						data[index + y * (width + 1) + x + 1]) {
						is_equal = 0;
						break;
					}
				}

				if (is_equal) {
					int is_fully_equal = 1;

					for (int i = x; i >= 0; i--) {
						int check_with = x - i + (x + 1);
						if (check_with > width - 1) {
							break;
						}

						for (int y = 0; y < height; y++) {
							if (data[index + y * (width + 1) + i] !=
								data[index + y * (width + 1) + check_with]) {
								is_fully_equal = 0;
								break;
							}
						}
					}

					if (is_fully_equal) {
						score += (x + 1);
						break;
					}
				}
			}
		}

		index += height * (width + 1) + 1;
	}

	fclose(fptr);

	printf("Total: %d\n", score);

	return 0;
}

int part_two() {
	FILE *fptr = fopen("input", "r");

	if (!fptr) {
		printf("Failed to open \"input\".\n");
		return 1;
	}

	fseek(fptr, 0L, SEEK_END);
	int file_size = ftell(fptr);
	rewind(fptr);

	char *data = malloc(file_size);

	if (!data) {
		printf("Failed to alloc enough to read file into memory.\n");
		return 1;
	}

	fread(data, 1, file_size, fptr);

	int score = 0;

	int index = 0;

	while (index != file_size) {
		int width = 0;
		int height = 0;

		while (data[index + width] != '\n') {
			width++;
		}

		while (data[index + height * (width + 1)] != '\n') {
			height++;
		}

		int is_horizontal = 0;

		for (int y = 0; y < height; y++) {
			int errors = 0;
			for (int x = 0; x < width; x++) {
				if (data[index + y * (width + 1) + x] !=
					data[index + (y + 1) * (width + 1) + x]) {
					errors++;
					if (errors > 1) {
						break;
					}
				}
			}

			if (errors < 2) {
				for (int i = y - 1; i >= 0; i--) {
					int check_with = y - i + (y + 1);

					if (check_with > height - 1) {
						break;
					}

					for (int x = 0; x < width; x++) {
						if (data[index + i * (width + 1) + x] !=
							data[index + check_with * (width + 1) + x]) {
							errors++;
							if (errors > 1) {
								break;
							}
						}
					}
				}

				if (errors == 1) {
					score += (y + 1) * 100;
					is_horizontal = 1;
					break;
				}
			}
		}
		if (!is_horizontal) {
			for (int x = 0; x < width; x++) {
				int errors = 0;
				for (int y = 0; y < height; y++) {
					if (data[index + y * (width + 1) + x] !=
						data[index + y * (width + 1) + x + 1]) {
						errors++;
						if (errors > 1) {
							break;
						}
					}
				}

				if (errors < 2) {
					for (int i = x - 1; i >= 0; i--) {
						int check_with = x - i + (x + 1);

						if (check_with > width - 1) {
							break;
						}

						for (int y = 0; y < height; y++) {
							if (data[index + y * (width + 1) + i] !=
								data[index + y * (width + 1) + check_with]) {
								errors++;
								if (errors > 1) {
									break;
								}
							}
						}
					}

					if (errors == 1) {
						score += (x + 1);
						break;
					}
				}
			}
		}

		index += height * (width + 1) + 1;
	}

	fclose(fptr);
	free(data);

	printf("Total: %d\n", score);

	return 0;
}

int main() { return part_one() || part_two(); }
