#include <stdio.h>
#include <stdint.h>

// 11 or 141
#define LINE_LENGTH 141
#define WINDOW_SIZE LINE_LENGTH*2+3
#define WINDOW_INDEX LINE_LENGTH+1

int is_special(uint8_t input)
{
	return (input < 48 && input != 0 && input != 10 && input != 46)
	    || input > 57;
}

int part_one()
{
	FILE *fptr;

	fptr = fopen("input", "r");

	if (!fptr) {
		printf("Could not open \"input\".\n");
		return 1;
	}

	char text;

	int engine_part = 0;
	int current_num = 0;
	int pos = 0;

	char window[WINDOW_SIZE] = "";

	int total_part_numbers = 0;

	while ((text = getc(fptr)) != -1
	       || (window[0] != 0 || window[sizeof(window) - 1] != 0)) {
		for (int k = 1; k < sizeof(window); k++) {
			window[k - 1] = window[k];
		}
		if (text != -1) {
			window[sizeof(window) - 1] = text;
		} else {
			window[sizeof(window) - 1] = 0;
		}

		uint8_t num = window[WINDOW_INDEX] - 48;
		if (num < 10) {
			current_num *= 10;
			current_num += num;
			// Pretty much just check if there is a special next to it
			if (!engine_part
			    && (is_special(window[WINDOW_INDEX - 1])
				|| is_special(window[WINDOW_INDEX + 1])
				||
				is_special(window[WINDOW_INDEX + LINE_LENGTH])
				||
				is_special(window[WINDOW_INDEX - LINE_LENGTH])
				|| (pos != LINE_LENGTH - 1
				    &&
				    (is_special
				     (window[WINDOW_INDEX + LINE_LENGTH + 1])
				     ||
				     is_special(window
						[WINDOW_INDEX -
						 LINE_LENGTH + 1])
				    )
				)
				|| (pos != 0
				    &&
				    (is_special
				     (window[WINDOW_INDEX + LINE_LENGTH - 1])
				     ||
				     is_special(window
						[WINDOW_INDEX -
						 LINE_LENGTH - 1])
				    )
				)
			    )
			    ) {
				engine_part = 1;
			}
		} else {
			if (engine_part) {
				total_part_numbers += current_num;
			}
			engine_part = 0;
			current_num = 0;
		}

		if (window[WINDOW_INDEX] == '\n') {
			pos = 0;
		} else {
			pos += 1;
		}
	}

	fclose(fptr);

	printf("total part numbers: %d\n", total_part_numbers);

	return 0;
}

#define WINDOW_SIZE_2 LINE_LENGTH*3+3
#define WINDOW_INDEX_2 LINE_LENGTH*2+1

int ratios_is_zero(int *ratios, int length)
{
	for (int i = 0; i < length; i++) {
		if (ratios[i]) {
			return 1;
		}
	}
	return 0;
}

int part_two()
{
	FILE *fptr;

	fptr = fopen("input", "r");

	if (!fptr) {
		printf("Could not open \"input\".\n");
		return 1;
	}

	char text;

	int gear_part = -1;
	int current_num = 0;
	int pos = 0;

	char window[WINDOW_SIZE_2] = { 0 };
	int ratios[sizeof(window)][2] = { 0 };

	int total_gear_ratios = 0;

	while ((text = getc(fptr)) != -1
	       || (window[0] != 0 || window[sizeof(window) - 1] != 0)
	       || ratios_is_zero(*ratios, sizeof(window) * 2)) {
		for (int k = 1; k < sizeof(window); k++) {
			window[k - 1] = window[k];

			ratios[k - 1][0] = ratios[k][0];
			ratios[k - 1][1] = ratios[k][1];
		}
		if (text != -1) {
			window[sizeof(window) - 1] = text;
		} else {
			window[sizeof(window) - 1] = 0;
		}

		ratios[sizeof(window) - 1][0] = 0;
		ratios[sizeof(window) - 1][1] = 0;

		gear_part--;

		uint8_t num = window[WINDOW_INDEX_2] - 48;
		if (num < 10) {
			current_num *= 10;
			current_num += num;
			// Pretty much just check if there is a * next to it
			if (gear_part < 0) {
				if (window[WINDOW_INDEX_2 - 1] == '*') {
					gear_part = WINDOW_INDEX_2 - 1;
				} else if (window[WINDOW_INDEX_2 + 1] == '*') {
					gear_part = WINDOW_INDEX_2 + 1;
				} else if (window[WINDOW_INDEX_2 + LINE_LENGTH]
					   == '*') {
					gear_part =
					    WINDOW_INDEX_2 + LINE_LENGTH;
				} else if (window[WINDOW_INDEX_2 - LINE_LENGTH]
					   == '*') {
					gear_part =
					    WINDOW_INDEX_2 - LINE_LENGTH;
				} else if (pos != LINE_LENGTH - 1
					   && window[WINDOW_INDEX_2 +
						     LINE_LENGTH + 1] == '*') {
					gear_part =
					    WINDOW_INDEX_2 + LINE_LENGTH + 1;
				} else if (pos != LINE_LENGTH - 1
					   && window[WINDOW_INDEX_2 -
						     LINE_LENGTH + 1] == '*') {
					gear_part =
					    WINDOW_INDEX_2 - LINE_LENGTH + 1;
				} else if (pos != 0
					   && window[WINDOW_INDEX_2 +
						     LINE_LENGTH - 1] == '*') {
					gear_part =
					    WINDOW_INDEX_2 + LINE_LENGTH - 1;
				} else if (pos != 0
					   && window[WINDOW_INDEX_2 -
						     LINE_LENGTH - 1] == '*') {
					gear_part =
					    WINDOW_INDEX_2 - LINE_LENGTH - 1;
				}
			}
		} else {
			if (gear_part > 0) {
				if (!ratios[gear_part][0]) {
					ratios[gear_part][0] = current_num;
				} else if (!ratios[gear_part][1]) {
					ratios[gear_part][1] = current_num;
				} else {
					ratios[gear_part][0] = -1;
				}
			}

			gear_part = -1;
			current_num = 0;

			if (window[WINDOW_INDEX_2] == '\n') {
				pos = 0;
			} else {
				pos += 1;
			}
		}

		if (ratios[0][0] > 0 && ratios[0][1]) {
			total_gear_ratios += ratios[0][0] * ratios[0][1];
		}
	}

	fclose(fptr);

	printf("total gear ratios: %d\n", total_gear_ratios);

	return 0;
}

int main()
{
	if (part_one() || part_two()) {
		return 1;
	}
	return 0;
}
