#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX

class Graph {
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int V) : V(V) {
        adj.resize(V);
    }

    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight}); 
    }

    void primMST() {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        vector<int> key(V, INF);     
        vector<int> parent(V, -1);   
        vector<bool> inMST(V, false);

        pq.push({0, 0});  
        key[0] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            inMST[u] = true;

            for (auto& [v, weight] : adj[u]) {
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    pq.push({key[v], v});
                    parent[v] = u;
                }
            }
        }

        cout << "Edge \tWeight\n";
        for (int i = 1; i < V; i++)
            cout << parent[i] << " - " << i << "\t" << key[i] << "\n";
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    g.primMST();
    

    return 0;
}
