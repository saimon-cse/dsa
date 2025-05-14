



#include <iostream>
#include <algorithm>

using namespace std;


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
    
    
    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }
    
    
    int getBalanceFactor(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }
    
    
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        
        
        x->right = y;
        y->left = T2;
        
        
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        
        
        return x;
    }
    
    
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        
        
        y->left = x;
        x->right = T2;
        
        
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        
        
        return y;
    }
    
    
    Node* insertNode(Node* node, int key) {
        
        if (node == nullptr) {
            return new Node(key);
        }
        
        if (key < node->key) {
            node->left = insertNode(node->left, key);
        } else if (key > node->key) {
            node->right = insertNode(node->right, key);
        } else {
            
            return node;
        }
        
        
        node->height = 1 + max(height(node->left), height(node->right));
        
        
        int balance = getBalanceFactor(node);
        
        
        if (balance > 1 && key < node->left->key) {
            return rightRotate(node);
        }
        
        
        if (balance < -1 && key > node->right->key) {
            return leftRotate(node);
        }
        
        
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        
        return node;
    }
    
    
    Node* minValueNode(Node* node) {
        Node* current = node;
        
        
        while (current->left != nullptr) {
            current = current->left;
        }
        
        return current;
    }
    
    
    Node* deleteNode(Node* root, int key) {
        
        if (root == nullptr) {
            return root;
        }
        
        
        
        if (key < root->key) {
            root->left = deleteNode(root->left, key);
        }
        
        
        else if (key > root->key) {
            root->right = deleteNode(root->right, key);
        }
        
        else {
            
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            
            
            
            Node* temp = minValueNode(root->right);
            
            
            root->key = temp->key;
            
            
            root->right = deleteNode(root->right, temp->key);
        }
        
        
        if (root == nullptr) {
            return root;
        }
        
        
        root->height = 1 + max(height(root->left), height(root->right));
        
        
        int balance = getBalanceFactor(root);
        
        
        if (balance > 1 && getBalanceFactor(root->left) >= 0) {
            return rightRotate(root);
        }
        
        
        if (balance > 1 && getBalanceFactor(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        
        
        if (balance < -1 && getBalanceFactor(root->right) <= 0) {
            return leftRotate(root);
        }
        
        
        if (balance < -1 && getBalanceFactor(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        
        return root;
    }
    
    
    void inOrder(Node* root) {
        if (root == nullptr) {
            return;
        }
        
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
    
    
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
    
    
    void insert(int key) {
        root = insertNode(root, key);
    }
    
    
    void remove(int key) {
        root = deleteNode(root, key);
    }
    
    
    void printInOrder() {
        cout << "In-order traversal: ";
        inOrder(root);
        cout << endl;
    }
    
    
    void printPreOrder() {
        cout << "Pre-order traversal: ";
        preOrder(root);
        cout << endl;
    }
};


int main() {
    AVLTree tree;
    
    
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);
    
    
    
    tree.printInOrder();
    tree.printPreOrder();
    
    
    tree.remove(30);
    
    
    tree.printInOrder();
    tree.printPreOrder();
    
    return 0;
}