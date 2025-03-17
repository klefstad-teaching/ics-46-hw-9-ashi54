#include "dijkstras.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

const int UNDEFINED = -1;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.size(); // Get the number of vertices in the graph
    vector<int> distances(numVertices, INF); // Initialize distances to INF
    vector<bool> visited(numVertices, false); // Track visited vertices
    previous.assign(numVertices, UNDEFINED); // Initialize previous vector

    // Min-heap priority queue (pair: {distance, vertex})
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
    
    // Start with the source node
    distances[source] = 0;
    previous[source] = UNDEFINED;
    minHeap.push({0, source});

    // Process nodes in order of shortest distance
    while (!minHeap.empty()) {
        int u = minHeap.top().second; // Extract vertex with smallest distance
        minHeap.pop();

        if (visited[u]) continue; // Skip already visited nodes
        visited[u] = true;

        // Explore all edges from vertex u
        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            // If a shorter path to v is found, update distance and path
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }

    return distances; // Return the shortest distances from the source
}


vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) {
        return path; // No path found
    }

    for (int v = destination; v != UNDEFINED; v = previous[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end()); // Reverse to get correct order
    return path;
}

void print_path(const vector<int>& path, int total_cost) {
    if (path.empty()) {
        cout << "No path found." << endl;
        return;
    }

    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << " (Total Cost: " << total_cost << ")" << endl;
}