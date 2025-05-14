



#include <iostream>

using namespace std;


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
    
    
    Node* rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }
    
    
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }
    
    
    Node* splay(Node* root, int key) {
        
        if (root == nullptr || root->key == key) {
            return root;
        }
        
        
        if (root->key > key) {
            
            if (root->left == nullptr) {
                return root;
            }
            
            
            if (root->left->key > key) {
                
                root->left->left = splay(root->left->left, key);
                
                
                root = rightRotate(root);
            }
            
            else if (root->left->key < key) {
                
                root->left->right = splay(root->left->right, key);
                
                
                if (root->left->right != nullptr) {
                    root->left = leftRotate(root->left);
                }
            }
            
            
            return (root->left == nullptr) ? root : rightRotate(root);
        }
        
        else {
            
            if (root->right == nullptr) {
                return root;
            }
            
            
            if (root->right->key > key) {
                
                root->right->left = splay(root->right->left, key);
                
                
                if (root->right->left != nullptr) {
                    root->right = rightRotate(root->right);
                }
            }
            
            else if (root->right->key < key) {
                
                root->right->right = splay(root->right->right, key);
                
                
                root = leftRotate(root);
            }
            
            
            return (root->right == nullptr) ? root : leftRotate(root);
        }
    }
    
    
    Node* search(Node* root, int key) {
        return splay(root, key);
    }
    
    
    Node* insert(Node* root, int key) {
        
        if (root == nullptr) {
            return new Node(key);
        }
        
        
        root = splay(root, key);
        
        
        if (root->key == key) {
            return root;
        }
        
        
        Node* newNode = new Node(key);
        
        
        
        if (root->key > key) {
            newNode->right = root;
            newNode->left = root->left;
            root->left = nullptr;
        }
        
        
        else {
            newNode->left = root;
            newNode->right = root->right;
            root->right = nullptr;
        }
        
        return newNode;
    }
    
    
    Node* deleteNode(Node* root, int key) {
        if (root == nullptr) {
            return nullptr;
        }
        
        
        root = splay(root, key);
        
        
        if (root->key != key) {
            return root;
        }
        
        
        Node* temp;
        
        
        if (root->left == nullptr) {
            temp = root;
            root = root->right;
        }
        
        else {
            temp = root;
            
            
            root = root->left;
            root = splay(root, key);
            root->right = temp->right;
        }
        
        delete temp;
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
    
    
    void insert(int key) {
        root = insert(root, key);
    }
    
    
    void search(int key) {
        root = search(root, key);
        if (root->key == key) {
            cout << "Key " << key << " found in the tree" << endl;
        } else {
            cout << "Key " << key << " not found in the tree" << endl;
        }
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
    
    
    int getRootKey() {
        if (root == nullptr) {
            cout << "Tree is empty" << endl;
            return -1;
        }
        return root->key;
    }
};


int main() {
    SplayTree tree;
    
    
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);
    
    
    tree.printInOrder();
    
    
    tree.search(30);
    cout << "After searching 30, root is: " << tree.getRootKey() << endl;
    tree.printInOrder();
    
    
    tree.remove(30);
    cout << "After removing 30:" << endl;
    tree.printInOrder();
    
    
    tree.search(25);
    cout << "After searching 25, root is: " << tree.getRootKey() << endl;
    tree.printInOrder();
    
    return 0;
}