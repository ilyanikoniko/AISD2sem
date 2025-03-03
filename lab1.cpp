#include <iostream>
#include <random>

using namespace std;
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

    void print(Node* node) const {
        if (node == nullptr) return;
        print(node->left);
        cout << node->key << " ";
        print(node->right);
    }

    bool insert(Node*& node, int key) {
        if (node == nullptr) {
            node = new Node(key);
            return true;
        }
        if (key == node->key)
        {
            return false;
        }
        if (key < node->key) {
            return insert(node->left, key);
        } else if (key > node->key) {
            return insert(node->right, key);
        } 
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

    void print() const {
        print(root); 
        cout << endl;
    }

    bool insert(int key) {
        return insert(root, key);
    }
};