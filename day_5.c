#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// 4 or 20
#define SEEDS_COUNT 20

int part_one() {
	FILE *fptr;

	fptr = fopen("input", "r");

	if (fptr == 0) {
		printf("Failed to open \"input\".\n");
		return 1;
	}

	char buffer[1024] = {0};

	uint64_t seeds[SEEDS_COUNT] = {0};
	int edited[SEEDS_COUNT] = {0};
	int seed_id = 0;

	int read = 0;

	uint64_t nums[3] = {-1, -1, -1};
	int id = 0;

	while ((read = fread(buffer, 1, sizeof(buffer), fptr))) {
		for (int i = 0; i < read; i++) {
			uint8_t num = buffer[i] - 48;

			if (num < 10) {
				if (nums[id] == -1) {
					nums[id] = 0;
				}

				nums[id] *= 10;
				nums[id] += num;
			} else if (buffer[i] == ' ' || buffer[i] == '\n') {
				if (seed_id != SEEDS_COUNT && nums[0] != -1) {
					seeds[seed_id] = nums[0];
					seed_id++;

					nums[0] = -1;
				} else if (nums[0] != -1) {
					if (buffer[i] == '\n') {
						for (int x = 0; x < SEEDS_COUNT; x++) {
							if (!edited[x] && seeds[x] >= nums[1] &&
								seeds[x] < nums[1] + nums[2]) {
								seeds[x] = seeds[x] - nums[1] + nums[0];
								edited[x] = 1;
							}
						}

						for (int x = 0; x < 3; x++) {
							nums[x] = -1;
						}
					}
					id = (id + 1) % 3;
				}
			} else if (buffer[i] == ':') {
				for (int x = 0; x < SEEDS_COUNT; x++) {
					edited[x] = 0;
				}
			}
		}
	}

	fclose(fptr);

	uint64_t min = -1;

	for (int i = 0; i < SEEDS_COUNT; i++) {
		if (seeds[i] < min) {
			min = seeds[i];
		}
	}

	printf("Min: %ld\n", min);

	return 0;
}

int part_two() {
	FILE *fptr;

	fptr = fopen("input", "r");

	if (fptr == 0) {
		printf("Failed to open \"input\".\n");
		return 1;
	}

	fseek(fptr, 0L, SEEK_END);
	int file_size = ftell(fptr);
	rewind(fptr);

	char *buffer = malloc(file_size);

	uint64_t seeds[SEEDS_COUNT] = {0};
	uint64_t lowests[SEEDS_COUNT/2] = {[0 ... SEEDS_COUNT/2-1] -1};
	int seed_id = 0;
	
	uint64_t *real_seeds = NULL;
	int *edited = NULL;

	uint64_t nums[3] = {-1, -1, -1};
	int id = 0;

	int through = 0;

	int after_seeds = 0;

	fread(buffer, 1, file_size, fptr);

	for (int i = 0; i < file_size; i++) {
		uint8_t num = buffer[i] - 48;
		if (num < 10) {
			if (nums[id] == -1) {
				nums[id] = 0;
			}

			nums[id] *= 10;
			nums[id] += num;
		} else if (buffer[i] == ' ' || buffer[i] == '\n') {
			if (!after_seeds && seed_id == SEEDS_COUNT) after_seeds = i;
			if (through == SEEDS_COUNT/2 + 1) break;
			if (seed_id == SEEDS_COUNT && (i == file_size-1 || through == 0)) {
				if (through != 0) {
					for (int x = 0; x < seeds[(through-1)*2+1]; x++) {
						if (real_seeds[x] < lowests[through-1]) lowests[through-1] = real_seeds[x];
					}
				}

				i = after_seeds;
				through++;
				if (through > SEEDS_COUNT/2) break;

				free(real_seeds);
				free(edited);

				real_seeds = malloc(seeds[(through-1)*2+1] * sizeof(uint64_t));
				edited = malloc(seeds[(through-1)*2+1] * sizeof(int));

				for (int x = 0; x < seeds[(through-1)*2+1]; x++) {
					real_seeds[x] = seeds[(through-1)*2] + x;
				}

				for (int x = 0; x < 3; x++) {
					nums[x] = -1;
				}

				id = 0;

				continue;
			}

			if (seed_id != SEEDS_COUNT && nums[0] != -1) {
				seeds[seed_id] = nums[0];
				seed_id++;

				nums[0] = -1;
			} else if (nums[0] != -1) {
				if (buffer[i] == '\n') {
					for (int x = 0; x < seeds[(through-1)*2+1]; x++) {
						if (!edited[x] && real_seeds[x] >= nums[1] &&
							real_seeds[x] < nums[1] + nums[2]) {
							real_seeds[x] = real_seeds[x] - nums[1] + nums[0];
							edited[x] = 1;
						}
					}

					for (int x = 0; x < 3; x++) {
						nums[x] = -1;
					}
				}
				id = (id + 1) % 3;
			}
		} else if (buffer[i] == ':' && seed_id == SEEDS_COUNT) {
			for (int x = 0; x < seeds[(through-1)*2+1]; x++) {
				edited[x] = 0;
			}
		}
	}

	fclose(fptr);
	free(real_seeds);
	free(edited);


	uint64_t min = -1;

	for (int i = 0; i < SEEDS_COUNT/2; i++) {
		if (lowests[i] < min) {
			min = lowests[i];
		}
	}

	printf("Min: %ld\n", min);

	return 0;
}

int main() {
	if (part_one() || part_two()) {
		return 1;
	}
	return 0;
}
