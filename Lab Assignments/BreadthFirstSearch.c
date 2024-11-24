#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size, front, rear;
    int *a;
}queue;

int isEmpty(queue *q) {
    return (q->front == q->rear);
}

int isFull(queue *q) {
    return (q->rear == q->size - 1);
}

void resize(queue *q) {
    q->size *= 2;
    q->a = (int *)realloc(q->a, q->size);
}
void enqueue(queue *q, int data) {
    if(isFull(q)) {
        resize(q);
    }
    q->a[++q->rear] = data;
}

int dequeue(queue *q) {
    return q->a[++q->front];
}

void bfs(int **adj, queue *q, int s, int n) {
    int *visited = (int *)calloc(n, sizeof(int));
    printf("%d ", s);
    visited[s] = 1;
    enqueue(q, s);

    while(!isEmpty(q)) {
        int node = dequeue(q);
        for(int j = 0;j < n;j++) {
            if(adj[node][j] == 1 && visited[j] == 0) {
                printf("%d ", j);
                visited[j] = 1;
                enqueue(q, j);
            }
        }
    }
    free(visited);
}

int main() {
    queue *q = (queue *)malloc(sizeof(queue));
    q->size = 10;
    q->front = q->rear = -1;
    q->a = (int *)malloc(sizeof(int) * q->size);

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

    int s;
    printf("Enter the starting node:");
    scanf("%d", &s);
    bfs(adj, q, s, n);
    free(q->a);
    free(q);
    for (int i = 0; i < n; i++)
    {
        free(adj[i]);
    }
    free(adj);
}