



#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>

using namespace std;


const int MAX_LEVEL = 16;


class Node {
public:
    int key;
    
    Node** forward;
    
    Node(int k, int level) : key(k) {
        
        forward = new Node*[level + 1];
        
        
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
    
    int level;
    
    
    Node* header;
    
    
    int randomLevel() {
        int lvl = 0;
        float r = static_cast<float>(rand()) / RAND_MAX;
        
        
        while (r < 0.5 && lvl < MAX_LEVEL) {
            lvl++;
            r = static_cast<float>(rand()) / RAND_MAX;
        }
        
        return lvl;
    }
    
public:
    SkipList() : level(0) {
        
        header = new Node(numeric_limits<int>::min(), MAX_LEVEL);
        
        
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
    
    
    bool search(int key) {
        Node* current = header;
        
        
        for (int i = level; i >= 0; i--) {
            
            while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                current = current->forward[i];
            }
        }
        
        
        current = current->forward[0];
        
        
        return (current != nullptr && current->key == key);
    }
    
    
    void insert(int key) {
        Node* current = header;
        
        
        Node* update[MAX_LEVEL + 1];
        for (int i = 0; i <= MAX_LEVEL; i++) {
            update[i] = nullptr;
        }
        
        
        for (int i = level; i >= 0; i--) {
            
            while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            
            update[i] = current;
        }
        
        
        current = current->forward[0];
        
        
        if (current == nullptr || current->key != key) {
            
            int randomLvl = randomLevel();
            
            
            
            if (randomLvl > level) {
                for (int i = level + 1; i <= randomLvl; i++) {
                    update[i] = header;
                }
                
                level = randomLvl;
            }
            
            
            Node* newNode = new Node(key, randomLvl);
            
            
            for (int i = 0; i <= randomLvl; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
            
            cout << "Successfully inserted key " << key << endl;
        }
    }
    
    
    void remove(int key) {
        Node* current = header;
        
        
        Node* update[MAX_LEVEL + 1];
        
        
        for (int i = level; i >= 0; i--) {
            
            while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            
            update[i] = current;
        }
        
        
        current = current->forward[0];
        
        
        if (current != nullptr && current->key == key) {
            
            for (int i = 0; i <= level; i++) {
                
                if (update[i]->forward[i] != current) {
                    break;
                }
                update[i]->forward[i] = current->forward[i];
            }
            
            
            while (level > 0 && header->forward[level] == nullptr) {
                level--;
            }
            
            delete current;
            cout << "Successfully deleted key " << key << endl;
        } else {
            cout << "Key " << key << " not found in the list" << endl;
        }
    }
    
    
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


int main() {
    SkipList list;
    
    
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
    
    
    list.display();
    
    
    cout << "\nSearching for 19: " << (list.search(19) ? "Found" : "Not Found") << endl;
    cout << "Searching for 20: " << (list.search(20) ? "Found" : "Not Found") << endl;
    
    
    list.remove(19);
    list.remove(20);
    
    
    
    list.display();
    
    return 0;
}