#include<stdio.h>
#include<stdlib.h>

#define MAX_Val 100

struct Graph{
    int n;
    int m[MAX_Val][MAX_Val];
    int fvalue[MAX_Val];
};

struct Graph* createGraph(int n){
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->n = n;
    graph->m[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            graph->m[i][j] = -1;
        }
    }
    graph->fvalue[n];
    for(int i=0;i<n;i++){
        graph->fvalue[i] = -1;
    }
    return graph;
}

void addEdge(struct Graph* graph,int src,int dest,int cost){
    graph->m[src][dest] = cost;
}

void sort_queue(int* queue,int front,int rare,int fvalue[]){
    int min = fvalue[queue[front]];
    int index = front;

    for(int i=front;i<rare;i++){
        if(fvalue[queue[i]] != -1 && min > fvalue[queue[i]]){
            min = fvalue[queue[i]];
            index = i;
        }
    }
    int temp = queue[index];
    queue[index] = queue[front];
    queue[front] = temp;
}

void print(int* queue,int front,int rare){
    for(int i=front;i<rare;i++){
        printf("%d ",queue[i]);
    }
    printf("\n");
}

void astar(struct Graph* graph,int src,int dest,int hvalue[]){

    int n = graph->n;
    int* queue = (int*)malloc(sizeof(int)*100);
    int front = 0,rare=0;

    int visited[n];
    for(int i=0;i<n;i++){
        visited[i] = 0;
    }

    int parent[n];
    for(int i=0;i<n;i++){
        parent[i] = -1;
    }

    int dist[n];
    for(int i=0;i<n;i++){
        dist[i] = 999;
    }

    queue[rare++] = src;
    visited[src] = 1;
    parent[src] = -1;
    dist[src] = 0;

    while(front<rare){
        int curr = queue[front++];
        printf("%d ",curr);
        visited[curr] = 1;
     
        for(int i=0;i<n;i++){
            if(graph->m[curr][i] != -1 && visited[i] == 0){
                int dist_value = dist[curr] + graph->m[curr][i];
                if(dist[i] >= dist_value){
                    dist[i] = dist_value;
                    parent[i] = curr;
                }
                queue[rare++] = i;
                visited[i] = 1;
                graph->fvalue[i] = hvalue[i] + dist[i];
            }
        }

        for(int i=0;i<n;i++){
            if(i!=curr){
                visited[i] =0;
            }
        }
    
        if(curr == dest) break;
        sort_queue(queue,front,rare,graph->fvalue);
    }
}       

int main(){
    
    int n,ele,edge,cost,src,dest;

    n=6;
    struct Graph* graph = createGraph(n);
    int hvalue[] = {5,3,2,4,6,0};

    addEdge(graph,0,1,1);
    addEdge(graph,0,5,10);

    addEdge(graph,1,0,1);
    addEdge(graph,1,2,1);
    addEdge(graph,1,3,2);

    addEdge(graph,2,1,1);
    addEdge(graph,2,4,3);
    addEdge(graph,2,5,4);

    addEdge(graph,3,1,2);
    addEdge(graph,3,4,5);

    addEdge(graph,4,2,3);
    addEdge(graph,4,3,5);
    addEdge(graph,4,5,2);

    addEdge(graph,5,0,10);
    addEdge(graph,5,2,4);
    addEdge(graph,5,4,2);

    src = 0;dest = 5;

    // printf("\nEnter size : ");
    // scanf("%d",&n);

    // struct Graph* graph = createGraph(n);
    // int hvalue[n];
    // printf("\nBuild Graph\n");
    // for(int i=0;i<n;i++){
    //     printf("\nEnter total Edges for vertex %d : ",i);
    //     scanf("%d",&edge);
    //     printf("\nEnter connected vertex and cost\n");
    //     for(int j=0;j<edge;j++){
    //         printf("\nvertex : ");
    //         scanf("%d",&ele);
    //         printf("\ncost : ");
    //         scanf("%d",&cost);
    //         addEdge(graph,i,ele,cost);
    //     }
    //     printf("\n");
    // }
    
    // printf("\nEnter hvalues : ");
    // for(int i=0;i<n;i++){
    //     scanf("%d",&ele);
    //     hvalue[i] = ele;
    // }

    // printf("\nPath : ");
    astar(graph,src,dest,hvalue);
}