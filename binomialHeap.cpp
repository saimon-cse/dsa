#include <iostream>
#include <climits>
using namespace std;

struct Node {
    int key, degree;
    Node *parent, *child, *sibling;

    Node(int val) {
        key = val;
        degree = 0;
        parent = child = sibling = nullptr;
    }
};

class BinomialHeap {
    Node* head;

    Node* mergeTrees(Node* b1, Node* b2) {
        if (b1->key > b2->key) swap(b1, b2);
        b2->parent = b1;
        b2->sibling = b1->child;
        b1->child = b2;
        b1->degree++;
        return b1;
    }

    Node* unionHeaps(Node* h1, Node* h2) {
        if (!h1) return h2;
        if (!h2) return h1;

        Node* res;
        Node* tail;

        if (h1->degree <= h2->degree) {
            res = h1;
            h1 = h1->sibling;
        } else {
            res = h2;
            h2 = h2->sibling;
        }

        tail = res;

        while (h1 && h2) {
            if (h1->degree <= h2->degree) {
                tail->sibling = h1;
                h1 = h1->sibling;
            } else {
                tail->sibling = h2;
                h2 = h2->sibling;
            }
            tail = tail->sibling;
        }

        tail->sibling = h1 ? h1 : h2;
        return res;
    }

    void linkTrees(Node* &head) {
        if (!head) return;

        Node* prev = nullptr;
        Node* curr = head;
        Node* next = curr->sibling;

        while (next) {
            if ((curr->degree != next->degree) ||
                (next->sibling && next->sibling->degree == curr->degree)) {
                prev = curr;
                curr = next;
            } else {
                if (curr->key <= next->key) {
                    curr->sibling = next->sibling;
                    curr = mergeTrees(curr, next);
                } else {
                    if (prev == nullptr) head = next;
                    else prev->sibling = next;
                    curr = mergeTrees(next, curr);
                }
            }
            next = curr->sibling;
        }
    }

    Node* reverseList(Node* node) {
        Node* prev = nullptr;
        while (node) {
            Node* next = node->sibling;
            node->sibling = prev;
            node->parent = nullptr;
            prev = node;
            node = next;
        }
        return prev;
    }

public:
    BinomialHeap(): head(nullptr) {}

    void insert(int key) {
        Node* temp = new Node(key);
        head = unionHeaps(head, temp);
        linkTrees(head);
    }

    Node* findMin() {
        Node* y = nullptr;
        Node* x = head;
        int minVal = INT_MAX;
        while (x != nullptr) {
            if (x->key < minVal) {
                minVal = x->key;
                y = x;
            }
            x = x->sibling;
        }
        return y;
    }

    int extractMin() {
        if (!head) return INT_MAX;

        Node* minNode = findMin();
        Node* prevMin = nullptr, *curr = head;

        while (curr->sibling && curr->sibling != minNode) {
            curr = curr->sibling;
        }

        if (curr == minNode) head = minNode->sibling;
        else curr->sibling = minNode->sibling;

        Node* child = reverseList(minNode->child);
        head = unionHeaps(head, child);
        linkTrees(head);

        int minVal = minNode->key;
        delete minNode;
        return minVal;
    }

    void display() {
        cout << "Binomial Heap:\n";
        Node* temp = head;
        while (temp) {
            cout << "B" << temp->degree << ": ";
            printTree(temp);
            cout << "\n";
            temp = temp->sibling;
        }
    }

    void printTree(Node* node) {
        if (node == nullptr) return;
        cout << node->key << " ";
        printTree(node->child);
        printTree(node->sibling);
    }
};

int main() {
    BinomialHeap bh;
    

    bh.insert(10);
    bh.insert(20);
    bh.insert(5);
    bh.insert(30);
    bh.insert(1);

    bh.display();

    cout << "\nExtracted Min: " << bh.extractMin() << endl;

    bh.display();

    return 0;
}
