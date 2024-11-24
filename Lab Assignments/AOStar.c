#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 20  // Maximum number of nodes in the graph

// Structure to represent a node in the graph
struct Node {
    int id;
    int cost;  // Heuristic cost
    bool isAndNode;  // True if AND node, False if OR node
    int children[2];  // Stores the children nodes (for AND-OR structure)
    int numChildren;  // Number of children (can be 1 or 2 for this example)
};

// Function to find the minimum cost path from the given node in the AND-OR graph
int AOStar(int node, struct Node graph[], int n, int solution[]) {
    // If the node is a leaf node, return its cost
    if (graph[node].numChildren == 0) {
        solution[node] = node;  // Add to solution
        return graph[node].cost;
    }

    int minCost = INT_MAX;  // Initialize minimum cost to infinity

    if (graph[node].isAndNode) {
        // AND node: Both children need to be solved, so sum their costs
        int cost1 = AOStar(graph[node].children[0], graph, n, solution);
        int cost2 = AOStar(graph[node].children[1], graph, n, solution);
        minCost = cost1 + cost2 + graph[node].cost;
        solution[node] = node;  // Mark current node as part of the solution
    } else {
        // OR node: Solve the child with the minimum cost
        for (int i = 0; i < graph[node].numChildren; i++) {
            int cost = AOStar(graph[node].children[i], graph, n, solution);
            if (cost < minCost) {
                minCost = cost;
                solution[node] = node;  // Update solution path
            }
        }
    }

    return minCost;
}

int main() {
    // Define an example AND-OR graph
    // Graph has 7 nodes where:
    // Nodes 0, 3, 4 are OR nodes; Nodes 1, 2, 5, 6 are AND nodes
    struct Node graph[MAX] = {
        {0, 0, false, {1, 2}, 2},  // Root node (OR node)
        {1, 1, true, {3, 4}, 2},   // AND node with 2 children (3 and 4)
        {2, 2, true, {5, 6}, 2},   // AND node with 2 children (5 and 6)
        {3, 3, false, {}, 0},      // Leaf node (OR node)
        {4, 4, false, {}, 0},      // Leaf node (OR node)
        {5, 5, false, {}, 0},      // Leaf node (OR node)
        {6, 6, false, {}, 0}       // Leaf node (OR node)
    };

    int solution[MAX] = {0};  // To store the solution path
    int startNode = 0;  // Start from the root node

    // Find the minimum cost solution from the start node
    int result = AOStar(startNode, graph, MAX, solution);

    // Print the solution path
    printf("Optimal Solution Path: \n");
    for (int i = 0; i < MAX; i++) {
        if (solution[i] != 0) {
            printf("Node %d -> ", solution[i]);
        }
    }
    printf("\nTotal Cost: %d\n", result);

    return 0;
}