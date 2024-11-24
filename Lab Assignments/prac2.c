#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size, top;
    int *a;
}stack;

int isEmpty(stack *);
int isFull(stack *);
void resize(stack *);
void push(stack *, int);
int pop(stack *);
void dfs(stack *, int **, int, int, int);

int isEmpty(stack *s) {
    return s->top == -1;
}

int isFull(stack *s) {
    return s->top == s->size - 1;
}

void resize(stack *s) {
    s->size *= 2;
    s->a = (int *)realloc(s->a, sizeof(s->size));
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

void dfs(stack *s, int **adj, int start, int goal, int n) {
    int *visited = (int *)calloc(n, sizeof(int));

    visited[start] = 1;
    push(s, start);

    while(!isEmpty(s)) {
        int node = pop(s);
        printf("%d ", node);
        if(node == goal) {
            break;
        }
        for(int j = n - 1;j > -1;j--) {
            if(adj[node][j] == 1 && visited[j] == 0) {
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
    s->a = (int *)malloc(s->size * sizeof(int));

    int n;
    printf("Enter the number of nodes in the graph:");
    scanf("%d", &n);

    int **adj = (int **)malloc(n * sizeof(int *));

    for(int i = 0;i < n;i++) {
        adj[i] = (int *)calloc(n, sizeof(int));
    }

    int edges;
    printf("Enter the number of edges in the graph:");
    scanf("%d", &edges);

    int src, dest;
    while(edges) {
        printf("Enter source node and destination node for the edge:");
        scanf("%d%d", &src, &dest);

        adj[src][dest] = adj[dest][src] = 1;
        edges--;
    }

    int start;
    printf("Enter the starting node:");
    scanf("%d", &start);

    int goal;
    printf("Enter the goal node:");
    scanf("%d", &goal);

    dfs(s, adj, start, goal, n);
}