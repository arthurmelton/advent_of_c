#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define INSTRUCTIONS 307
#define NODES 790

int part_one() {
	FILE *fptr = fopen("input", "r");

	if (!fptr) {
		printf("Failed to open \"input\".\n");
		return 1;
	}

	char buffer[1024];

	uint8_t movement[INSTRUCTIONS] = {0};  // too lazy to do bit by bit stuff
	int movement_id = 0;

	uint8_t nodes[NODES][3][3];
	int node_id[3] = {0};

	int read = 0;

	while ((read = fread(buffer, 1, sizeof(buffer), fptr))) {
		for (int i = 0; i < read; i++) {
			if (movement_id < INSTRUCTIONS) {
				movement[movement_id] = MIN(buffer[i] - 76, 1);
				movement_id++;
			} else {
				uint8_t current_char = buffer[i] - 65;

				if (current_char < 26) {
					nodes[node_id[0]][node_id[1]][node_id[2]] = current_char;

					if (node_id[1] == 2 && node_id[2] == 2) {
						node_id[0]++;
						node_id[1] = 0;
					} else if (node_id[2] == 2) {
						node_id[1]++;
					}
					node_id[2] = (node_id[2] + 1) % 3;
				}
			}
		}
	}

	fclose(fptr);

	int current_node = 0;
	int current_movement = 0;
	int moves = 0;

	for (int i = 0; i < NODES; i++) {
		if (nodes[i][0][0] == 0 && nodes[i][0][1] == 0 && nodes[i][0][2] == 0) {
			current_node = i;
			break;
		}
	}

	while (nodes[current_node][0][0] != 25 || nodes[current_node][0][1] != 25 ||
		   nodes[current_node][0][2] != 25) {
		uint8_t new[3];

		new[0] = nodes[current_node][movement[current_movement] + 1][0];
		new[1] = nodes[current_node][movement[current_movement] + 1][1];
		new[2] = nodes[current_node][movement[current_movement] + 1][2];

		for (int i = 0; i < NODES; i++) {
			if (nodes[i][0][0] == new[0] && nodes[i][0][1] == new[1] &&
				nodes[i][0][2] == new[2]) {
				current_node = i;
				break;
			}
		}

		current_movement = (current_movement + 1) % INSTRUCTIONS;
		moves++;
	}

	printf("Moves: %d\n", moves);

	return 0;
}

int part_two() {
	FILE *fptr = fopen("input", "r");

	if (!fptr) {
		printf("Failed to open \"input\".\n");
		return 1;
	}

	char buffer[1024];

	uint8_t movement[INSTRUCTIONS] = {0};  // too lazy to do bit by bit stuff
	int movement_id = 0;

	uint8_t nodes[NODES][3][3];
	int node_id[3] = {0};

	int read = 0;

	while ((read = fread(buffer, 1, sizeof(buffer), fptr))) {
		for (int i = 0; i < read; i++) {
			if (movement_id < INSTRUCTIONS) {
				movement[movement_id] = MIN(buffer[i] - 76, 1);
				movement_id++;
			} else {
				uint8_t current_char = buffer[i] - 65;

				if (current_char < 26) {
					nodes[node_id[0]][node_id[1]][node_id[2]] = current_char;

					if (node_id[1] == 2 && node_id[2] == 2) {
						node_id[0]++;
						node_id[1] = 0;
					} else if (node_id[2] == 2) {
						node_id[1]++;
					}
					node_id[2] = (node_id[2] + 1) % 3;
				}
			}
		}
	}

	fclose(fptr);

	int node_numbers = 0;
	int *current_nodes = NULL;
	int current_movement = 0;
	uint64_t moves = 1;

	for (int i = 0; i < NODES; i++) {
		if (nodes[i][0][2] == 0) {
			node_numbers++;
			current_nodes = realloc(current_nodes, node_numbers * sizeof(int));
			current_nodes[node_numbers - 1] = i;
		}
	}

	int *state = malloc(node_numbers * sizeof(int));
	int *times = malloc(node_numbers * sizeof(int));

	for (int i = 0; i < node_numbers; i++) {
		state[i] = 0;
		times[i] = 0;
	}

	while (1) {
		int found_end = 1;
		for (int i = 0; i < node_numbers; i++) {
			if (!times[i]) {
				found_end = 0;
				break;
			}
		}

		if (found_end) {
			break;
		}

		for (int i = 0; i < node_numbers; i++) {
			if (!times[i]) {
				uint8_t new[3];

				new[0] =
					nodes[current_nodes[i]][movement[current_movement] + 1][0];
				new[1] =
					nodes[current_nodes[i]][movement[current_movement] + 1][1];
				new[2] =
					nodes[current_nodes[i]][movement[current_movement] + 1][2];

				if (new[2] == 25) {
					times[i] = moves;
					continue;
				}

				for (int x = 0; x < NODES; x++) {
					if (nodes[x][0][0] == new[0] && nodes[x][0][1] == new[1] &&
						nodes[x][0][2] == new[2]) {
						current_nodes[i] = x;
						break;
					}
				}
			}
		}

		current_movement = (current_movement + 1) % INSTRUCTIONS;
		moves++;
	}

	free(current_nodes);

	moves = times[0];
	while (1) {
		int found_end = 1;
		for (int i = 1; i < node_numbers; i++) {
			if (moves % times[i] != 0) {
				found_end = 0;
				break;
			}
		}

		if (found_end) {
			break;
		}

		moves += times[0];
	}

	free(times);

	printf("Moves: %ld\n", moves);

	return 0;
}

int main() { return part_one() || part_two(); }
