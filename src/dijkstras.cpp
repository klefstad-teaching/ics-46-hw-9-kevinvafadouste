#include "dijkstras.h"
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distances(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    
    distances[source] = 0;
    pq.push({0, source});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        if (visited[u]) continue;
        visited[u] = true;
        
        for (const Edge& neighbor : G[u]) {
            int v = neighbor.dst, weight = neighbor.weight;
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total) {
    if (path.size() < 2) {
        cout << "No path found." << endl;
        return;
    }
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) cout << " ";
    }
    cout << "\nTotal cost is " << total << "\n";
}
