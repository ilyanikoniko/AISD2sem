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

    bool contains(Node* node, int key) const {
        if (node == nullptr) {
            return false;
        }
        if (key < node->key) {
            return contains(node->left, key);
        } else if (key > node->key) {
            return contains(node->right, key);
        }
        return true; 
    }

    bool erase(Node*& node, int key) {
        if (node == nullptr) {
            return false;
        }
        if (key < node->key) {
            return erase(node->left, key);
        } else if (key > node->key) {
            return erase(node->right, key);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                node = temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                node = temp;
            } else {
                Node* temp = node->right;
                while (temp->left != nullptr) {
                    temp = temp->left;
                }
                node->key = temp->key;
                erase(node->right, temp->key);
            }
            return true;
        }
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

    bool contains(int key) const {
        return contains(root, key);
    }

    bool erase(int key) {
        return erase(root, key);
    }
};