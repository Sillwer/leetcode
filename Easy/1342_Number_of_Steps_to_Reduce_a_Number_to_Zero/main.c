#include <stdio.h>

int numberOfSteps(int num);

int main(void) {

    int input = 14;
    int output = numberOfSteps(input);

    printf("Input: %d | Output %d\n", input, output);

    return 0;
}


int numberOfSteps(int num) {

    int steps;

    if (num == 0) steps = 0;    // if input 0
    else          steps = 1;    // last step (wen num = 1)

    // one iteration:
    // - reduce by 1 one if num is even
    // - divide by 2
    while (num > 1) {
        // (num % 2) - if num is even then 1 step for reduce by 1   [sometimes]
        // + 1       - step for divide by 2                         [every step]
        steps += (num % 2) + 1;

        // bit shift right - is throw out last digit in binary
        // i.e. minus 1 for even number and divide by 2 anyway
        num = num >> 1;
    }

    return steps;
}