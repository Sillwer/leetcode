#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void quick_sort(int* arr, int left, int right);
int binary_search_modified(int* arr, int arr_len, long long key, int* last_index);
int* successfulPairs(int* spells, int spellsSize, int* potions, int potionsSize, long long success,
                     int* returnSize);

void print_arr(int* arr, int len, char* message);

int main(void) {
    int spells[] = {5, 1, 3}, spellsSize = 3;
    int potions[] = {1, 2, 3, 4, 5}, potionsSize = 5;
    long long success = 7;
    int resultSize;
    int* result = successfulPairs(spells, spellsSize, potions, potionsSize, success, &resultSize);

    print_arr(spells, spellsSize, "spells ");
    print_arr(potions, potionsSize, "potions");
    print_arr(result, resultSize, "Output ");

    free(result);
    return 0;
}

// 0) prepare fase - sort potions
// do for evry spell:
//      1) define necessary power of porion (for example 8)
//      2) find potion with defined power (8)
//      3) if nod found, search more powerfull potion (9 or more)
//      4) define count of potions from current to end - it's answer
int* successfulPairs(int* spells, int spellsSize, int* potions, int potionsSize, long long success,
                     int* returnSize) {
    *returnSize = spellsSize;
    int* result = malloc(*returnSize * sizeof(int));

    // prepare fase-0 - sort by non-decreasing ascending
    quick_sort(potions, 0, potionsSize - 1);

    // do for every spell
    for (int i = 0; i < spellsSize; i++) {
        // fase-1 - define necessary power of porion (for example 8)
        long long success_potion_strength = ceil(success * 1.0 / spells[i]);

        // fase-2 find potion with defined power (8)
        int last_index;  // memorize the index of the potion close in strength to the desired potion
        int success_potion_id =
            binary_search_modified(potions, potionsSize, success_potion_strength, &last_index);

        // fase-3 if nod found the poison with necessary power, search more powerfull potion (9 or more)
        if (success_potion_id == -1) {
            while (last_index < potionsSize) {
                if (potions[last_index] > success_potion_strength) {
                    success_potion_id = last_index;
                    break;
                }
                last_index++;
            }
        }

        if (success_potion_id == -1)
            result[i] = 0;
        else
            // calculate cout of rihght porions
            result[i] = potionsSize - success_potion_id;
    }

    return result;
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

int binary_search_modified(int* arr, int arr_len, long long key, int* last_index) {
    int result = -1;
    int left = 0, right = arr_len - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (key == arr[mid]) {
            result = mid;
            right = mid - 1;
        } else if (key < arr[mid]) {
            right = mid - 1;
        } else if (key > arr[mid]) {
            left = mid + 1;
        }
    }

    // if not found the potion with necessary power,
    // remember id of the potion with close power
    if (result == -1) *last_index = left;

    return result;
}

void print_arr(int* arr, int len, char* message) {
    printf("%s: [ ", message);
    for (int i = 0; i < len; i++) printf("%d ", arr[i]);
    printf("]\n");
}