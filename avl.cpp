// AVL Tree Implementation in C++
// AVL Tree is a self-balancing Binary Search Tree (BST) where the difference between
// heights of left and right subtrees cannot be more than one for all nodes

#include <iostream>
#include <algorithm>

using namespace std;

// AVL Tree Node
class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;
    
    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    Node* root;
    
    // Get the height of a node
    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }
    
    // Get balance factor of a node
    int getBalanceFactor(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }
    
    // Right rotation
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        
        // Perform rotation
        x->right = y;
        y->left = T2;
        
        // Update heights
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        
        // Return new root
        return x;
    }
    
    // Left rotation
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        
        // Perform rotation
        y->left = x;
        x->right = T2;
        
        // Update heights
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        
        // Return new root
        return y;
    }
    
    // Insert a node
    Node* insertNode(Node* node, int key) {
        // Perform standard BST insertion
        if (node == nullptr) {
            return new Node(key);
        }
        
        if (key < node->key) {
            node->left = insertNode(node->left, key);
        } else if (key > node->key) {
            node->right = insertNode(node->right, key);
        } else {
            // Duplicate keys are not allowed
            return node;
        }
        
        // Update height of current node
        node->height = 1 + max(height(node->left), height(node->right));
        
        // Get the balance factor to check if this node became unbalanced
        int balance = getBalanceFactor(node);
        
        // Left Left Case
        if (balance > 1 && key < node->left->key) {
            return rightRotate(node);
        }
        
        // Right Right Case
        if (balance < -1 && key > node->right->key) {
            return leftRotate(node);
        }
        
        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        // No rotations needed, return the node
        return node;
    }
    
    // Find the node with minimum value
    Node* minValueNode(Node* node) {
        Node* current = node;
        
        // Find the leftmost leaf
        while (current->left != nullptr) {
            current = current->left;
        }
        
        return current;
    }
    
    // Delete a node
    Node* deleteNode(Node* root, int key) {
        // Perform standard BST delete
        if (root == nullptr) {
            return root;
        }
        
        // If the key to be deleted is smaller than the root's key,
        // then it lies in left subtree
        if (key < root->key) {
            root->left = deleteNode(root->left, key);
        }
        // If the key to be deleted is greater than the root's key,
        // then it lies in right subtree
        else if (key > root->key) {
            root->right = deleteNode(root->right, key);
        }
        // If key is same as root's key, then this is the node to be deleted
        else {
            // Node with only one child or no child
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            
            // Node with two children: Get the inorder successor (smallest
            // in the right subtree)
            Node* temp = minValueNode(root->right);
            
            // Copy the inorder successor's data to this node
            root->key = temp->key;
            
            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
        
        // If the tree had only one node, return
        if (root == nullptr) {
            return root;
        }
        
        // Update height of current node
        root->height = 1 + max(height(root->left), height(root->right));
        
        // Get the balance factor to check if this node became unbalanced
        int balance = getBalanceFactor(root);
        
        // Left Left Case
        if (balance > 1 && getBalanceFactor(root->left) >= 0) {
            return rightRotate(root);
        }
        
        // Left Right Case
        if (balance > 1 && getBalanceFactor(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        
        // Right Right Case
        if (balance < -1 && getBalanceFactor(root->right) <= 0) {
            return leftRotate(root);
        }
        
        // Right Left Case
        if (balance < -1 && getBalanceFactor(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        
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
    
public:
    AVLTree() : root(nullptr) {}
    
    // Insert a key into the tree
    void insert(int key) {
        root = insertNode(root, key);
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
};

// Example usage
int main() {
    AVLTree tree;
    
    // Insert some values
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);
    
    
    // Print the tree
    tree.printInOrder();
    tree.printPreOrder();
    
    // Delete some values
    tree.remove(30);
    
    // Print the tree after deletion
    tree.printInOrder();
    tree.printPreOrder();
    
    return 0;
}