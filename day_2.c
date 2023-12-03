#include <stdio.h>
#include <stdint.h>

#define POSSIBLE_RED 12
#define POSSIBLE_GREEN 13
#define POSSIBLE_BLUE 14

int part_one()
{
	FILE *fptr;

	fptr = fopen("input", "r");

	if (!fptr) {
		printf("Cant read file \"input\".\n");
		return 0;
	}

	char text[1024];
	int read;

	int max_red = 0;
	int max_green = 0;
	int max_blue = 0;
	int current_game = 0;
	int current_number = 0;
	int id_sums = 0;

	while ((read = fread(text, 1, sizeof(text), fptr))) {
		for (int i = 0; i < read; i++) {
			uint8_t num = text[i] - 48;
			if (num < 10) {
				current_number *= 10;
				current_number += num;
			} else if (text[i] != ' ') {
				if (text[i] == ':') {
					current_game = current_number;
				} else if (text[i] == 'r') {
					if (current_number > max_red) {
						max_red = current_number;
					}
				} else if (text[i] == 'g') {
					if (current_number > max_green) {
						max_green = current_number;
					}
				} else if (text[i] == 'b') {
					if (current_number > max_blue) {
						max_blue = current_number;
					}
				} else if (text[i] == '\n') {
					i += 5;
					if (max_red <= POSSIBLE_RED
					    && max_green <= POSSIBLE_GREEN
					    && max_blue <= POSSIBLE_BLUE) {
						id_sums += current_game;
					}
					max_red = 0;
					max_green = 0;
					max_blue = 0;
				}
				current_number = 0;
			}
		}
	}

	fclose(fptr);

	printf("Sums: %d\n", id_sums);

	return 0;
}

int part_two()
{
	FILE *fptr;

	fptr = fopen("input", "r");

	if (!fptr) {
		printf("Cant read file \"input\".\n");
		return 0;
	}

	char text[1024];
	int read;

	int min_red = 0;
	int min_green = 0;
	int min_blue = 0;
	int current_number = 0;
	int power_sums = 0;

	while ((read = fread(text, 1, sizeof(text), fptr))) {
		for (int i = 0; i < read; i++) {
			uint8_t num = text[i] - 48;
			if (num < 10) {
				current_number *= 10;
				current_number += num;
			} else if (text[i] != ' ') {
				if (text[i] == 'r') {
					if (current_number > min_red) {
						min_red = current_number;
					}
				} else if (text[i] == 'g') {
					if (current_number > min_green) {
						min_green = current_number;
					}
				} else if (text[i] == 'b') {
					if (current_number > min_blue) {
						min_blue = current_number;
					}
				} else if (text[i] == '\n') {
					i += 5;
					power_sums +=
					    min_red * min_green * min_blue;
					min_red = 0;
					min_green = 0;
					min_blue = 0;
				}
				current_number = 0;
			}
		}
	}

	fclose(fptr);

	printf("Power Sums: %d\n", power_sums);

	return 0;
}

int main()
{
	if (part_one() || part_two()) {
		return 1;
	}
	return 0;
}
