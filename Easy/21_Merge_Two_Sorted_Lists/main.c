#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2);
void list_print(char* message, struct ListNode* list);

int main(void) {
    struct ListNode* l1_root = malloc(sizeof(struct ListNode));
    struct ListNode* l1 = l1_root;
    l1->val = 1;
    l1->next = malloc(sizeof(struct ListNode));
    l1 = l1->next;
    l1->val = 2;
    l1->next = malloc(sizeof(struct ListNode));
    l1 = l1->next;
    l1->val = 4;
    l1->next = NULL;

    list_print("list 1", l1_root);

    struct ListNode* l2_root = malloc(sizeof(struct ListNode));
    struct ListNode* l2 = l2_root;
    l2->val = 1;
    l2->next = malloc(sizeof(struct ListNode));
    l2 = l2->next;
    l2->val = 3;
    l2->next = NULL;

    list_print("list 2", l2_root);

    struct ListNode* merged = mergeTwoLists(l1_root, l2_root);

    list_print("merged", merged);

    return 0;
}

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    // pointer on root of merged list
    struct ListNode* root = NULL;

    // set root of merged list
    if (list1 != NULL && list2 != NULL) {
        if (list1->val < list2->val) {
            root = list1;
            list1 = list1->next;
        } else {
            root = list2;
            list2 = list2->next;
        }
    } else if (list1 != NULL) {
        root = list1;
        list1 = list1->next;
    } else if (list2 != NULL) {
        root = list2;
        list2 = list2->next;
    }

    struct ListNode* current = root;
    if (root != NULL) current->next = NULL;

    // set next elements of merged list
    while (list1 != NULL && list2 != NULL) {
        if (list1->val < list2->val) {
            current->next = list1;
            current = current->next;

            list1 = list1->next;
        } else {
            current->next = list2;
            current = current->next;

            list2 = list2->next;
        }
    }

    // if elements remained in 1 or 2 list
    while (list1 != NULL) {
        current->next = list1;
        current = current->next;

        list1 = list1->next;
    }
    while (list2 != NULL) {
        current->next = list2;
        current = current->next;

        list2 = list2->next;
    }

    return root;
}

void list_print(char* message, struct ListNode* list) {
    printf("%s: [ ", message);
    while (list != NULL) {
        printf("%d ", list->val);
        list = list->next;
    }
    printf("]\n");
}