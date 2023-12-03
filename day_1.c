#include <stdio.h>
#include <stdint.h>

int part_one()
{
	FILE *fptr;

	fptr = fopen("input", "r");

	if (fptr == NULL) {
		printf("Cant open file \"input\"");
		return 1;
	}

	char text[1024];

	int total = 0;
	char first = -1;
	char last = -1;

	int read;

	while ((read = fread(text, 1, sizeof(text), fptr))) {
		for (int i = 0; i < sizeof(text) && i < read; i++) {
			uint8_t num = text[i] - 48;
			if (num < 10) {
				if (first == -1) {
					first = num;
				}
				last = num;
			} else if (text[i] == 10) {
				total += first * 10 + last;
				first = -1;
				last = -1;
			}
		}
	}

	printf("total: %d\n", total);

	fclose(fptr);

	return 0;
}

// I dont want to have to end with a \0, to save 1 byte
int get_window_number(char *window, int length)
{
	if (window[1] == 'z' && window[2] == 'e' && window[3] == 'r'
	    && window[4] == 'o')
		return 0;

	if (window[2] == 'o' && window[3] == 'n' && window[4] == 'e')
		return 1;

	if (window[2] == 't' && window[3] == 'w' && window[4] == 'o')
		return 2;

	if (window[0] == 't' && window[1] == 'h' && window[2] == 'r'
	    && window[3] == 'e' && window[4] == 'e')
		return 3;

	if (window[1] == 'f' && window[2] == 'o' && window[3] == 'u'
	    && window[4] == 'r')
		return 4;

	if (window[1] == 'f' && window[2] == 'i' && window[3] == 'v'
	    && window[4] == 'e')
		return 5;

	if (window[2] == 's' && window[3] == 'i' && window[4] == 'x')
		return 6;

	if (window[0] == 's' && window[1] == 'e' && window[2] == 'v'
	    && window[3] == 'e' && window[4] == 'n')
		return 7;

	if (window[0] == 'e' && window[1] == 'i' && window[2] == 'g'
	    && window[3] == 'h' && window[4] == 't')
		return 8;

	if (window[1] == 'n' && window[2] == 'i' && window[3] == 'n'
	    && window[4] == 'e')
		return 9;

	return -1;
}

int part_two()
{
	FILE *fptr;

	fptr = fopen("input", "r");

	if (fptr == NULL) {
		printf("Cant open file \"input\"");
		return 1;
	}

	char text[1024];

	int total = 0;
	char first = -1;
	char last = -1;

	int read;

	char window[5] = "";

	while ((read = fread(text, 1, sizeof(text), fptr))) {
		for (int i = 0; i < sizeof(text) && i < read; i++) {
			for (int k = 0; k < sizeof(window) - 1; k++) {
				window[k] = window[k + 1];
			}
			window[4] = text[i];

			uint8_t num = text[i] - 48;

			int window_number =
			    get_window_number(window, sizeof(window));
			if (window_number > -1) {
				num = window_number;
			}
			if (num < 10) {
				if (first == -1) {
					first = num;
				}
				last = num;
			} else if (text[i] == 10 && first != -1) {
				total += first * 10 + last;
				first = -1;
				last = -1;
			}
		}
	}

	printf("total: %d\n", total);

	fclose(fptr);

	return 0;
}

int main()
{
	if (part_one() || part_two()) {
		return 1;
	}
	return 0;

}
