// Bellman-Ford Algorithm Implementation in C++
// This algorithm finds the shortest paths from a source vertex to all other vertices,
// even in the presence of negative weight edges. It can also detect negative weight cycles.

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Structure to represent a weighted edge in graph
struct Edge {
    int src, dest, weight;
};

// Graph class using edge list representation
class Graph {
    int V, E; // Number of vertices and edges
    vector<Edge> edges; // Edge list
    
public:
    Graph(int vertices, int edgeCount) : V(vertices), E(edgeCount) {
        edges.reserve(E);
    }
    
    // Add an edge to the graph
    void addEdge(int src, int dest, int weight) {
        Edge edge = {src, dest, weight};
        edges.push_back(edge);
    }
    
    // Bellman-Ford algorithm to find shortest paths from src to all vertices
    vector<int> bellmanFord(int src) {
        // Initialize distances from src to all vertices as infinity
        vector<int> dist(V, numeric_limits<int>::max());
        dist[src] = 0; // Distance of source vertex from itself is 0
        
        // Relax all edges |V| - 1 times
        // A shortest path can have at most |V| - 1 edges
        for (int i = 1; i < V; i++) {
            for (int j = 0; j < E; j++) {
                int u = edges[j].src;
                int v = edges[j].dest;
                int weight = edges[j].weight;
                
                // If vertex u is reachable and there's a shorter path to v
                if (dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
        
        // Check for negative-weight cycles
        for (int i = 0; i < E; i++) {
            int u = edges[i].src;
            int v = edges[i].dest;
            int weight = edges[i].weight;
            
            // If there's still a shorter path after |V| - 1 relaxations, we have a negative cycle
            if (dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                cout << "Graph contains negative weight cycle" << endl;
                return vector<int>(); // Return empty vector to indicate error
            }
        }
        
        return dist;
    }
    
    // Print the solution
    void printSolution(const vector<int>& dist) {
        if (dist.empty()) {
            return; // Negative cycle was detected
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

// Example usage
int main() {
    // Create a graph with 5 vertices and 8 edges
    int V = 5;
    int E = 8;
    Graph g(V, E);
    
    // Add edges
    g.addEdge(0, 1, -1);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(1, 4, 2);
    g.addEdge(3, 2, 5);
    g.addEdge(3, 1, 1);
    g.addEdge(4, 3, -3);
    
    // Run Bellman-Ford algorithm with source vertex 0
    vector<int> dist = g.bellmanFord(0);
    
    // Print the shortest distances
    g.printSolution(dist);
    
    return 0;
}