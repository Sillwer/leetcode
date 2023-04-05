#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct MyHashMap {
    int key;
    int value;
    struct MyHashMap *next;
} MyHashMap;

int get_hash(int key);
MyHashMap *myHashMapCreate();
void myHashMapFree(MyHashMap *obj);
int myHashMapGet(MyHashMap *obj, int key);
void myHashMapPut(MyHashMap *obj, int key, int value);
void myHashMapRemove(MyHashMap *obj, int key);
void hash_print(MyHashMap *root);

int main(void) {
    int exists;

    printf("Create hash-table: ");
    MyHashMap *obj = myHashMapCreate();
    hash_print(obj);

    printf("Add elements (1, 1) and (2, 2): ");
    myHashMapPut(obj, 1, 1);  // The map is now [[1,1]]
    myHashMapPut(obj, 2, 2);  // The map is now [[1,1], [2,2]]
    hash_print(obj);

    exists = myHashMapGet(obj, 1);  // return 1, The map is now [[1,1], [2,2]]
    printf("check availability element with key (1) -> %s\n", exists != -1 ? "true" : "false");

    exists = myHashMapGet(obj, 3);  // return -1 (i.e., not found), The map is now [[1,1], [2,2]]
    printf("check availability element with key (3) -> %s\n", exists != -1 ? "true" : "false");

    printf("Add element (2, 1): ");
    myHashMapPut(obj, 2, 1);  // The map is now [[1,1], [2,1]] (i.e., update the existing value)
    hash_print(obj);

    exists = myHashMapGet(obj, 2);  // return 1, The map is now [[1,1], [2,1]]
    printf("check availability element with key (2) -> %s\n", exists != -1 ? "true" : "false");

    printf("Remove element with key (2): ");
    myHashMapRemove(obj, 2);  // remove the mapping for 2, The map is now [[1,1]]
    hash_print(obj);

    exists = myHashMapGet(obj, 2);  // return -1 (i.e., not found), The map is now [[1,1]]
    printf("check availability element with key (2) -> %s\n", exists != -1 ? "true" : "false");

    myHashMapFree(obj);
    return 0;
}

int get_hash(int key) {
    int n = SIZE;                     // size of hash-table
    double A = 0.618033;              // arbitrary constant - choosed from golden section
    int hash = n * fmod(key * A, 1);  // multiplicative method of hashing

    return hash;
}

MyHashMap *myHashMapCreate() {
    // root of hash-table
    MyHashMap *obj = malloc(SIZE * sizeof(MyHashMap));

    for (int i = 0; i < SIZE; i++) {
        // buckets of hash-table
        obj[i].key = -1;
        obj[i].value = -1;
        obj[i].next = NULL;
    }

    return obj;
}

void myHashMapFree(MyHashMap *obj) {
    for (int i = 0; i < SIZE; i++) {
        MyHashMap *current = obj[i].next;

        while (current != NULL) {
            // deleting elements of hash-table
            MyHashMap *for_delete = current;
            current = current->next;
            free(for_delete);
        }
    }

    free(obj);  // deleting root of hash-table
}

int myHashMapGet(MyHashMap *obj, int key) {
    int result = -1;

    int hash = get_hash(key);

    if (obj[hash].value != -1) {
        // go throught elements in relevant table
        MyHashMap *current = obj + hash;

        while (1) {
            if (current == NULL || current->key == key) break;
            current = current->next;
        }
        if (current != NULL) result = current->value;
    }

    return result;
}

void myHashMapPut(MyHashMap *obj, int key, int value) {
    // if element is exist in hash-table - reset value
    if (myHashMapGet(obj, key) != -1) {
        int hash = get_hash(key);

        MyHashMap *current = (obj + hash);
        while (current->key != key) current = current->next;
        current->value = value;

        return;
    }

    int hash = get_hash(key);

    if (obj[hash].value == -1) {
        // if bucket is free, then just set element
        obj[hash].key = key;
        obj[hash].value = value;
    } else {
        // else go to end of bucket
        MyHashMap *current = (obj + hash);
        while (current->next != NULL) current = current->next;
        // and add new element
        MyHashMap *new_node = malloc(SIZE * sizeof(MyHashMap));
        new_node->key = key;
        new_node->value = value;
        new_node->next = NULL;

        current->next = new_node;
    }
}

void myHashMapRemove(MyHashMap *obj, int key) {
    int hash = get_hash(key);

    if (obj[hash].value != -1) {  // if bucket not empty
        // if need remove first element in bucket
        if (obj[hash].key == key) {
            MyHashMap *for_delete = obj[hash].next;

            if (for_delete != NULL) {
                obj[hash].key = for_delete->key;
                obj[hash].value = for_delete->value;
                obj[hash].next = for_delete->next;
                free(for_delete);
            } else {
                obj[hash].key = -1;
                obj[hash].value = -1;
                obj[hash].next = NULL;
            }
        } else {
            // if need remove second or farther element
            MyHashMap *for_delete = obj[hash].next;
            MyHashMap *prev = obj + hash;
            while (1) {  // search element
                if (for_delete == NULL || for_delete->key == key) break;
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

void hash_print(MyHashMap *root) {
    printf("[ ");
    for (int i = 0; i < SIZE; i++) {
        MyHashMap *current = root + i;
        while (current != NULL) {
            if (current->value != -1) printf("[%d, %d] ", current->key, current->value);
            current = current->next;
        }
    }
    printf("]\n");
}