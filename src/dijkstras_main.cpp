#include "dijkstras.h"
#include <iostream>
#include <set>

#define my_assert(e) {cout << #e << ((e) ? " passed" : " failed") << endl;}

using namespace std;

// Function to verify correctness of Dijkstra's implementation
void verify_dijkstra(const Graph& G, int source) {
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    for (int i = 0; i < G.numVertices; i++) {
        if (i == source) {
            // distance is 0
            my_assert(distances[i] == 0);
        } else {
            // checking with infinity/should be bvalid
            my_assert(distances[i] >= 0 || distances[i] == INF); 
        }
    }
}

void run_dijkstra_test(const string& filename, int source) {
    Graph G;
    file_to_graph(filename, G);

    cout << "\nDijkstra on graph: " << filename << " from source: " << source << endl;
    
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    // need to print shortest paths and distances
    for (int i = 0; i < G.numVertices; i++) {
        cout << "Shortest path from " << source << " to " << i << ": ";
        vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }
    verify_dijkstra(G, source);
}

int main() {
    run_dijkstra_test("small.txt", 0);
    run_dijkstra_test("medium.txt", 0);
    run_dijkstra_test("large.txt", 0);
    run_dijkstra_test("largest.txt", 0);

    return 0;
}
