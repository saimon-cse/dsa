



#include <iostream>
#include <vector>
#include <limits>

using namespace std;


struct Edge {
    int src, dest, weight;
};


class Graph {
    int V, E; 
    vector<Edge> edges; 
    
public:
    Graph(int vertices, int edgeCount) : V(vertices), E(edgeCount) {
        edges.reserve(E);
    }
    
    
    void addEdge(int src, int dest, int weight) {
        Edge edge = {src, dest, weight};
        edges.push_back(edge);
    }
    
    
    vector<int> bellmanFord(int src) {
        
        vector<int> dist(V, numeric_limits<int>::max());
        dist[src] = 0; 
        
        
        
        for (int i = 1; i < V; i++) {
            for (int j = 0; j < E; j++) {
                int u = edges[j].src;
                int v = edges[j].dest;
                int weight = edges[j].weight;
                
                
                if (dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
        
        
        for (int i = 0; i < E; i++) {
            int u = edges[i].src;
            int v = edges[i].dest;
            int weight = edges[i].weight;
            
            
            if (dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                cout << "Graph contains negative weight cycle" << endl;
                return vector<int>(); 
            }
        }
        
        return dist;
    }
    
    
    void printSolution(const vector<int>& dist) {
        if (dist.empty()) {
            return; 
        }
        
        
        cout << "Vertex \t Distance from Source" << endl;
        for (int i = 0; i < V; i++) {
            if (dist[i] == numeric_limits<int>::max()) {
                cout << i << " \t INFINITY" << endl;
            } else {
                cout << i << " \t " << dist[i] << endl;
            }
        }
    }
};


int main() {
    
    int V = 5;
    int E = 8;
    Graph g(V, E);
    
    
    g.addEdge(0, 1, -1);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(1, 4, 2);
    g.addEdge(3, 2, 5);
    g.addEdge(3, 1, 1);
    g.addEdge(4, 3, -3);
    
    
    vector<int> dist = g.bellmanFord(0);
    
    
    g.printSolution(dist);
    
    return 0;
}