#include <stdio.h>
#include <stdlib.h>

#define N 3
#define M 3

typedef struct point {
    int i;
    int j;
} point;

typedef struct list_node {
    point p;
    struct list_node* next;
} list_node;

void list_push(list_node** head, point p);
void list_pop(list_node** head, point* p);

int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc, int color, int* returnSize,
                int** returnColumnSizes);
int** matrix_create(int input[N][M]);
void matrix_delete(int** matrix, int rows);
void matrix_printf(int** matrixm, int n, int m, char* message);

int main(void) {
    // input
    int imageSize = N;
    int imageColSize[imageSize];
    for (int i = 0; i < imageSize; i++) imageColSize[i] = M;
    int input[N][M] = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
    int sr = 1, sc = 0, color = 2;

    int** image = matrix_create(input);
    matrix_printf(image, imageSize, *imageColSize, "Input");

    // outut
    int returnSize, *returnColumnSizes = NULL;
    int** out = floodFill(image, imageSize, imageColSize, sr, sc, color, &returnSize, &returnColumnSizes);

    matrix_printf(out, returnSize, *returnColumnSizes, "Out");

    matrix_delete(image, N);
    matrix_delete(out, N);
    free(returnColumnSizes);
    return 0;
}

int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc, int color, int* returnSize,
                int** returnColumnSizes) {
    *returnSize = imageSize;
    int** out = (int**)malloc(*returnSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(imageSize * sizeof(int));
    for (int i = 0; i < *returnSize; i++) {
        *(*returnColumnSizes + i) = imageColSize[0];
        out[i] = (int*)malloc(imageColSize[0] * sizeof(int));
    }
    for (int i = 0; i < imageSize; i++)
        for (int j = 0; j < imageColSize[0]; j++) out[i][j] = image[i][j];

    int* visited = (int*)calloc(imageSize * imageColSize[0], sizeof(int));

    list_node* list = NULL;
    point p = {sr, sc};
    int prev_color = image[p.i][p.j];
    list_push(&list, p);

    while (list) {
        list_pop(&list, &p);
        out[p.i][p.j] = color;
        int index_current = p.i * imageColSize[0] + p.j;
        int i = p.i, j = p.j;

        int next_i = i - 1, next_j = j;
        int index_next = next_i * imageColSize[0] + next_j;
        if (next_i >= 0 && image[next_i][next_j] == prev_color && !visited[index_next]) {
            p.i = next_i;
            p.j = next_j;
            list_push(&list, p);
        }

        next_i = i + 1, next_j = j;
        index_next = next_i * imageColSize[0] + next_j;
        if (next_i < imageSize && image[next_i][next_j] == prev_color && !visited[index_next]) {
            p.i = next_i;
            p.j = next_j;
            list_push(&list, p);
        }

        next_i = i, next_j = j - 1;
        index_next = next_i * imageColSize[0] + next_j;
        if (next_j >= 0 && image[next_i][next_j] == prev_color && !visited[index_next]) {
            p.i = next_i;
            p.j = next_j;
            list_push(&list, p);
        }

        next_i = i, next_j = j + 1;
        index_next = next_i * imageColSize[0] + next_j;
        if (next_j < imageColSize[0] && image[next_i][next_j] == prev_color && !visited[index_next]) {
            p.i = next_i;
            p.j = next_j;
            list_push(&list, p);
        }

        visited[index_current] = 1;
    }
    free(visited);
    return out;
}

void list_push(list_node** head, point p) {
    list_node* new_node = (list_node*)malloc(sizeof(list_node));
    new_node->p = p;
    new_node->next = *head;

    *head = new_node;
}
void list_pop(list_node** head, point* p) {
    if (*head) {
        *p = (*head)->p;
        list_node* new_head = (*head)->next;
        free(*head);
        *head = new_head;
    } else
        p->i = p->j = -1;
}

int** matrix_create(int input[N][M]) {
    int** image = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) image[i] = (int*)malloc(M * sizeof(int));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) image[i][j] = input[i][j];
    return image;
}
void matrix_delete(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) free(matrix[i]);
    free(matrix);
}
void matrix_printf(int** matrixm, int n, int m, char* message) {
    printf("%s:\n", message);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) printf("%d ", matrixm[i][j]);
        printf("\n");
    }
}