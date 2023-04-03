#include <stdio.h>

void quick_sort(int* arr, int left, int right);
int numRescueBoats(int* people, int peopleSize, int limit);

int main(void) {
    int input[] = {3,2,2,1};
    int len = 4;

    printf("Input: ");
    for (int i = 0; i < len; i++) printf("%d ", input[i]);

    int output = numRescueBoats(input, len, 3);
    printf("\nOutput: %d\n", output);

    return 0;
}

int numRescueBoats(int* people, int peopleSize, int limit) {
    int min_ships = 0;

    quick_sort(people, 0, peopleSize - 1);

    int i = peopleSize - 1;  // with the highest weight 
    int j = 0;               // with the lowest weight
    while (i >= j)
    {
        // if boat can handle second take j-people
        if (people[i] + people[j] <= limit) j++;
        // take i-people
        i--;
        // send a boat
        min_ships++;
    }

    return min_ships;
}

void quick_sort(int* arr, int left, int right) {
    if (left < right) {
        int pivote = arr[(right + left) / 2];
        int less = left, more = right;

        do {
            while (arr[less] < pivote) less++;
            while (arr[more] > pivote) more--;

            if (less <= more) {
                int temp = arr[less];
                arr[less] = arr[more];
                arr[more] = temp;
                less++;
                more--;
            }

        } while (less < more);

        quick_sort(arr, left, more);
        quick_sort(arr, less, right);
    }
}