
#include <stdio.h>
#include<stdlib.h>

// Define a struct to represent a node in the graph
struct Node {
    int nodeId;
    int adjCount;
    int adjacentNodes[10];
    int edgeCosts[10];
};

// Function prototypes
int checkTriangle(struct Node* nodes, int nodeCount);
int addNode(struct Node* nodes, int nodeId, int nodeCount);
void addAdjacent(struct Node* nodes, int nodeId1, int nodeId2, int cost, int nodeCount);
int isAdded(int* list, int listCount, int nodeId);
void findPath(struct Node* nodes, int nodeCount, int start, int end, int* pathList, int* costList, int pathCount);

int main() {
    struct Node nodes[50]; // Array to hold nodes
    int nodeCount = 0; // Counter for number of nodes
    int node1 = 0, node2 = 0, cost = 0; // Variables for input

    // Loop to input nodes and edges
    while (1) {
        printf("Enter node1, node2, cost (or -9 to exit): ");
        scanf("%d %d %d", &node1, &node2, &cost);
        if (node1 == -9 || node2 == -9 || cost == -9) {
            break;
        }
        nodeCount = addNode(nodes, node1, nodeCount);
        nodeCount = addNode(nodes, node2, nodeCount);
        addAdjacent(nodes, node1, node2, cost, nodeCount);
        addAdjacent(nodes, node2, node1, cost, nodeCount);
    }

    // Input start and end nodes
    int start, end;
    printf("Enter start and end node: ");
    scanf("%d %d", &start, &end);

    // Array to store path and costs
    int pathList[50], costList[50], pathCount = 0;
    pathList[0] = start; costList[0] = 0; pathCount = 1;

    // Find paths from start to end
    findPath(nodes, nodeCount, start, end, pathList, costList, pathCount);

    // Output the number of triangles in the graph
    int triangleCount = checkTriangle(nodes, nodeCount);
    printf("Number of triangles: %d\n", triangleCount);

    return 0;
}

// Function to check for triangles in the graph
int checkTriangle(struct Node* nodes, int nodeCount) {
    int triangleCount = 0;

    // Loop through all combinations of three nodes
    for (int i = 0; i < nodeCount; i++) {
        for (int j = i + 1; j < nodeCount; j++) {
            for (int k = j + 1; k < nodeCount; k++) {
                int node1 = nodes[i].nodeId;
                int node2 = nodes[j].nodeId;
                int node3 = nodes[k].nodeId;
                int edge1 = 0, edge2 = 0, edge3 = 0;

                // Check if each pair of nodes shares an edge
                for (int x = 0; x < nodes[i].adjCount; x++) {
                    if ((nodes[i].adjacentNodes[x] == node2) || (nodes[i].adjacentNodes[x] == node3)) {
                        edge1++;
                    }
                }
                for (int y = 0; y < nodes[j].adjCount; y++) {
                    if ((nodes[j].adjacentNodes[y] == node1) || (nodes[j].adjacentNodes[y] == node3)) {
                        edge2++;
                    }
                }
                for (int z = 0; z < nodes[k].adjCount; z++) {
                    if ((nodes[k].adjacentNodes[z] == node1) || (nodes[k].adjacentNodes[z] == node2)) {
                        edge3++;
                    }
                }
                // If all three nodes form a triangle, increment the triangle count
                if (edge1 == 2 && edge2 == 2 && edge3 == 2) {
                    printf("Triangle nodes: %d %d %d\n", node1, node2, node3);
                    triangleCount++;
                }
            }
        }
    }
    return triangleCount;
}

// Function to add a node to the graph
int addNode(struct Node* nodes, int nodeId, int nodeCount) {
    int i = 0, newNodeCount = nodeCount;
    for (i = 0; i < nodeCount; i++) {
        if (nodes[i].nodeId == nodeId) { break; }
    }
    if (i == nodeCount) {
        nodes[i].nodeId = nodeId;
        nodes[i].adjCount = 0;
        newNodeCount++;
    }
    return newNodeCount;
}

// Function to add an adjacent node and its cost to a given node
void addAdjacent(struct Node* nodes, int nodeId1, int nodeId2, int cost, int nodeCount) {
    int i = 0, index;
    for (i = 0; i < nodeCount; i++) {
        if (nodes[i].nodeId == nodeId1) {
            int c = nodes[i].adjCount;
            nodes[i].adjacentNodes[c] = nodeId2;
            nodes[i].edgeCosts[c] = cost;
            nodes[i].adjCount = c + 1;
            break;
        }
    }
}

// Function to check if a node is already added to the list
int isAdded(int* list, int listCount, int nodeId) {
    for (int i = 0; i < listCount; i++) {
        if (list[i] == nodeId) { return 1; }
    }
    return 0;
}

// Function to find all possible paths from start to end node
// Function to find all possible paths from start to end node
void findPath(struct Node* nodes, int nodeCount, int start, int end, int* pathList, int* costList, int pathCount) {
    int index = 0;

    // Check if list contains the end node
    if (pathList[pathCount - 1] == end) {
        int totalCost = 0;
        printf("\nPath: ");
        for (int i = 0; i < pathCount; i++) {
            printf("%d ", pathList[i]);
            totalCost += costList[i];
        }
        printf(" Cost = %d\n", totalCost);
        return;
    }

    // Find the index of the starting node
    for (int i = 0; i < nodeCount; i++) {
        if (nodes[i].nodeId == start) { index = i; break; }
    }

    // Iterate through adjacent nodes and recursively find paths
    for (int i = 0; i < nodes[index].adjCount; i++) {
        int added = isAdded(pathList, pathCount, nodes[index].adjacentNodes[i]);
        if (!added) {
            pathList[pathCount] = nodes[index].adjacentNodes[i];
            costList[pathCount] = nodes[index].edgeCosts[i];
            pathCount++;
            findPath(nodes, nodeCount, nodes[index].adjacentNodes[i], end, pathList, costList, pathCount);
            pathCount--;
        }
    }
}
