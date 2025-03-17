#include <iostream>
#include <cstdlib>  
#include <ctime>
#include <optional>
#include <string>
#include <vector>
#include <utility>  // для std::pair

class Hash_table {
private:
    struct Bucket {
        std::optional<std::pair<int, std::string>> data;  // Пара ключ-значение или пусто
        bool isDeleted = false;  // Флаг для удалённых элементов
    };

    size_t table_size;  
    Bucket* table;  // Массив бакетов
public:
    //Конструктор для пустой таблицы
    Hash_table(size_t size = 10) : table_size(size), table(new Bucket[size]) {}

    // Конструктор копирования
    Hash_table(const Hash_table& other): table_size(other.table_size), table(new Bucket[other.table_size]){
        for (size_t i = 0; i < table_size; ++i) {
            table[i] = other.table[i];  
        }
    }

    // Деструктор
    Hash_table() {
        delete[] table;
    }
};