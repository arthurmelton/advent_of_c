#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int part_one() {
	FILE *fptr = fopen("input", "r");

	if (!fptr) {
		printf("Could not read \"input\".");
		return 1;
	}

	char buffer[1024];

	int read;

	uint8_t current = 0;
	int total = 0;

	while ((read = fread(buffer, 1, sizeof(buffer), fptr))) {
		for (int i = 0; i < read; i++) {
			if (buffer[i] == ',' || buffer[i] == '\n') {
				total += current;
				current = 0;
			} else {
				current = ((int)current + buffer[i]) * 17;
			}
		}
	}

	fclose(fptr);

	printf("Total %d\n", total);

	return 0;
}

int part_two() {
	FILE *fptr = fopen("input", "r");

	if (!fptr) {
		printf("Could not read \"input\".");
		return 1;
	}

	char buffer[1024];

	int read;

	uint8_t current = 0;
	int total = 0;
	int equals = 0;

	char *text = NULL;
	int text_length = 0;

	uint8_t *boxes[256] = {[0 ... 255] = NULL};
	int lengths[256] = {0};

	while ((read = fread(buffer, 1, sizeof(buffer), fptr))) {
		for (int i = 0; i < read; i++) {
			if (buffer[i] == ',' || buffer[i] == '\n') {
				current = 0;
				text_length = 0;
			} else if (buffer[i] == '=') {
				equals = 1;
			} else if (equals == 1) {
				equals = 0;
				char *current_text = NULL;
				int current_text_length = 0;
				int found = 0;
				for (int k = 0; k < lengths[current]; k++) {
					if (boxes[current][k] != '\0') {
						current_text_length++;
						current_text =
							realloc(current_text, current_text_length);
						current_text[current_text_length - 1] =
							boxes[current][k];
					} else {
						if (text_length == current_text_length &&
							memcmp(&text[0], &current_text[0],
								   current_text_length) == 0) {
							boxes[current][k + 1] = buffer[i] - 48;
							found = 1;
							break;
						}

						free(current_text);
						current_text = NULL;
						current_text_length = 0;
					}
				}
				free(current_text);

				if (!found) {
					lengths[current] += text_length + 3;
					boxes[current] = realloc(boxes[current], lengths[current]);
					memcpy(
						boxes[current] + lengths[current] - (text_length + 3),
						text, text_length);
					boxes[current][lengths[current] - 3] = '\0';
					boxes[current][lengths[current] - 2] = buffer[i] - 48;
					boxes[current][lengths[current] - 1] = '\0';
				}
			} else if (buffer[i] == '-') {
				char *current_text = NULL;
				int current_text_length = 0;
				for (int k = 0; k < lengths[current]; k++) {
					if (boxes[current][k] != '\0') {
						current_text_length++;
						current_text =
							realloc(current_text, current_text_length);
						current_text[current_text_length - 1] =
							boxes[current][k];
					} else {
						if (text_length == current_text_length &&
							memcmp(&text[0], &current_text[0],
								   current_text_length) == 0) {
							lengths[current] -= text_length + 3;
							for (int y = k; y < lengths[current] + text_length;
								 y++) {
								boxes[current][y - text_length] =
									boxes[current][y + 3];
							}
							boxes[current] =
								realloc(boxes[current], lengths[current]);
							break;
						}

						free(current_text);
						current_text = NULL;
						current_text_length = 0;
					}
				}
				free(current_text);
			} else {
				text_length++;
				text = realloc(text, text_length);
				text[text_length - 1] = buffer[i];

				current = ((int)current + buffer[i]) * 17;
			}
		}
	}

	fclose(fptr);

	for (int i = 0; i < 256; i++) {
		int if_odd = 0;
		int index = 0;
		for (int k = 0; k < lengths[i]; k++) {
			if (boxes[i][k] == '\0') {
				if_odd = !if_odd;
			} else if (if_odd) {
				index++;
				printf("k: %d, index: %d, lense: %d\n", i + 1, index,
					   boxes[i][k]);
				total += (i + 1) * index * boxes[i][k];
			} else {
				printf("%c\n", boxes[i][k]);
			}
		}
	}

	printf("Total %d\n", total);

	return 0;
}

int main() { return part_one() || part_two(); }
