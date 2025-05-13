// Dijkstra's Algorithm Implementation in C++
// This implementation uses an adjacency list representation of a graph
// and a priority queue to efficiently find the shortest paths from a source vertex

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

// Graph class using adjacency list representation
class Graph {
    int V; // Number of vertices
    vector<vector<pair<int, int>>> adj; // Adjacency list of <vertex, weight> pairs
    
public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }
    
    // Add an edge to the graph
    void addEdge(int u, int v, int weight) {
        adj[u].push_back(make_pair(v, weight));
        adj[v].push_back(make_pair(u, weight)); // For undirected graph
    }
    
    // Dijkstra's algorithm to find shortest paths from src to all vertices
    vector<int> dijkstra(int src) {
        // Min-heap priority queue
        // pair<dist, vertex>
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        // Vector to store distances from src to all vertices
        vector<int> dist(V, numeric_limits<int>::max());
        
        // Add source to priority queue and set its distance to 0
        pq.push(make_pair(0, src));
        dist[src] = 0;
        
        // Loop until priority queue becomes empty
        while (!pq.empty()) {
            // Extract minimum distance vertex from priority queue
            int u = pq.top().second;
            pq.pop();
            
            // Visit all adjacent vertices of u
            for (auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;
                
                // If there is a shorter path to v through u
                if (dist[v] > dist[u] + weight) {
                    // Update distance of v
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        
        return dist;
    }
    
    // Print the solution
    void printSolution(const vector<int>& dist) {
        cout << "Vertex \t Distance from Source" << endl;
        for (int i = 0; i < V; i++) {
            cout << i << " \t " << dist[i] << endl;
        }
    }
};

// Example usage
int main() {
    // Create a graph with 9 vertices
    Graph g(9);
    
    
    // Add edges
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
    
    // Run Dijkstra's algorithm with source vertex 0
    vector<int> dist = g.dijkstra(0);
    
    // Print the shortest distances
    g.printSolution(dist);
    
    return 0;
}