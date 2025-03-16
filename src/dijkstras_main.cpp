#include "dijkstras.h"
#include <iostream>

using namespace std;

int main() {
    Graph G;
    string filename;
    cout << "Enter the graph input file: ";
    cin >> filename;
    
    try {
        file_to_graph(filename, G);
    } 
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }
    
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    
    for (int i = 0; i < G.numVertices; i++) {
        vector<int> path = extract_shortest_path(distances, previous, i);
        cout << "Shortest path to vertex " << i << ": ";
        print_path(path, distances[i]);
    }
    
    return 0;
}

