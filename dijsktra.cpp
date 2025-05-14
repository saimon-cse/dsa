



#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using namespace std;


class Graph {
    int V; 
    vector<vector<pair<int, int>>> adj; 
    
public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }
    
    
    void addEdge(int u, int v, int weight) {
        adj[u].push_back(make_pair(v, weight));
        adj[v].push_back(make_pair(u, weight)); 
    }
    
    
    vector<int> dijkstra(int src) {
        
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        
        vector<int> dist(V, numeric_limits<int>::max());
        
        
        pq.push(make_pair(0, src));
        dist[src] = 0;
        
        
        while (!pq.empty()) {
            
            int u = pq.top().second;
            pq.pop();
            
            
            for (auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;
                
                
                if (dist[v] > dist[u] + weight) {
                    
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        
        return dist;
    }
    
    
    void printSolution(const vector<int>& dist) {
        cout << "Vertex \t Distance from Source" << endl;
        for (int i = 0; i < V; i++) {
            cout << i << " \t " << dist[i] << endl;
        }
    }
};


int main() {
    
    Graph g(9);
    
    
    
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
    
    
    vector<int> dist = g.dijkstra(0);
    
    
    g.printSolution(dist);
    
    return 0;
}