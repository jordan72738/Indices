#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

const int INF = INT_MAX; // Infinity to represent unreachable nodes

// Function to find the vertex with the minimum distance value
int minDistance(vector<int>& dist, vector<bool>& visited, int V) {
    int minDist = INF;
    int minVertex = -1;

    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= minDist) {
            minDist = dist[v];
            minVertex = v;
        }
    }

    return minVertex;
}

// Function to print the shortest path from source to destination
void printPath(vector<int>& parent, int dest) {
    if (parent[dest] == -1)
        return;

    printPath(parent, parent[dest]);
    cout << " -> " << dest;
}

// Function to implement Dijkstra's Algorithm to find the shortest path
void dijkstra(vector<vector<int>>& graph, int src, int dest, int V) {
    vector<int> dist(V, INF);   // To store the shortest distances from source to all vertices
    vector<bool> visited(V, false); // To keep track of visited vertices
    vector<int> parent(V, -1); // To store the parent vertices for constructing the path

    dist[src] = 0; // Distance from source to itself is 0

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF && (dist[u] + graph[u][v] < dist[v])) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    cout << "Shortest path from " << src << " to " << dest << " with cost " << dist[dest] << " is:" << endl;
    cout << src;
    printPath(parent, dest);
    cout << endl;
}

int main() {
    int V; // Number of vertices
    cout << "Enter the number of vertices: ";
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V, 0)); // Adjacency matrix

    // Input graph data
    cout << "Enter the adjacency matrix for the graph (0 for no edge, weight for edge):" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> graph[i][j];
        }
    }

    int src, dest;
    cout << "Enter the starting node: ";
    cin >> src;
    cout << "Enter the ending node: ";
    cin >> dest;

    dijkstra(graph, src, dest, V);

    return 0;
}
