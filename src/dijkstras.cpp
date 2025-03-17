#include "dijkstras.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

const int UNDEFINED = -1;


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    /*
    (0) --5--> (1)
     |        /
     2      3
     |    /
    (2)
    */

    int numVertices = G.size(); 
    // initialize to infinity
    vector<int> distances(numVertices, INF); 
    vector<bool> visited(numVertices, false);
    previous.assign(numVertices, UNDEFINED);

    // want minheap so that the shortest is added everytime!!
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
    
    distances[source] = 0;
    previous[source] = UNDEFINED;
    minHeap.push({0, source});

    while (!minHeap.empty()) {
        // get the node with the shortest distance
        int u = minHeap.top().second;
        minHeap.pop();

        if (visited[u]) continue; 
        visited[u] = true;
        // exploring all the edges from the node you are looking at
        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            // if the shortest is fo0und, need to update the distance and path
            // would be (distance[u] + weight)
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }

    return distances;
}


vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    
    // if unreachable ->"No path found"
    if (distances[destination] == INF || previous[destination] == -1) {
        return path;
    }

    // need to go back to the previous to get the new path
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    // need to reverse to get the correct order
    reverse(path.begin(), path.end()); 
    return path;
}



void print_path(const vector<int>& path, int total_cost) {
    if (path.empty()) {
        cout << "No path found." << endl;
        return;
    }

    for (size_t i = 0; i < path.size(); i++) {
        if (i > 0) cout << " ";  
        cout << path[i];
    }

    cout << " \nTotal cost is " << total_cost << endl;
}
