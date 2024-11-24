#include<stdio.h>
#include<stdlib.h>

#define MAX_VAL 100

struct Graph{
    int no_vertex;
    int m[MAX_VAL][MAX_VAL];
};

struct Graph* createGraph(int size){
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->no_vertex = size;
    graph->m[size][size];
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            graph->m[i][j] = 0;
        }
    }
    return graph;
}

void addEdge(struct Graph* graph,int src,int dest){
    graph->m[src][dest] = 1;
}

void sort_queue(int* queue,int front,int rare,int hvalue[]){
   int min = hvalue[front];
   int index = front;
    for(int i=front;i<rare;i++){
        if(min>hvalue[queue[i]]){
            min = hvalue[queue[i]];
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

void bestfs(struct Graph* graph,int src,int dest,int hvalue[]){ 
    int n = graph->no_vertex;

    int* queue = (int*)malloc(sizeof(int)*100);
    int front = 0,rare=0;

    int* closeList = (int*)malloc(sizeof(int)*100);
    int c = 0;

    int visited[n];
    for(int i=0;i<n;i++){
        visited[i] = 0;
    }

    int parent[n];
    for(int i=0;i<n;i++){
        parent[i] = -1;
    }

    queue[rare++] = src;
    visited[src] = 1;
    parent[src] = -1;    

    while(front<rare){
        int curr = queue[front++];
        printf("%d ",curr);
        closeList[c++] = curr;

        for(int i=0;i<n;i++){
            if(graph->m[curr][i] == 1 && visited[i] == 0){
                queue[rare++] = i;
                parent[i] = curr;
                visited[i] = 1;
            }
        }
        if(curr == dest) break;
        sort_queue(queue,front,rare,hvalue);
    }
}

int main(){

    int n;
    int ele;
    int edge;

    printf("\nEnter total Vertex : ");
    scanf("%d",&n);

    struct Graph* graph = createGraph(n);

    printf("\nHValue : ");
    int hvalue[n];
    for(int i=0;i<n;i++){
        scanf("%d",&ele);
        hvalue[i] = ele;
    }

    // int hvalue[] = {40,32,25,35,19,17,10,0};

    // addEdge(graph,0,1);
    // addEdge(graph,0,2);
    // addEdge(graph,0,3);

    // addEdge(graph,1,0);
    // addEdge(graph,1,4);

    // addEdge(graph,2,0);
    // addEdge(graph,2,3);
    // addEdge(graph,2,4);
    // addEdge(graph,2,5);

    // addEdge(graph,3,0);
    // addEdge(graph,3,2);
    // addEdge(graph,3,5);

    // addEdge(graph,4,1);
    // addEdge(graph,4,2);
    // addEdge(graph,4,6);

    // addEdge(graph,5,2);
    // addEdge(graph,5,3);
    // addEdge(graph,5,7);

    // addEdge(graph,6,4);
    // addEdge(graph,6,7);

    // addEdge(graph,7,5);
    // addEdge(graph,7,6);

    printf("\nEnter edges :\n");
    
    for(int i=0;i<n;i++){
        printf("\nEnter no. of edges for vertex %d : ",i);
        scanf("%d",&edge);
        printf("\nEnter vertex connected : ");
        for(int j=0;j<edge;j++){
            scanf("%d",&ele);
            addEdge(graph,i,ele);
        }
    }
    
    printf("\nOptimal Path : ");
    bestfs(graph,0,7,hvalue);
}