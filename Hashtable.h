#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include <string>

// Состояния
enum Status {
    FREE, CONTAINS, REMOVED
};

/**
 * Кастомная структура для пары с состоянием в таблице
 * @tparam key_type - ключ
 * @tparam mapped_type - хранимое значение
 */
template<class key_type, class mapped_type>
struct Pair {
    key_type first;
    mapped_type second;
    Status status;

    Pair() : first(key_type()), second(mapped_type()), status(FREE) {}

    Pair(key_type key, mapped_type value) : first(key), second(value), status(FREE) {}

    Pair operator=(const Pair &p) {
        this->first = p.first;
        this->second = p.second;
        return *this;
    }

    bool operator==(const Pair &p) {
        return this->first == p.first && this->second == p.second && this->status == p.status;
    }

};

/**
 * Хэш таблица
 * @tparam K - ключ, реализующий метод std::hash<K> для вычисления хэша и переопредиляющий операторы ==  !=
 * @tparam V - значение
 * @tparam Hash - хэш-функция, определена изначально, можно добавить свою
 */
template<typename K, typename V, typename Hash = std::hash<K>>
class Hashtable {
public:
    using key_type = K;
    using mapped_type = V;
    using size_type = std::size_t;
    using value_type = Pair<key_type, mapped_type>;
    using hasher = Hash;
    using reference = value_type &;
    using pointer = std::vector<value_type>; // Вектор, хранящий наши пары

public:

    Hashtable() : bucket_count(20), load_factor(0.75), table(pointer(20)) {}

    Hashtable(size_type size) : bucket_count(size), load_factor(0.75), table(pointer(size)) {}

    ~Hashtable() {
        bucket_count = 0;
        current_load = 0;
        load_factor = 0.0;
        table.clear();
    }

    void clear() {
        for (value_type &item: this->table) {
            item.status = FREE;
        }
        this->rebuildTable(20);
    }

    bool has(key_type key) {
        auto found_val = this->find(key);
        return found_val != DEFAULT_VALUE;
    }

    bool has(key_type key, mapped_type value) {
        return this->find(key) != DEFAULT_VALUE && this->find(key) == value;
    }

    std::vector<value_type> to_vector() {
        return this->table;
    }

    void insert(key_type key, mapped_type value) {
        size_type index = firstHashFunction(key);
        if (table[index].status == FREE || (table[index].first == key && table[index].status == REMOVED)) {
            table[index] = value_type(key, value);
            table[index].status = CONTAINS;
            current_load++;
            if (current_load >= load_factor * bucket_count) {
                rebuildTable(bucket_count * 2);
            }
            return;
        }
        if (table[index].first == key) {
            table[index].second = value;
            return;
        }
        index = resolveCollision(key, index);
        if (table[index].status != CONTAINS) {
            table[index] = value_type(key, value);
            table[index].status = CONTAINS;
            current_load++;
            if (current_load >= load_factor * bucket_count) {
                rebuildTable(bucket_count * 2);
            }
            return;
        }
        if (table[index].first == key) {
            table[index].second = value;
            return;
        }
//        std::cout << "No bucket to insert for " << key << " " << value << "\n";
    }

    void erase(key_type key, mapped_type value) {
        size_type index = firstHashFunction(key);
        if (table[index].status != CONTAINS)
            return;
        if (table[index].first == key && table[index].second == value) {
            table[index].status = REMOVED;
            current_load--;
            if (current_load <= (1 - load_factor) * bucket_count) {
                rebuildTable(bucket_count / 2);
                return;
            }
        }
        index = resolveCollision(key, index);
        if (table[index].status != CONTAINS)
            return;
        if (table[index].first == key && table[index].second == value) {
            table[index].status = REMOVED;
            current_load--;
            if (current_load <= (1 - load_factor) * bucket_count)
                rebuildTable(bucket_count / 2);
        }
    }

    void erase(key_type key) {
        this->erase(key, this->find(key));
    }

    mapped_type &find(key_type key) {
        size_type index = firstHashFunction(key);
        if (table[index].status == FREE)
            return DEFAULT_VALUE;
        if (table[index].status == CONTAINS && table[index].first == key)
            return table[index].second;
        index = resolveCollision(key, index);
        if (table[index].status == CONTAINS && table[index].first == key)
            return table[index].second;
        return DEFAULT_VALUE;
    }

    void print() {
        for (int i = 0; i < bucket_count; i++) {
            if (table[i].status != FREE) {
                std::cout << i << "| [" << table[i].first << "]: Value : (" << table[i].second << ") " << " Status : "
                          << table[i].status << std::endl;
            } else {
                std::cout << i << ". NULL " << " Status " << FREE << std::endl;
            }
        }
    }

    size_type size() noexcept {
        return current_load;
    }

    void setLoadFactor(double load) {
        if (load <= 0 && load > 1)
            throw std::logic_error("load factor cannot be <= 0 and > 1");
        this->load_factor = load;
    }

    std::string to_string(std::string (*to_str_1)(key_type &), std::string (*to_str_2)(mapped_type &)) {
        std::string result = "";
        auto items = this->to_vector();
        for (int i = 0; i < items.size(); i++) {
            key_type key = items[i].first;
            int keyHash = this->firstHashFunction(key);
            if (items[i].status != FREE) {
                result += std::to_string(i) +
                          "| [" +
                          to_str_1(items[i].first) +
                          "]: Value : (" +
                          to_str_2(items[i].second) +
                          ")  Status : " +
                          std::to_string(items[i].status) +
                          ", First hash: " +
                          std::to_string(keyHash);
                if (keyHash != i) {
                    result += ", Second hashes: ";
                    int currentIndex;
                    int step = 1;
                    do {
                        currentIndex = secondHashFunction(keyHash, step);
                        result += std::to_string(currentIndex) + ", ";
                        step++;
                    } while (i != currentIndex);
                }
                result += "\n";
            } else {
                result += std::to_string(i) +
                          ". NULL  Status " +
                          std::to_string(FREE) +
                          "\n";
            }
        }
        return result;
    }

private:
    // первая хэш функция, просто вызываем хэш функцию на стороне ключа
    size_type firstHashFunction(key_type key) {

        long long temp = hash(key);
        size_t sum = 0;

        while (temp != 0) {
            sum += temp % 10;
            temp /= 10;
        }

        return sum % bucket_count;
    }

    size_type secondHashFunction(size_type keyHash, size_type step) {
        return (keyHash + 3 * step) % bucket_count;
    }

//    size_type secondHashFunction(size_type keyHash, int step, int q1, int q2){
//            size_type resut = keyHash * step * q1 * step * step * q2;
//            return (resut < 0) ? -resut : resut;
//        }

    size_type resolveCollision(key_type key, size_type currentIndex) {
//        const int q1 = (31 % bucket_count == 0 ? 30 : 31);
//        const int q2 = bucket_count;
        size_type oldIndex = currentIndex;
        size_type firstHash = currentIndex;
        size_type step = 1;
        size_type insertIndex = -1; // переменная, хранящая первую встречнную ячейку, которая удалена, и которую нужно будет вернуть
        do {
            currentIndex = secondHashFunction(firstHash, step);
            //currentIndex = (keyHash + step) % bucket_count; //Для теста с вторичной функцией, где шаг = 1
            if (table[currentIndex].status == FREE)
                return (insertIndex != -1) ? insertIndex : currentIndex;
            if (table[currentIndex].status == REMOVED && insertIndex == -1) {
                insertIndex = currentIndex; // Изменяем индекс, если только впервые встретили удалённую ячейку
            }
            if (table[currentIndex].status == CONTAINS && table[currentIndex].first == key) {
                return currentIndex; // ключи равны и ячейка удалена - точное совпадение
            }
            step++;
        } while (oldIndex != currentIndex);
        return (insertIndex != -1) ? insertIndex : currentIndex;
    }

    void rebuildTable(size_type newSize) {
        auto tempTable = table;
        table.clear();
//        std::cout << "Rehash table to new Size " << newSize << "\n";
        //std::cout << "Size before " << current_load << "\n";
        table.resize(newSize);
        size_type oldSize = bucket_count;
        bucket_count = newSize;
        current_load = 0;
        for (int i = 0; i < oldSize; i++) {
            if (tempTable[i].status == CONTAINS) {
                insert(tempTable[i].first, tempTable[i].second);
            }
        }
        //std::cout << "Size after : " << current_load << "\n";
    }

    mapped_type DEFAULT_VALUE = mapped_type();
    pointer table; // вектор пар
    hasher hash; // первичная хэш-функция
    size_type bucket_count; // максимальный размер
    size_type current_load = 0; // размер
    float load_factor; // загрузка таблицы
};
