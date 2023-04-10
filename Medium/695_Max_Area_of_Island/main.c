#include <stdio.h>
#include <stdlib.h>

typedef struct point {
    int i, j;
} point;

typedef struct list_node {
    point p;
    struct list_node* next;
} list_node;

void list_push(list_node** head, point p);
void list_pop(list_node** head, point* p);
int** matrix_new(int rows, int cols);
void matrix_delete(int** matrix, int rows);
int area_get(int** matrix, int rows, int cols, int r, int c, int** visited);
int maxAreaOfIsland(int** grid, int gridSize, int* gridColSize);

int main(void) {
    int gridSize = 4, gridColSize[] = {5, 5, 5, 5};
    int** grid = matrix_new(gridSize, gridColSize[0]);

    printf("Input:\n");
    int input[4][5] = {{1, 1, 0, 0, 0}, {1, 1, 0, 0, 0}, {0, 0, 0, 1, 1}, {0, 0, 0, 1, 1}};
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[0]; j++) {
            grid[i][j] = input[i][j];
            printf("%d ", input[i][j]);
        }
        printf("\n");
    }

    int max_area = maxAreaOfIsland(grid, gridSize, gridColSize);

    printf("Output: %d", max_area);

    matrix_delete(grid, gridSize);
    return 0;
}

int maxAreaOfIsland(int** grid, int gridSize, int* gridColSize) {
    int** visited = matrix_new(gridSize, gridColSize[0]);
    int max_area = 0;

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[0]; j++) {
            if (grid[i][j] == 1 && !visited[i][j]) {
                int area = area_get(grid, gridSize, gridColSize[0], i, j, visited);
                if (max_area < area) max_area = area;
            }
        }
    }

    matrix_delete(visited, gridSize);
    return max_area;
}

int area_get(int** matrix, int rows, int cols, int r, int c, int** visited) {
    list_node* list = NULL;
    point p = {r, c};
    visited[r][c] = 1;
    list_push(&list, p);

    int area = 0;
    while (list) {
        list_pop(&list, &p);
        int i = p.i, j = p.j;
        area++;

        if (i - 1 >= 0 && matrix[i - 1][j] == 1 && !visited[i - 1][j]) {
            visited[i - 1][j] = 1;
            p.i = i - 1;
            p.j = j;
            list_push(&list, p);
        }
        if (i + 1 < rows && matrix[i + 1][j] == 1 && !visited[i + 1][j]) {
            visited[i + 1][j] = 1;
            p.i = i + 1;
            p.j = j;
            list_push(&list, p);
        }

        if (j - 1 >= 0 && matrix[i][j - 1] == 1 && !visited[i][j - 1]) {
            visited[i][j - 1] = 1;
            p.i = i;
            p.j = j - 1;
            list_push(&list, p);
        }
        if (j + 1 < cols && matrix[i][j + 1] == 1 && !visited[i][j + 1]) {
            visited[i][j + 1] = 1;
            p.i = i;
            p.j = j + 1;
            list_push(&list, p);
        }
    }

    return area;
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

int** matrix_new(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) matrix[i] = (int*)calloc(cols, sizeof(int));
    return matrix;
}
void matrix_delete(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) free(matrix[i]);
    free(matrix);
}
