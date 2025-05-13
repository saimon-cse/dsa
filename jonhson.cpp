#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX

struct Edge {
    int u, v, w;
};

void dijkstra(int src, const vector<vector<pair<int, int>>>& adj, vector<int>& dist) {
    int V = adj.size();
    dist.assign(V, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();

        if (d > dist[u]) continue;

        for (auto& [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

void johnson(vector<Edge>& edges, int V) {
    vector<Edge> allEdges = edges;
    for (int i = 0; i < V; i++) {
        allEdges.push_back({V, i, 0}); // Add dummy vertex
    }

    vector<int> h(V + 1, INF);
    h[V] = 0;

    // Bellman-Ford
    for (int i = 0; i < V; i++) {
        for (auto& e : allEdges) {
            if (h[e.u] != INF && h[e.u] + e.w < h[e.v])
                h[e.v] = h[e.u] + e.w;
        }
    }

    // Reweight edges
    vector<vector<pair<int, int>>> adj(V);
    for (auto& e : edges) {
        int newWeight = e.w + h[e.u] - h[e.v];
        adj[e.u].push_back({e.v, newWeight});
    }

    // Run Dijkstra from each vertex
    cout << "All-Pairs Shortest Paths:\n";
    for (int u = 0; u < V; u++) {
        vector<int> dist;
        dijkstra(u, adj, dist);

        for (int v = 0; v < V; v++) {
            if (dist[v] == INF)
                cout << "INF\t";
            else
                cout << dist[v] - h[u] + h[v] << "\t"; // Reverse reweighting
        }
        cout << "\n";
    }
}

int main() {
    int V = 5;
    vector<Edge> edges = {
        {0, 1, -1}, {0, 2,  4},
        {1, 2,  3}, {1, 3,  2}, {1, 4, 2},
        {3, 2,  5}, {3, 1,  1},
        {4, 3, -3}
        
    };

    johnson(edges, V);

    return 0;
}
