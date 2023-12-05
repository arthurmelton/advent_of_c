#include <stdio.h>
#include <stdint.h>

// 5 or 10
#define FIRST_NUMBER_COUNT 10

int part_one()
{
	FILE *fptr;

	fptr = fopen("input", "r");

	if (fptr == 0) {
		printf("Could not read \"input\".\n");
		return 1;
	}

	int total = 0;
	int winners[FIRST_NUMBER_COUNT];
	int current_num = 0;
	int past_first = 0;
	int num_done = 0;
	int score = 1;

	char buffer[1024] = { 0 };

	int read = 0;

	while ((read = fread(buffer, 1, sizeof(buffer), fptr))) {
		for (int i = 0; i < read; i++) {
			uint8_t num = buffer[i] - 48;

			if (num < 10) {
				current_num *= 10;
				current_num += num;
			} else if ((buffer[i] == ' ' || buffer[i] == '\n')
				   && current_num) {
				if (!past_first) {
					winners[num_done] = current_num;
				} else {
					for (int x = 0; x < FIRST_NUMBER_COUNT;
					     x++) {
						if (current_num == winners[x]) {
							score *= 2;
							break;
						}
					}
				}
				current_num = 0;
				num_done++;

				if (buffer[i] == '\n') {
					total += score >> 1;
					num_done = 0;
					score = 1;
					past_first = 0;
				}
			} else if (buffer[i] == ':') {
				current_num = 0;
			} else if (buffer[i] == '|') {
				past_first = 1;
			}
		}
	}

	printf("Total points: %d\n", total);

	fclose(fptr);

	return 0;
}

int part_two()
{
	FILE *fptr;

	fptr = fopen("input", "r");

	if (fptr == 0) {
		printf("Could not read \"input\".\n");
		return 1;
	}

	int total = 0;
	int winners[FIRST_NUMBER_COUNT];
	int cards[FIRST_NUMBER_COUNT + 1] = {[0 ... FIRST_NUMBER_COUNT] = 1 };
	int current_num = 0;
	int past_first = 0;
	int num_done = 0;
	int score = 0;

	char buffer[1024] = { 0 };

	int read = 0;

	while ((read = fread(buffer, 1, sizeof(buffer), fptr))) {
		for (int i = 0; i < read; i++) {
			uint8_t num = buffer[i] - 48;

			if (num < 10) {
				current_num *= 10;
				current_num += num;
			} else if ((buffer[i] == ' ' || buffer[i] == '\n')
				   && current_num) {
				if (!past_first) {
					winners[num_done] = current_num;
				} else {
					for (int x = 0; x < FIRST_NUMBER_COUNT;
					     x++) {
						if (current_num == winners[x]) {
							score += 1;
							break;
						}
					}
				}

				current_num = 0;
				num_done++;

				if (buffer[i] == '\n') {
					int current_count = cards[0];
					total += current_count;
					for (int x = 0; x < score; x++) {
						cards[x] =
						    cards[x + 1] +
						    current_count;
					}
					for (int x = score;
					     x < FIRST_NUMBER_COUNT; x++) {
						cards[x] = cards[x + 1];
					}

					cards[sizeof(cards) / sizeof(*cards) -
					      1] = 1;

					num_done = 0;
					score = 0;
					past_first = 0;
				}
			} else if (buffer[i] == ':') {
				current_num = 0;
			} else if (buffer[i] == '|') {
				past_first = 1;
			}
		}
	}

	printf("Total points: %d\n", total);

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
