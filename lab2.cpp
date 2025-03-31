#include <iostream>
#include <cstdlib>  
#include <ctime>
#include <string>
#include <vector>



using namespace std;

template <typename K, typename T>
class Hash_table {
private:
    struct Node {
        K key;
        T value;
        Node* next;
        Node(K k, const T& v) : key(k), value(v), next(nullptr) {}
    };

    Node** table;// массив указателей на Node
    size_t table_size;
    size_t table_capacity; 

    // Хэш-функция 
    size_t hash_Function(const K key) const {
        const uint64_t a = 2654435761;// случайная нечётная константа,
        const uint64_t w = 32;// размер машинного слова в битах
        uint64_t key64 = static_cast<uint64_t>(key);//кдюч приводится к 64-битному типу, чтобы избежать переполнения при умножении.
        uint64_t hash = (key64 * a) % (1ULL << w);//(k * a) mod 2^w
        return hash >> (w - static_cast<uint64_t>(log2(table_size)));//битовый сдвиг на (w - l) бит
    }

public:
    //Конструктор для пустой таблицы
    Hash_table(size_t capacity = 16) : table_size(0), table_capacity(capacity) {
        table = new Node*[table_capacity]();
    }

    // Конструктор, заполняющий хэш таблицу случайными значениями
    Hash_table(size_t capacity, size_t num) : table_capacity(capacity), table_size(0) {
        table = new Node*[table_capacity]();
        for (size_t i = 0; i < num; ++i) {
            K key = static_cast<K>(rand());
            T value = static_cast<T>(rand());
            insert(key, value);
        }
    }

    // Конструктор копирования
    Hash_table(const Hash_table& other): table_size(other.table_size), table_capacity(other.table_capacity){
        table = new Node*[table_capacity]();
        for (size_t i = 0; i < capacity; ++i) {
            Node* current = other.table[i];
            while (current != nullptr) {
                insert(current->key, current->value);
                current = current->next;
            }
        }
    }

    // Деструктор
    Hash_table() {
        for (size_t i = 0; i < capacity; ++i) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
            table[i] = nullptr;
        }
        size = 0;
        delete[] table;
    }
};