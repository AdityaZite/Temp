#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size, front, rear;
    int *a;
}queue;

int isEmpty(queue *);
int isFull(queue *);
void resize(queue *);
void enqueue(queue *, int);
int dequeue(queue *);
void bfs(queue *, int **, int, int, int);

int isEmpty(queue *q) {
    return q->front == q->rear;
}

int isFull(queue *q) {
    return q->rear == q->size - 1;
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

void bfs(queue *q, int **adj, int start, int goal, int n) {
    int *visited = (int *)calloc(n, sizeof(int));

    visited[start] = 1;
    enqueue(q, start);

    while(!isEmpty(q)) {
        int node = dequeue(q);
        printf("%d ", node);
        if(node == goal) {
            break;
        }
        for(int j = 0;j < n;j++) {
            if(adj[node][j] == 1 && visited[j] == 0) {
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
    q->a = (int *)malloc(q->size * sizeof(int));

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

    bfs(q, adj, start, goal, n);    
}