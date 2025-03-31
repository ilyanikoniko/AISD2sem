#include <windows.h>
#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>


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

    void inorderTraversal(Node* node, vector<int>& elements) const {
        if (node == nullptr) return;
        inorderTraversal(node->left, elements);
        elements.push_back(node->key);
        inorderTraversal(node->right, elements);
    }

    void findIntersection(Node* node, const Binary& other, vector<int>& result) const {
        if (node == nullptr) return;
        findIntersection(node->left, other, result);
        if (other.contains(node->key)) {
            result.push_back(node->key);
        }
        findIntersection(node->right, other, result);
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

    // Функция-генератор псевдослучайных чисел
    size_t lcg(){
        static size_t x = 0;
        x = (1021*x+24631) % 116640;
        return x;
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
    
    void inorderTraversal(vector<int>& elements) const {
        inorderTraversal(root, elements);
    }

    void findIntersection(const Binary& other, vector<int>& result) const {
        findIntersection(root, other, result);
    }
};

vector<int> getUnion(const Binary& tree1, const Binary& tree2) {
    vector<int> result;

    tree1.inorderTraversal(result);
    tree2.inorderTraversal(result);

    sort(result.begin(), result.end());               
    result.erase(unique(result.begin(), result.end()), result.end()); 

    return result;
}

// Функция для пересечения двух деревьев
vector<int> getIntersection(const Binary& tree1, const Binary& tree2) {
    vector<int> result;
    tree1.findIntersection(tree2, result);
    return result;
}

void random_numbers(Binary& tree, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        int randomNumber = tree.lcg(); 
        tree.insert(randomNumber); 
    }
}

void filling_task(int size) {
    cout << "Size:" << size << endl;
    double time = 0;
    double time1 = 0;
    for (int i = 0; i < 100; i++) {
        Binary tree;
        vector<int> vec;
        auto begin = std::chrono::steady_clock::now();
        for (int i = 0; i < size; i++) {
            tree.insert(tree.lcg());
        }
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        time += elapsed_ms.count();

        auto begin1 = std::chrono::steady_clock::now();
        for (int i = 0; i < size; i++) {
            vec.push_back(rand());
        }
        auto end1 = std::chrono::steady_clock::now();
        auto elapsed_ms1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1);
        time1 += elapsed_ms1.count()*1000;
    }
    cout << "Time to fill the binary tree:" << (time / 100) << " microseconds" << endl;
    cout << "Vector filling time:" << (time1 / 100) << " microseconds" << endl;
}

void search_time(int size)
{
    cout << "Size:" << size << endl;
    double time = 0;
    double time1 = 0;
    for (int i = 0; i < 1000; i++) {
        Binary tree;
        vector<int> vec;
        for (int i = 0; i < size; i++) {
            tree.insert(tree.lcg());
        }
        int random_number = rand();
        auto begin = std::chrono::steady_clock::now();
        tree.contains(random_number);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        time += elapsed_ms.count();
        for (int i = 0; i < size; i++) {
            vec.push_back(rand());
        }
        int random_number1 = rand();
        auto begin1 = std::chrono::steady_clock::now();
        auto a = find(vec.begin(), vec.end(), random_number1);
        auto end1 = std::chrono::steady_clock::now();
        auto elapsed_ms1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1);
        time1 += elapsed_ms1.count();
    }
    cout << "Binary tree number search time:" << (time / 100) << " microseconds" << endl;
    cout << "Vector number search time:" << (time1 / 100) << " microseconds" << endl;
}
void adding_and_deleting_time(int size) {
    cout << "Size:" << size << endl;
    double time = 0;
    double time1 = 0;
    for (int i = 0; i < 1000; i++) {
        Binary tree;
        vector<int> vec;
        for (int i = 0; i < size; i++) {
            tree.insert(tree.lcg());
        }
        int random_number = rand();
        int random_number_delete = rand();
        auto begin = std::chrono::steady_clock::now();
        tree.insert(random_number);
        tree.erase(random_number_delete);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        time += elapsed_ms.count();
        for (int i = 0; i < size; i++) {
            vec.push_back(rand());
        }
        int random_number1 = rand();
        int random_number_delete1 = rand();
        auto begin1 = std::chrono::steady_clock::now();
        vec.push_back(random_number1);
        vec.erase(remove(vec.begin(), vec.end(), random_number_delete1), vec.end());
        auto end1 = std::chrono::steady_clock::now();
        auto elapsed_ms1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1);
        time1 += elapsed_ms1.count();
    }
    cout << "Time of adding and removing numbers of a binary tree:" << (time / 100) << " nanoseconds" << endl;
    cout << "Time to add and remove a vector number:" << (time1 / 100) << " nanoseconds" << endl;
}

int main() {
   setlocale(LC_ALL, "ru");
   SetConsoleCP(1251);
   SetConsoleOutputCP(1251);
   Binary tree;
   Binary tree1;
   Binary tree2;
   tree2.insert(30);
   tree2.insert(20);
   tree.insert(50);
   tree.insert(30);
   tree.insert(20);
   tree.print();
   tree.insert(20);
   tree.print();
   tree.contains(10);
   tree.erase(20);
   tree.print();
   tree.insert(20);
   tree1.insert(5);
   tree1.insert(10);
   vector<int> v = getUnion(tree,tree1);
   cout<<"The union of trees:"<<endl;
   for(int i=0; i<v.size(); ++i)
   {
    cout<<v[i]<<endl;
   }
   vector<int> v1 = getIntersection(tree,tree2);
   cout<<"The intersection of trees:"<<endl;
   for(int i=0; i<v1.size(); ++i)
   {
    cout<<v1[i]<<endl;
   }

   // Для каждого размера контейнера (1000, 10000, 100000)
   for (int size : {1000, 10000, 100000}) {
    cout << "Size of contanier: " << size << endl;
    
    // Замер времени для заполнения
    filling_task(size);
    
    // Замер времени для поиска
    search_time(size);
    
    // Замер времени для добавления и удаления
    adding_and_deleting_time(size);
    
    cout << endl;
    }
}