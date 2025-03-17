#include "dijkstras.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

const int UNDEFINED = -1;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.size();
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    previous.assign(numVertices, -1);  // -1 means "no previous node"

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
    
    distances[source] = 0;
    minHeap.push({0, source});

    while (!minHeap.empty()) {
        int u = minHeap.top().second;
        minHeap.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;  // Update previous
                minHeap.push({distances[v], v});
            }
        }
    }

    return distances;
}


vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    
    // If destination is unreachable, return "No path found"
    if (distances[destination] == INF || previous[destination] == -1) {
        return path;
    }

    // Traverse back using `previous` to reconstruct the path
    for (int v = destination; v != -1; v = previous[v]) {
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

    cout << "\nTotal cost is " << total_cost << endl;
}
