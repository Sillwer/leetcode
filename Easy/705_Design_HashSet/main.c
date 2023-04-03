#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define bool int
#define false 0
#define true 1
#define SIZE 100

typedef struct MyHashSet {
    int value;
    struct MyHashSet *next;
} MyHashSet;

int get_hash(int key);
MyHashSet *myHashSetCreate();
void myHashSetFree(MyHashSet *obj);
bool myHashSetContains(MyHashSet *obj, int key);
void myHashSetAdd(MyHashSet *obj, int key);
void myHashSetRemove(MyHashSet *obj, int key);
void hash_print(MyHashSet *root);

int main(void) {
    int exists;

    printf("Create hash-table: ");
    MyHashSet *obj = myHashSetCreate();
    hash_print(obj);

    printf("Add elements (1) and (2): ");
    myHashSetAdd(obj, 1);  // set = [1]
    myHashSetAdd(obj, 2);  // set = [1, 2]
    hash_print(obj);

    exists = myHashSetContains(obj, 1);  // return True
    printf("check availability element (1) -> %s\n", exists ? "true" : "false");

    exists = myHashSetContains(obj, 3);  // return False, (not found)
    printf("check availability element (3) -> %s\n", exists ? "true" : "false");

    printf("Add element (2): ");
    myHashSetAdd(obj, 2);  // set = [1, 2]
    hash_print(obj);

    exists = myHashSetContains(obj, 2);  // return True
    printf("check availability element (2) -> %s\n", exists ? "true" : "false");

    printf("Remove element (2): ");
    hash_print(obj);

    myHashSetRemove(obj, 2);             // set = [1]
    exists = myHashSetContains(obj, 2);  // return False, (already removed)
    printf("check availability element (2) -> %s\n", exists ? "true" : "false");

    myHashSetFree(obj);
    return 0;
}

int get_hash(int key) {
    int n = SIZE;                     // size of hash-table
    double A = 0.618033;              // arbitrary constant - choosed from golden section
    int hash = n * fmod(key * A, 1);  // multiplicative method of hashing

    return hash;
}

MyHashSet *myHashSetCreate() {
    // root of hash-table
    MyHashSet *obj = malloc(SIZE * sizeof(MyHashSet));

    for (int i = 0; i < SIZE; i++) {
        // buckets of hash-table
        obj[i].value = -1;
        obj[i].next = NULL;
    }

    return obj;
}

void myHashSetFree(MyHashSet *obj) {
    for (int i = 0; i < SIZE; i++) {
        MyHashSet *current = obj[i].next;

        while (current != NULL) {
            // deleting elements of hash-table
            MyHashSet *for_delete = current;
            current = current->next;
            free(for_delete);
        }
    }

    free(obj);  // deleting root of hash-table
}

bool myHashSetContains(MyHashSet *obj, int key) {
    bool result = false;

    int hash = get_hash(key);

    if (obj[hash].value != -1) {
        // go throught elements in relevant table
        MyHashSet *current = obj + hash;

        while (true) {
            if (current == NULL || current->value == key) break;
            current = current->next;
        }
        if (current != NULL) result = true;
    }

    return result;
}

void myHashSetAdd(MyHashSet *obj, int key) {
    // if element is exist in hash-table - dont do duplicate
    if (myHashSetContains(obj, key)) return;

    int hash = get_hash(key);

    if (obj[hash].value == -1)
        // if bucket is free, then just set element
        obj[hash].value = key;
    else {
        // else go to end of bucket
        MyHashSet *current = (obj + hash);
        while (current->next != NULL) current = current->next;
        // and add new element
        MyHashSet *new_node = malloc(SIZE * sizeof(MyHashSet));
        new_node->value = key;
        new_node->next = NULL;

        current->next = new_node;
    }
}

void myHashSetRemove(MyHashSet *obj, int key) {
    int hash = get_hash(key);

    if (obj[hash].value != -1) {  // if bucket not empty
        // if need remove first element in bucket
        if (obj[hash].value == key) {
            MyHashSet *for_delete = obj[hash].next;

            if (for_delete != NULL) {
                obj[hash].value = for_delete->value;
                obj[hash].next = for_delete->next;
            } else {
                obj[hash].value = -1;
                obj[hash].next = NULL;
            }
        } else {
            // if need remove second or farther element
            MyHashSet *for_delete = obj[hash].next;
            MyHashSet *prev = obj + hash;
            while (1) {  // search element
                if (for_delete == NULL || for_delete->value == key) break;
                prev = for_delete;
                for_delete = for_delete->next;
            }

            if (for_delete != NULL) {
                prev->next = for_delete->next;
                free(for_delete);
            }
        }
    }
}

void hash_print(MyHashSet *root) {
    printf("[ ");
    for (int i = 0; i < SIZE; i++) {
        MyHashSet *current = root + i;
        while (current != NULL) {
            if (current->value != -1) printf("%d ", current->value);
            current = current->next;
        }
    }
    printf("]\n");
}