implements graphs with its traingle found oparation
#include <stdio.h>

// Define a struct to represent a node in the graph
struct Node {
    int nodeid;
    int adjcount;
    int cost[10];
    int costs[10];
};

// Function prototypes
int chacktringle(struct Node* p, int count);
int addNode(struct Node* p, int nid, int count);
void addAdjacent(struct Node* p, int nid1, int nid2, int cost, int count);
int added(int* list, int lcount, int nid);
void findpath(struct Node* p, int count, int start, int end, int* list, int* clist, int lcount);

int main() {
    struct Node nodes[50]; // Array to hold nodes
    int nodecount = 0; // Counter for number of nodes
    int n1 = 0, n2 = 0, c = 0; // Variables for input
    
    // Loop to input nodes and edges
    while (1) {
        printf("Enter n1, n2, cost (or -9 to exit): ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c == -9) {
            break;
        }
        nodecount = addNode(&nodes[0], n1, nodecount);
        nodecount = addNode(&nodes[0], n2, nodecount);
        addAdjacent(&nodes[0], n1, n2, c, nodecount);
        addAdjacent(&nodes[0], n2, n1, c, nodecount);
    }

    // Input start and end nodes
    int start, end;
    printf("Enter start and end node: ");
    scanf("%d %d", &start, &end);
    
    // Array to store path and costs
    int list[50], clist[50], lcount = 0;
    list[0] = start; clist[0] = 0; lcount = 1;

    // Find paths from start to end
    findpath(nodes, nodecount, start, end, list, clist, lcount);
    
    // Output the number of triangles in the graph
    int triangleCount = chacktringle(nodes, nodecount);
    printf("Number of triangles: %d\n", triangleCount);
    
    return 0;
}

// Function to check for triangles in the graph
int chacktringle(struct Node* p, int count) {
    int tcount = 0;
    
    // Loop through all combinations of three nodes
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            for (int k = j + 1; k < count; k++) {
                int node1 = p[i].nodeid;
                int node2 = p[j].nodeid;
                int node3 = p[k].nodeid;
                int e1 = 0, e2 = 0, e3 = 0;

                // Check if each pair of nodes shares an edge
                for (int x = 0; x < p[i].adjcount; x++) {
                    if ((p[i].cost[x] == node2) || (p[i].cost[x] == node3)) {
                        e1++;
                    }
                }
                for (int y = 0; y < p[j].adjcount; y++) {
                    if ((p[j].cost[y] == node1) || (p[j].cost[y] == node3)) {
                        e2++;
                    }
                }
                for (int z = 0; z < p[k].adjcount; z++) {
                    if ((p[k].cost[z] == node1) || (p[k].cost[z] == node2)) {
                        e3++;
                    }
                }
                // If all three nodes form a triangle, increment the triangle count
                if (e1 == 2 && e2 == 2 && e3 == 2) {
                    printf("Triangle nodes: %d %d %d\n", node1, node2, node3);
                    tcount++;
                }
            }
        }
    }
    return tcount;
}

// Function to add a node to the graph
int addNode(struct Node* p, int nid, int count) {
    int i = 0, ncount = count;
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid) { break; }
    }
    if (i == count) {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    return ncount;
}

// Function to add an adjacent node and its cost to a given node
void addAdjacent(struct Node* p, int nid1, int nid2, int cost, int count) {
    int i = 0, index;
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid1) {
            int c = p[i].adjcount;
            p[i].cost[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount = c + 1;
            break;
        }
    }
}

// Function to check if a node is already added to the list
int added(int* list, int lcount, int nid) {
    int i = 0;
    for (i = 0; i < lcount; i++) {
        if (list[i] == nid) { return 1; }
    }
    return 0;
}

// Function to find all possible paths from start to end node
void findpath(struct Node* p, int count, int start, int end, int* list, int* clist, int lcount) {
    int index = 0, i = 0, j = 0, k = 0;

    // Check if list contains the end node
    if (list[lcount - 1] == end) {
        int tcost = 0;
        printf("\nPath: ");
        for (i = 0; i < lcount; i++) {
            printf("%d ", list[i]);
            tcost += clist[i];
        }
        printf(" Cost = %d\n", tcost);
        return;
    }

    // Find the index of the starting node
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == start) { index = i; break; }
    }

    // Iterate through adjacent nodes and recursively find paths
    for (i = 0; i < p[index].adjcount; i++) {
        int a = added(list, lcount, p[index].cost[i]);
        if (a == 0) {
            list[lcount] = p[index].cost[i];
            clist[lcount] = p[index].costs[i];
            lcount++;
            findpath(p, count, p[index].cost[i], end, list, clist, lcount);
            lcount--;
        }
    }
}
