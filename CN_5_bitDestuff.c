#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

void bit_destuffing(char *input, char *output) {
    int i, j, count;
    int len = strlen(input);

    count = 0;
    j = 0;

    for (i = 0; i < len; i++) {
        if (input[i] == '1') {
            output[j++] = input[i];
            count++;
        } else {
            output[j++] = input[i];
            count = 0;
        }

        if (count == 5) {
            i++; // Skip the stuffed '0' bit
            count = 0;
        }
    }

    output[j] = '\0';
}

int main() {
    char input[MAX_SIZE], output[MAX_SIZE];

    printf("Enter the received frame (0's and 1's only): ");
    scanf("%s", input);

    bit_destuffing(input, output);

    printf("After bit de-stuffing: %s\n", output);

    return 0;
}

