#include<stdio.h>
#include<stdlib.h>
#define MAX_VAL 100

struct Graph{
    int n;
    int m[MAX_VAL][MAX_VAL];
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
    return graph;
}

void addEdge(struct Graph* graph,int src,int dest){
    graph->m[src][dest] = 1;
}

void graphColoring(struct Graph* graph,int m){

    int n = graph->n;
    int* queue = (int*)malloc(sizeof(int)*100);
    int front=0,rare=0;

    int colored[n];
    for(int i=0;i<n;i++){
        colored[i] = -1;
    }

    int visited[n];
    for(int i=0;i<n;i++){
        visited[i] = 0;
    }

    int ncolor = m+1;
    int color[ncolor];
    for(int i=0;i<ncolor;i++){
        color[i] = 0;
    }

    queue[rare++] = 0;
    visited[0] = 1;
   
    while(front<rare){
        int curr = queue[front++];

        int flag = -1;
        // checking neighbours color
        for(int i=0;i<n;i++){
            if(graph->m[curr][i] == 1 && colored[i] != -1){
                color[colored[i]] = 1;
            }
        }
    
        // identify ideal color
        for(int i=1;i<ncolor;i++){
            if(color[i] == 0){
                flag = i;
                break;
            }
        }
        // if any color is ideal then assign to curr element otherwise no solution.
        if(flag != -1){
            colored[curr] = flag;
        }else{
            printf("\nSolution not exist!!!!");
            return;
        }
        
        // insert all neighbours
        for(int i=0;i<n;i++){
            if(graph->m[curr][i] == 1 && visited[i] == 0){
                queue[rare++] = i;
                visited[i] = 1;
            }
        }

        // free all color 
        for(int i=1;i<ncolor;i++){
            color[i] = 0;
        }
    }

    // print solution
    printf("\nSolution Exist : ");
    for(int i=0;i<n;i++){
        printf("%d ",colored[i]);
    }
}

int main(){

    int n=6;
    struct Graph* graph = createGraph(n);
    int hvalue[] = {5,3,2,4,6,0};

    addEdge(graph,0,1);
    addEdge(graph,0,5);

    addEdge(graph,1,0);
    addEdge(graph,1,2);
    addEdge(graph,1,3);

    addEdge(graph,2,1);
    addEdge(graph,2,4);
    addEdge(graph,2,5);

    addEdge(graph,3,1);
    addEdge(graph,3,4);

    addEdge(graph,4,2);
    addEdge(graph,4,3);
    addEdge(graph,4,5);

    addEdge(graph,5,0);
    addEdge(graph,5,2);
    addEdge(graph,5,4);

    graphColoring(graph,3);
}