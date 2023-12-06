#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

	char buffer[1024] = {0};

	int first_seeds[SEEDS_COUNT] = {0};

	uint32_t *seeds = NULL;
	int seeds_length = 0;

	int *edited = NULL;
	int seed_id = 0;

	int read = 0;

	uint32_t nums[3] = {-1, -1, -1};
	int id = 0;

	while ((read = fread(buffer, 1, sizeof(buffer), fptr))) {
		for (int i = 0; i < read; i++) {
			printf("%d - %c\n", i, buffer[i]);
			uint8_t num = buffer[i] - 48;

			if (num < 10) {
				if (nums[id] == -1) {
					nums[id] = 0;
				}

				nums[id] *= 10;
				nums[id] += num;
			} else if (buffer[i] == ' ' || buffer[i] == '\n') {
				if (seed_id != SEEDS_COUNT && nums[0] != -1) {
					first_seeds[seed_id] = nums[0];
					seed_id++;

					if (seed_id == SEEDS_COUNT) {
						int size = 0;
						for (int x = 0; x < SEEDS_COUNT / 2; x++) {
							size += first_seeds[x * 2 + 1];
						}
						seeds_length = size;

						printf("%d\n", size);

						seeds = (uint32_t *)malloc(size * sizeof(uint32_t));
						edited = (int *)malloc(size * sizeof(int));

						if (seeds == 0) {
							printf(
								"Could not allocate %ld bytes (first iteration "
								"of it)\n",
								size * sizeof(uint32_t));
							return 0;
						}

						if (edited == 0) {
							printf(
								"Could not allocate %ld bytes (second "
								"iteration of it)\n",
								size * sizeof(uint32_t));
							return 0;
						}

						int done = 0;
						for (int x = 0; x < SEEDS_COUNT / 2; x++) {
							for (int y = 0; y < first_seeds[x * 2 + 1]; y++) {
								seeds[done] = first_seeds[x * 2] + y;
								edited[done] = 0;
								done++;
							}
						}
					}

					nums[0] = -1;
				} else if (nums[0] != -1) {
					if (buffer[i] == '\n') {
						for (int x = 0; x < seeds_length; x++) {
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
				for (int x = 0; x < seeds_length; x++) {
					edited[x] = 0;
				}
			}
		}
	}

	fclose(fptr);

	uint32_t min = -1;

	for (int i = 0; i < seeds_length; i++) {
		if (seeds[i] < min) {
			min = seeds[i];
		}
	}

	free(seeds);

	printf("Min: %ld\n", min);

	return 0;
}

int main() {
	if (part_one() || part_two()) {
		return 1;
	}
	return 0;
}
