// Splay Tree Implementation in C++
// A splay tree is a self-adjusting binary search tree with the property that
// recently accessed elements are quick to access again

#include <iostream>

using namespace std;

// Splay Tree Node
class Node {
public:
    int key;
    Node* left;
    Node* right;
    
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class SplayTree {
private:
    Node* root;
    
    // Right rotate around x
    Node* rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }
    
    // Left rotate around x
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }
    
    // Splay key to the root
    Node* splay(Node* root, int key) {
        // Base cases
        if (root == nullptr || root->key == key) {
            return root;
        }
        
        // Key is in the left subtree
        if (root->key > key) {
            // Key is not in tree
            if (root->left == nullptr) {
                return root;
            }
            
            // Zig-Zig (Left Left)
            if (root->left->key > key) {
                // Recursively bring the key as root of left-left
                root->left->left = splay(root->left->left, key);
                
                // First rotation for root
                root = rightRotate(root);
            }
            // Zig-Zag (Left Right)
            else if (root->left->key < key) {
                // Recursively bring the key as root of left-right
                root->left->right = splay(root->left->right, key);
                
                // First rotation for root->left
                if (root->left->right != nullptr) {
                    root->left = leftRotate(root->left);
                }
            }
            
            // Second rotation for root
            return (root->left == nullptr) ? root : rightRotate(root);
        }
        // Key is in the right subtree
        else {
            // Key is not in tree
            if (root->right == nullptr) {
                return root;
            }
            
            // Zag-Zig (Right Left)
            if (root->right->key > key) {
                // Recursively bring the key as root of right-left
                root->right->left = splay(root->right->left, key);
                
                // First rotation for root->right
                if (root->right->left != nullptr) {
                    root->right = rightRotate(root->right);
                }
            }
            // Zag-Zag (Right Right)
            else if (root->right->key < key) {
                // Recursively bring the key as root of right-right
                root->right->right = splay(root->right->right, key);
                
                // First rotation for root
                root = leftRotate(root);
            }
            
            // Second rotation for root
            return (root->right == nullptr) ? root : leftRotate(root);
        }
    }
    
    // Search and splay
    Node* search(Node* root, int key) {
        return splay(root, key);
    }
    
    // Insert a key
    Node* insert(Node* root, int key) {
        // If tree is empty
        if (root == nullptr) {
            return new Node(key);
        }
        
        // Splay the tree first with key
        root = splay(root, key);
        
        // If key is already present, return
        if (root->key == key) {
            return root;
        }
        
        // Create a new node
        Node* newNode = new Node(key);
        
        // If root's key is greater, make root's left subtree
        // as left of new node and root's right subtree as new node's right
        if (root->key > key) {
            newNode->right = root;
            newNode->left = root->left;
            root->left = nullptr;
        }
        // If root's key is smaller, make root's right subtree
        // as right of new node and root's left subtree as new node's left
        else {
            newNode->left = root;
            newNode->right = root->right;
            root->right = nullptr;
        }
        
        return newNode;
    }
    
    // Delete a key
    Node* deleteNode(Node* root, int key) {
        if (root == nullptr) {
            return nullptr;
        }
        
        // Splay the tree with key
        root = splay(root, key);
        
        // If key is not present
        if (root->key != key) {
            return root;
        }
        
        // If key is present
        Node* temp;
        
        // No left subtree
        if (root->left == nullptr) {
            temp = root;
            root = root->right;
        }
        // Left subtree exists
        else {
            temp = root;
            
            // Make the right subtree as right of left subtree
            root = root->left;
            root = splay(root, key);
            root->right = temp->right;
        }
        
        delete temp;
        return root;
    }
    
    // Inorder traversal
    void inOrder(Node* root) {
        if (root == nullptr) {
            return;
        }
        
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
    
    
    // Preorder traversal
    void preOrder(Node* root) {
        if (root == nullptr) {
            return;
        }
        
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
    
    // Clean up the tree
    void clear(Node* root) {
        if (root == nullptr) {
            return;
        }
        
        clear(root->left);
        clear(root->right);
        delete root;
    }
    
public:
    SplayTree() : root(nullptr) {}
    
    ~SplayTree() {
        clear(root);
    }
    
    // Insert a key into the tree
    void insert(int key) {
        root = insert(root, key);
    }
    
    // Search for a key in the tree and splay
    void search(int key) {
        root = search(root, key);
        if (root->key == key) {
            cout << "Key " << key << " found in the tree" << endl;
        } else {
            cout << "Key " << key << " not found in the tree" << endl;
        }
    }
    
    // Delete a key from the tree
    void remove(int key) {
        root = deleteNode(root, key);
    }
    
    // Print the tree in-order
    void printInOrder() {
        cout << "In-order traversal: ";
        inOrder(root);
        cout << endl;
    }
    
    // Print the tree pre-order
    void printPreOrder() {
        cout << "Pre-order traversal: ";
        preOrder(root);
        cout << endl;
    }
    
    // Get the root key
    int getRootKey() {
        if (root == nullptr) {
            cout << "Tree is empty" << endl;
            return -1;
        }
        return root->key;
    }
};

// Example usage
int main() {
    SplayTree tree;
    
    // Insert some values
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);
    
    // Print the tree
    tree.printInOrder();
    
    // Search for a key (this will splay the key to root)
    tree.search(30);
    cout << "After searching 30, root is: " << tree.getRootKey() << endl;
    tree.printInOrder();
    
    // Delete a key
    tree.remove(30);
    cout << "After removing 30:" << endl;
    tree.printInOrder();
    
    // Access a key to bring it to the root
    tree.search(25);
    cout << "After searching 25, root is: " << tree.getRootKey() << endl;
    tree.printInOrder();
    
    return 0;
}