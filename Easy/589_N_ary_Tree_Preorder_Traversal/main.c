#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
    int size;
    int elements_in_stack;
    struct Node** data;
} stack;

stack* stack_new(int size);
void stack_push(stack* st, struct Node* new_data);
struct Node* stack_pop(stack* st);
void stack_delete(stack** st);
void stack_ptint(stack* st);

typedef struct Node {
    int val;
    int numChildren;
    struct Node** children;
} Node;

int* out_add(int* out, int* size, int* elems_count, int new_elem);
int* preorder(struct Node* root, int* returnSize);
Node* node_add(Node* parent, int new_val);
void node_free(Node* node);

int main(void) {
    Node* root = node_add(NULL, 1);
    node_add(root, 3);
    node_add(root->children[0], 5);
    node_add(root->children[0], 6);
    node_add(root, 2);
    node_add(root, 4);

    int out_size;
    int* out = preorder(root, &out_size);

    printf("Output:[ ");
    for (int i = 0; i < out_size; i++) printf("%d ", out[i]);
    printf("]\n");

    node_free(root);
    if (out != NULL) free(out);
    return 0;
}

int* preorder(struct Node* root, int* returnSize) {
    // stack for temporary storage of nodes
    stack* st = stack_new(50);

    // dinamic array for output
    int out_size = 50;  // start size of array
    int out_count = 0;  // start count of elements
    int* out = (int*)malloc(out_size * sizeof(int));

    // pointer for the passage trought Tree
    struct Node* node = root;

    while (node != NULL) {
        // add current node for output
        out = out_add(out, &out_size, &out_count, node->val);
        // save all childrens into stack
        for (int i = node->numChildren - 1; i >= 0; i--) stack_push(st, node->children[i]);
        // get node from stack or NULL if stack is empty
        node = stack_pop(st);
    }

    *returnSize = out_count;  // save count of outputing elements
    stack_delete(&st);        // delete stack
    return out;
}

// for dinamic adding to outputing array
int* out_add(int* out, int* size, int* elems_count, int new_elem) {
    // when dont have place to new element
    if (*size < *elems_count + 1) {
        if (*size < 500)  // when array is small
            *size *= 2;   // to double size
        else              // else add 1/3 from current size
            *size += *size / 3 + 1;
        out = (int*)realloc(out, *size * sizeof(int));
    }
    // add element and increment counter
    out[(*elems_count)++] = new_elem;
    // its important when we reallocating memory
    return out;
}

stack* stack_new(int size) {
    stack* new = (stack*)malloc(sizeof(stack));

    if (new != NULL) {
        new->size = size;
        new->elements_in_stack = 0;
        new->data = (struct Node**)malloc(sizeof(struct Node*) * size);
    }
    return new;
}

void stack_push(stack* st, struct Node* new_data) {
    if (st->elements_in_stack == st->size) {
        if (st->size < 500)
            st->size *= 2;
        else
            st->size += st->size / 3 + 1;
        st->data = (struct Node**)realloc(st->data, sizeof(struct Node*) * st->size);
    }
    st->data[st->elements_in_stack++] = new_data;
}

struct Node* stack_pop(stack* st) {
    struct Node* elem = NULL;
    if (st->elements_in_stack > 0) elem = st->data[--(st->elements_in_stack)];
    return elem;
}

void stack_delete(stack** st) {
    free((*st)->data);
    free(*st);
    st = NULL;
}

void stack_ptint(stack* st) {
    printf("stack: [ ");
    for (int i = 0; i < st->size; i++) printf("%d ", st->data[i]->val);
    printf("]\n");
}

Node* node_add(Node* parent, int new_val) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->val = new_val;
    new_node->numChildren = 0;
    new_node->children = NULL;

    if (parent != NULL) {
        parent->children = (Node**)realloc(parent->children, sizeof(Node*) * (parent->numChildren + 1));
        parent->children[parent->numChildren++] = new_node;
    }

    return new_node;
}

void node_free(Node* node) {
    for (int i = 0; i < node->numChildren; i++) {
        node_free(node->children[i]);
    }

    free(node->children);
    free(node);
}