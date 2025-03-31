#include <iostream>
#include <complex>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class BinarySet {
private:
    struct Node {
        T key;
        Node* left;
        Node* right;

        Node(const T& k) : key(k), left(nullptr), right(nullptr) {}
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

    bool insert(Node*& node, const T& key) {
        if (node == nullptr) {
            node = new Node(key);
            return true;
        }
        if (key == node->key) {
            return false;
        }
        if (key < node->key) {
            return insert(node->left, key);
        } else {
            return insert(node->right, key);
        }
    }

    bool contains(Node* node, const T& key) const {
        if (node == nullptr) {
            return false;
        }
        if (key == node->key) {
            return true;
        }
        if (key < node->key) {
            return contains(node->left, key);
        } else {
            return contains(node->right, key);
        }
    }

    bool erase(Node*& node, const T& key) {
        if (node == nullptr) {
            return false;
        }
        if (key < node->key) {
            return erase(node->left, key);
        } else if (key > node->key) {
            return erase(node->right, key);
        } else {
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

    void inorderTraversal(Node* node, vector<T>& elements) const {
        if (node == nullptr) return;
        inorderTraversal(node->left, elements);
        elements.push_back(node->key);
        inorderTraversal(node->right, elements);
    }

public:
    BinarySet() : root(nullptr) {}
    ~BinarySet() { clear(root); }
    
    BinarySet(const BinarySet& other) {
        root = copy(other.root);
    }

    BinarySet& operator=(const BinarySet& other) {
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

    bool insert(const T& key) {
        return insert(root, key);
    }

    bool contains(const T& key) const {
        return contains(root, key);
    }

    bool erase(const T& key) {
        return erase(root, key);
    }

    vector<T> toVector() const {
        vector<T> elements;
        inorderTraversal(root, elements);
        return elements;
    }
};

// Специализация операторов для complex (только < и >)
template <typename T>
bool operator<(const complex<T>& lhs, const complex<T>& rhs) {
    return abs(lhs) < abs(rhs);
}

template <typename T>
bool operator>(const complex<T>& lhs, const complex<T>& rhs) {
    return abs(lhs) > abs(rhs);
}

int main() {
    // Тестирование с int
    BinarySet<int> intSet;
    intSet.insert(5);
    intSet.insert(3);
    intSet.insert(7);
    cout << "Int set: ";
    intSet.print();

    // Тестирование с complex<float>
    BinarySet<complex<float>> complexSet;
    complexSet.insert({1.0f, 2.0f});
    complexSet.insert({3.0f, 4.0f});
    complexSet.insert({0.5f, 0.5f});
    cout << "Complex<float> set: ";
    complexSet.print();

    // Проверка наличия элемента
    cout << "Contains (3.0, 4.0): " 
         << complexSet.contains({3.0f, 4.0f}) << endl;

    // Тестирование с string
    BinarySet<string> stringSet;
    stringSet.insert("apple");
    stringSet.insert("banana");
    stringSet.insert("cherry");
    cout << "String set: ";
    stringSet.print();

    // Удаление элемента
    stringSet.erase("banana");
    cout << "After erase: ";
    stringSet.print();

    return 0;
}