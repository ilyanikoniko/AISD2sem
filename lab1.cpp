#include <iostream>
#include <random>

class Binary {
    private:

    struct Node {
        int key;
        Node* left;
        Node* right;

        Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void clear(Node* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    Node* copy(Node* node) {
        if (node == nullptr) {
            return nullptr;  
        }
        
        Node* newNode = new Node(node->key);

        newNode->left = copy(node->left);
        newNode->right = copy(node->right);

        return newNode;
    }

    public:
    Binary() : root(nullptr) {}
    ~Binary(){ clear(root);}
    Binary(const Binary& other) {
        root = copy(other.root);  
    }

    Binary& operator=(const Binary& other) {
        if (this != &other) {  
            clear(root);       
            root = copy(other.root);  
        }
        return *this;  
    }
};