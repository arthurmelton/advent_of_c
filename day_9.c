#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define HISTORIES 200
#define NUMBERS 21

//#define HISTORIES 3
//#define NUMBERS 6

int part_one() {
    FILE *fptr = fopen("input", "r");

    if (!fptr) {
        printf("Failed to open \"input\".\n");
        return 1;
    }

    int numbers[HISTORIES][NUMBERS];
    int index[2] = {0};
    int current_number = 0;
    int negative = 0;

    char buffer[1024];

    int read;

    while((read = fread(buffer, 1, sizeof(buffer), fptr))) {
        for (int i = 0; i < read; i++) {
            uint8_t num = buffer[i]-48;

            if (num < 10) {
                current_number *= 10;
                current_number += num;
            }
            else if (buffer[i] == '-') {
                negative = 1;
            }
            else {
                if (negative) {
                    current_number *= -1;
                }
                numbers[index[0]][index[1]] = current_number;
                index[1]++;
                if (index[1] == NUMBERS) {
                    index[0]++;
                    index[1] = 0;
                }
                current_number = 0;
                negative = 0;
            }
        }
    }

    fclose(fptr);

    int total = 0;

    for (int y = 0; y < HISTORIES; y++) {
        int iteration = 1;
        int *number_table = malloc((NUMBERS+1)*iteration*sizeof(int));

        if (!number_table) {
            printf("Cant alloc enough space\n");
            return 1;
        }

        for (int i = 0; i < NUMBERS; i++) {
            number_table[i] = numbers[y][i];
        }

        while(1) {
            int all_zeros = 1;
            for (int i = 0; i < NUMBERS+1-iteration; i++) {
                if (number_table[((NUMBERS+1)*(iteration-1))+i]) {
                    all_zeros = 0;
                    break;
                }
            }
            if (all_zeros) {
                break;
            }

            iteration++;

            number_table = realloc(number_table, (NUMBERS+1)*iteration*sizeof(int));

            if (!number_table) {
                printf("Cant realloc enough space\n");
                return 1;
            }

            for (int i = 0; i < NUMBERS-iteration+1; i++) {
                number_table[(NUMBERS+1)*(iteration-1)+i] = number_table[(NUMBERS+1)*(iteration-2)+i+1] - number_table[(NUMBERS+1)*(iteration-2)+i];
            }
        }

        number_table[NUMBERS*iteration] = 0;

        for (int i = iteration-1; i > 0; i--) {
            number_table[(NUMBERS+1)*(i-1)+NUMBERS+1-i] = number_table[(NUMBERS+1)*(i-1)+NUMBERS-i] + number_table[(NUMBERS+1)*(i-1)+NUMBERS*2+1-i];
        }

        total += number_table[NUMBERS];

        free(number_table);
    }

    printf("Total: %d\n", total);

    return 0;
}

int part_two() {
    FILE *fptr = fopen("input", "r");

    if (!fptr) {
        printf("Failed to open \"input\".\n");
        return 1;
    }

    int numbers[HISTORIES][NUMBERS];
    int index[2] = {0, NUMBERS-1};
    int current_number = 0;
    int negative = 0;

    char buffer[1024];

    int read;

    while((read = fread(buffer, 1, sizeof(buffer), fptr))) {
        for (int i = 0; i < read; i++) {
            uint8_t num = buffer[i]-48;

            if (num < 10) {
                current_number *= 10;
                current_number += num;
            }
            else if (buffer[i] == '-') {
                negative = 1;
            }
            else {
                if (negative) {
                    current_number *= -1;
                }
                numbers[index[0]][index[1]] = current_number;
                index[1]--;
                if (index[1] == -1) {
                    index[0]++;
                    index[1] = NUMBERS-1;
                }
                current_number = 0;
                negative = 0;
            }
        }
    }

    fclose(fptr);

    int total = 0;

    for (int y = 0; y < HISTORIES; y++) {
        int iteration = 1;
        int *number_table = malloc((NUMBERS+1)*iteration*sizeof(int));

        if (!number_table) {
            printf("Cant alloc enough space\n");
            return 1;
        }

        for (int i = 0; i < NUMBERS; i++) {
            number_table[i] = numbers[y][i];
        }

        while(1) {
            int all_zeros = 1;
            for (int i = 0; i < NUMBERS+1-iteration; i++) {
                if (number_table[((NUMBERS+1)*(iteration-1))+i]) {
                    all_zeros = 0;
                    break;
                }
            }
            if (all_zeros) {
                break;
            }

            iteration++;

            number_table = realloc(number_table, (NUMBERS+1)*iteration*sizeof(int));

            if (!number_table) {
                printf("Cant realloc enough space\n");
                return 1;
            }

            for (int i = 0; i < NUMBERS-iteration+1; i++) {
                number_table[(NUMBERS+1)*(iteration-1)+i] = number_table[(NUMBERS+1)*(iteration-2)+i+1] - number_table[(NUMBERS+1)*(iteration-2)+i];
            }
        }

        number_table[NUMBERS*iteration] = 0;

        for (int i = iteration-1; i > 0; i--) {
            number_table[(NUMBERS+1)*(i-1)+NUMBERS+1-i] = number_table[(NUMBERS+1)*(i-1)+NUMBERS-i] + number_table[(NUMBERS+1)*(i-1)+NUMBERS*2+1-i];
        }

        total += number_table[NUMBERS];

        free(number_table);
    }

    printf("Total: %d\n", total);

    return 0;
}

int main() {
    return part_one() || part_two();
}
