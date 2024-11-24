#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size, top;
    int *a;
}stack;

int isEmpty(stack *s) {
    return (s->top == -1);
}

int isFull(stack *s) {
    return (s->top == s->size - 1);
}

void resize(stack *s) {
    s->size *= 2;
    s->a = (int *)realloc(s->a, s->size);
}
void push(stack *s, int data) {
    if(isFull(s)) {
        resize(s);
    }
    s->a[++s->top] = data;
}

int pop(stack *s) {
    return s->a[s->top--];
}

void bfs(int **adj, stack *s, int start, int n) {
    int *visited = (int *)calloc(n, sizeof(int));
    printf("%d ", start);
    visited[start] = 1;
    push(s, start);

    while(!isEmpty(s)) {
        int node = pop(s);
        for(int j = 0;j < n;j++) {
            if(adj[node][j] == 1 && visited[j] == 0) {
                printf("%d ", j);
                visited[j] = 1;
                push(s, j);
            }
        }
    }
    free(visited);
}

int main() {
    stack *s = (stack *)malloc(sizeof(stack));
    s->size = 10;
    s->top = -1;
    s->a = (int *)malloc(sizeof(int) * s->size);

    int n;

    printf("Enter the number of nodes in the graph:");
    scanf("%d", &n);

    int **adj = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
    {
        adj[i] = (int *)malloc(sizeof(int) * n);
    }
    
    printf("Enter the adjacency matrix representation of the graph:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    int start;
    printf("Enter the starting node:");
    scanf("%d", &start);
    bfs(adj, s, start, n);
    free(s->a);
    free(s);
    for (int i = 0; i < n; i++)
    {
        free(adj[i]);
    }
    free(adj);
}