#include <iostream>
#include <queue>
#include <vector>
#include <omp.h>

using namespace std;

// Structure to represent a graph node
struct Node {
    int id;
    vector<int> neighbors;
};

// Function to perform BFS traversal
void bfs(vector<Node>& graph, int startNode) {
    int numNodes = graph.size();
    vector<bool> visited(numNodes, false);
    queue<int> q;

    // Mark the start node as visited and enqueue it
    visited[startNode] = true;
    q.push(startNode);

    // Perform BFS
    while (!q.empty()) {
        int currNode = q.front();
        q.pop();
        cout << "Visited node: " << currNode << endl;

        // Process neighbors of the current node
        #pragma omp parallel for
        for (int i = 0; i < graph[currNode].neighbors.size(); ++i) {
            int neighbor = graph[currNode].neighbors[i];
            if (!visited[neighbor]) {
                // Mark the neighbor as visited and enqueue it
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    // Example graph representation
    vector<Node> graph(7);
    graph[0].id = 0;
    graph[0].neighbors = {1, 2};

    graph[1].id = 1;
    graph[1].neighbors = {0, 3, 4};

    graph[2].id = 2;
    graph[2].neighbors = {0, 5, 6};

    graph[3].id = 3;
    graph[3].neighbors = {1};

    graph[4].id = 4;
    graph[4].neighbors = {1};

    graph[5].id = 5;
    graph[5].neighbors = {2};

    graph[6].id = 6;
    graph[6].neighbors = {2};

    // Perform BFS traversal with parallelization
    bfs(graph, 0);

    return 0;
}
