// Skip List Implementation in C++
// A Skip List is a probabilistic data structure that allows for fast search, insertion,
// and deletion operations on a sorted sequence of elements, with expected time complexity of O(log n)

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>

using namespace std;

// Maximum level for this Skip List
const int MAX_LEVEL = 16;

// Skip List Node
class Node {
public:
    int key;
    // Array to hold pointers to node of different levels
    Node** forward;
    
    Node(int k, int level) : key(k) {
        // Allocate memory for forward array
        forward = new Node*[level + 1];
        
        // Initialize forward array with nullptr
        for (int i = 0; i <= level; i++) {
            forward[i] = nullptr;
        }
    }
    
    ~Node() {
        delete[] forward;
    }
};

class SkipList {
private:
    // Current maximum level of skip list
    int level;
    
    // Pointer to header node
    Node* header;
    
    // Random level generator
    int randomLevel() {
        int lvl = 0;
        float r = static_cast<float>(rand()) / RAND_MAX;
        
        // Probability p = 1/2
        while (r < 0.5 && lvl < MAX_LEVEL) {
            lvl++;
            r = static_cast<float>(rand()) / RAND_MAX;
        }
        
        return lvl;
    }
    
public:
    SkipList() : level(0) {
        // Create header node with maximum level
        header = new Node(numeric_limits<int>::min(), MAX_LEVEL);
        
        // Seed random number generator
        srand(time(nullptr));
    }
    
    ~SkipList() {
        Node* current = header;
        Node* next;
        
        while (current != nullptr) {
            next = current->forward[0];
            delete current;
            current = next;
        }
    }
    
    // Search for an element in skip list
    bool search(int key) {
        Node* current = header;
        
        // Start from highest level and move down
        for (int i = level; i >= 0; i--) {
            // Move forward at current level
            while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                current = current->forward[i];
            }
        }
        
        // Reached level 0 and advance pointer to right position
        current = current->forward[0];
        
        // If current node has key equal to search key, we found it
        return (current != nullptr && current->key == key);
    }
    
    // Insert an element in skip list
    void insert(int key) {
        Node* current = header;
        
        // Create update array and initialize it
        Node* update[MAX_LEVEL + 1];
        for (int i = 0; i <= MAX_LEVEL; i++) {
            update[i] = nullptr;
        }
        
        // Start from highest level and move down
        for (int i = level; i >= 0; i--) {
            // Move forward at current level
            while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            // Store pointer to rightmost node at level i
            update[i] = current;
        }
        
        // Reached level 0 and forward pointer to right position
        current = current->forward[0];
        
        // If current is nullptr or key is not present, insert it
        if (current == nullptr || current->key != key) {
            // Generate a random level for node
            int randomLvl = randomLevel();
            
            // If random level is greater than skip list's current level
            // initialize update value with header for further use
            if (randomLvl > level) {
                for (int i = level + 1; i <= randomLvl; i++) {
                    update[i] = header;
                }
                // Update the list level
                level = randomLvl;
            }
            
            // Create new node with random level
            Node* newNode = new Node(key, randomLvl);
            
            // Insert node at all levels
            for (int i = 0; i <= randomLvl; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
            
            cout << "Successfully inserted key " << key << endl;
        }
    }
    
    // Delete an element from skip list
    void remove(int key) {
        Node* current = header;
        
        // Create update array and initialize it
        Node* update[MAX_LEVEL + 1];
        
        // Start from highest level and move down
        for (int i = level; i >= 0; i--) {
            // Move forward at current level
            while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            // Store pointer to rightmost node at level i
            update[i] = current;
        }
        
        // Reached level 0 and forward pointer to right position
        current = current->forward[0];
        
        // If current node is target node
        if (current != nullptr && current->key == key) {
            // Start from lowest level and rearrange pointers
            for (int i = 0; i <= level; i++) {
                // If at level i, next node is not target node, break the loop
                if (update[i]->forward[i] != current) {
                    break;
                }
                update[i]->forward[i] = current->forward[i];
            }
            
            // Remove levels with no elements
            while (level > 0 && header->forward[level] == nullptr) {
                level--;
            }
            
            delete current;
            cout << "Successfully deleted key " << key << endl;
        } else {
            cout << "Key " << key << " not found in the list" << endl;
        }
    }
    
    // Display skip list level by level
    void display() {
        cout << "\n*****Skip List*****" << endl;
        for (int i = 0; i <= level; i++) {
            Node* node = header->forward[i];
            cout << "Level " << i << ": ";
            while (node != nullptr) {
                cout << node->key << " ";
                node = node->forward[i];
            }
            cout << endl;
        }
    }
};

// Example usage
int main() {
    SkipList list;
    
    // Insert some values
    list.insert(3);
    list.insert(6);
    list.insert(7);
    list.insert(9);
    list.insert(12);
    list.insert(19);
    list.insert(17);
    list.insert(26);
    list.insert(21);
    list.insert(25);
    
    // Display skip list
    list.display();
    
    // Search for elements
    cout << "\nSearching for 19: " << (list.search(19) ? "Found" : "Not Found") << endl;
    cout << "Searching for 20: " << (list.search(20) ? "Found" : "Not Found") << endl;
    
    // Delete elements
    list.remove(19);
    list.remove(20);
    
    
    // Display after deletion
    list.display();
    
    return 0;
}