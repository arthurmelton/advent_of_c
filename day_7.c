#include <stdint.h>
#include <stdio.h>

// 5 or 1000
#define HANDS 1000

int part_one() {
	FILE *fptr = fopen("input", "r");

	if (fptr == 0) {
		printf("Error opening \"input\".\n");
		return 1;
	}

	char buffer[1024];

	int cards[HANDS][5];
	int types[HANDS] = {0};
	uint64_t scores[HANDS];
	int bets[HANDS];
	int cards_index[2] = {0};

	int read;
	int current_number = 0;

	while ((read = fread(buffer, 1, sizeof(buffer), fptr))) {
		for (int i = 0; i < read; i++) {
			uint8_t num = buffer[i] - 48;

			if (num < 10 && cards_index[1] == 5) {
				current_number *= 10;
				current_number += num;
			} else if (buffer[i] == '\n') {
				bets[cards_index[0]] = current_number;
				current_number = 0;

				cards_index[0]++;
				cards_index[1] = 0;
			} else if (cards_index[1] < 5) {
				int score;
				if (buffer[i] == '2')
					score = 0;
				else if (buffer[i] == '3')
					score = 1;
				else if (buffer[i] == '4')
					score = 2;
				else if (buffer[i] == '5')
					score = 3;
				else if (buffer[i] == '6')
					score = 4;
				else if (buffer[i] == '7')
					score = 5;
				else if (buffer[i] == '8')
					score = 6;
				else if (buffer[i] == '9')
					score = 7;
				else if (buffer[i] == 'T')
					score = 8;
				else if (buffer[i] == 'J')
					score = 9;
				else if (buffer[i] == 'Q')
					score = 10;
				else if (buffer[i] == 'K')
					score = 11;
				else /* (buffer[i] == 'A') */
					score = 12;

				cards[cards_index[0]][cards_index[1]] = score;
				cards_index[1]++;
			}
		}
	}

	for (int i = 0; i < HANDS; i++) {
		int counts[13] = {0};

		for (int x = 0; x < 5; x++) {
			counts[cards[i][x]]++;
		}

		int type = 0;
		for (int x = 0; x < sizeof(counts) / sizeof(*counts); x++) {
			if (counts[x] == 5) {
				types[i] = 6;
				break;
			} else if (counts[x] == 4) {
				types[i] = 5;
				break;
			} else if (counts[x] == 3) {
				if (type == 1) {
					types[i] = 4;
					break;
				}
				type = 3;
			} else if (counts[x] == 2) {
				if (type == 1) {
					types[i] = 2;
				} else if (type == 3) {
					types[i] = 4;
				} else {
					type = 1;
				}
			}
		}
		if (!types[i]) types[i] = type;

		scores[i] = (((uint64_t)(types[i])) << (6 * 4)) +
					(((uint64_t)(cards[i][0])) << (5 * 4)) +
					(((uint64_t)(cards[i][1])) << (4 * 4)) +
					(((uint64_t)(cards[i][2])) << (3 * 4)) +
					(((uint64_t)(cards[i][3])) << (2 * 4)) +
					(((uint64_t)(cards[i][4])) << (1 * 4));
	}

	int new_cards[HANDS][2] = {0};

	for (int i = 0; i < HANDS; i++) {
		for (int x = 0; x < HANDS; x++) {
			if (scores[i] > new_cards[x][0]) {
				for (int y = HANDS - 1; y > x; y--) {
					new_cards[y][0] = new_cards[y - 1][0];
					new_cards[y][1] = new_cards[y - 1][1];
				}
				new_cards[x][0] = scores[i];
				new_cards[x][1] = i;
				break;
			}
		}
	}

	int total = 0;

	for (int i = 0; i < HANDS; i++) {
		int index = new_cards[i][1];
		total += bets[index] * (HANDS - i);
	}

	printf("Total: %d\n", total);

	fclose(fptr);

	return 0;
}

int part_two() {
	FILE *fptr = fopen("input", "r");

	if (fptr == 0) {
		printf("Error opening \"input\".\n");
		return 1;
	}

	char buffer[1024];

	int cards[HANDS][5];
	int types[HANDS] = {0};
	uint64_t scores[HANDS];
	int bets[HANDS];
	int cards_index[2] = {0};

	int read;
	int current_number = 0;

	while ((read = fread(buffer, 1, sizeof(buffer), fptr))) {
		for (int i = 0; i < read; i++) {
			uint8_t num = buffer[i] - 48;

			if (num < 10 && cards_index[1] == 5) {
				current_number *= 10;
				current_number += num;
			} else if (buffer[i] == '\n') {
				bets[cards_index[0]] = current_number;
				current_number = 0;

				cards_index[0]++;
				cards_index[1] = 0;
			} else if (cards_index[1] < 5) {
				int score;
				if (buffer[i] == 'J')
					score = 0;
				else if (buffer[i] == '2')
					score = 1;
				else if (buffer[i] == '3')
					score = 2;
				else if (buffer[i] == '4')
					score = 3;
				else if (buffer[i] == '5')
					score = 4;
				else if (buffer[i] == '6')
					score = 5;
				else if (buffer[i] == '7')
					score = 6;
				else if (buffer[i] == '8')
					score = 7;
				else if (buffer[i] == '9')
					score = 8;
				else if (buffer[i] == 'T')
					score = 9;
				else if (buffer[i] == 'Q')
					score = 10;
				else if (buffer[i] == 'K')
					score = 11;
				else /* (buffer[i] == 'A') */
					score = 12;

				cards[cards_index[0]][cards_index[1]] = score;
				cards_index[1]++;
			}
		}
	}

	for (int i = 0; i < HANDS; i++) {
		int counts[13] = {0};

		int highest = 0;

		for (int x = 0; x < 5; x++) {
			counts[cards[i][x]]++;
			if (cards[i][x] != 0 && counts[cards[i][x]] > highest) {
				highest = counts[cards[i][x]];
			}
		}

		for (int x = 1; x < 13; x++) {
			if (counts[x] == highest) {
				counts[x] += counts[0];
				break;
			}
		}

		counts[0] = 0;

		int type = 0;
		for (int x = 0; x < sizeof(counts) / sizeof(*counts); x++) {
			if (counts[x] == 5) {
				types[i] = 6;
				break;
			} else if (counts[x] == 4) {
				types[i] = 5;
				break;
			} else if (counts[x] == 3) {
				if (type == 1) {
					types[i] = 4;
					break;
				}
				type = 3;
			} else if (counts[x] == 2) {
				if (type == 1) {
					types[i] = 2;
				} else if (type == 3) {
					types[i] = 4;
				} else {
					type = 1;
				}
			}
		}
		if (!types[i]) types[i] = type;

		scores[i] = (((uint64_t)(types[i])) << (6 * 4)) +
					(((uint64_t)(cards[i][0])) << (5 * 4)) +
					(((uint64_t)(cards[i][1])) << (4 * 4)) +
					(((uint64_t)(cards[i][2])) << (3 * 4)) +
					(((uint64_t)(cards[i][3])) << (2 * 4)) +
					(((uint64_t)(cards[i][4])) << (1 * 4));

		// printf("%d %d %d %d %d - %d, %d, %ld\n", cards[i][0], cards[i][1],
		// cards[i][2], cards[i][3], cards[i][4], bets[i], types[i], scores[i]);
	}

	int new_cards[HANDS][2] = {0};

	for (int i = 0; i < HANDS; i++) {
		for (int x = 0; x < HANDS; x++) {
			if (scores[i] > new_cards[x][0]) {
				for (int y = HANDS - 1; y > x; y--) {
					new_cards[y][0] = new_cards[y - 1][0];
					new_cards[y][1] = new_cards[y - 1][1];
				}
				new_cards[x][0] = scores[i];
				new_cards[x][1] = i;
				break;
			}
		}
	}

	int total = 0;

	for (int i = 0; i < HANDS; i++) {
		int index = new_cards[i][1];
		total += bets[index] * (HANDS - i);
		printf("%d %d %d %d %d - %d, %ld\n", cards[index][0], cards[index][1],
			   cards[index][2], cards[index][3], cards[index][4], bets[index],
			   scores[index]);
	}

	printf("Total with jack: %d\n", total);

	fclose(fptr);

	return 0;
}

int main() { return part_one() || part_two(); }
