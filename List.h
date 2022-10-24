#pragma once

#include <iostream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

// структура списка
template<typename T>
struct Node {
    Node *prev;
    Node *next;
    T value;
};

// класс кольцевого двусвязного списка
template<typename T>
class List {
    Node<T> *head;
public:

    //Инициализация списка
    List() {
        head = NULL;
    }

    //Очистка списка
    ~List() {
        if (head != NULL) {
            Delete_List();
        }
    }

    // Добавление элемента со значением в начало список
    void add(T value) {
        Node<T> *elem = new Node<T>;
        elem->next = elem->prev = elem;
        elem->value = value;
        if (head == NULL)
            head = elem;
        else {
            elem->next = head;
            elem->prev = head->prev;
            head->prev->next = elem;
            head->prev = elem;
        }
    };

    //Удаление элементов в списке
    void Delete_List() {
        if (head == NULL)
            return;
        else {
            Node<T> *curr;
            head->prev->next = NULL;
            while (head != NULL) {
                curr = head->next;
                delete head;
                head = curr;
            }
            head = NULL;
        }
    }

    void remove(T value) {
        // Удаляет из списка значение val. Возвращает исключение, если значение отсутствует в списке
        if (this->isEmpty())
            throw runtime_error("Error: Removing from empty list");

        if (head->value == value) {
            if (head->next == head) {  // Если в списке 1 элемент
                delete head;
                head = NULL;
            } else {
                head->prev->next = head->next;
                head->next->prev = head->prev;
                Node<T> *tmp = head->next;
                delete head;
                head = tmp;
            }
            return;
        }

        Node<T> *node = this->find(value);
        if (node != NULL) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            delete node;
        } else {
            throw runtime_error("Error: Removing non-existing value from list");
        }
    }

    bool isEmpty() {
        return this->head == NULL;
    }

    bool has(T value) {
        // Возвращает True, если в списке есть значение value
        return this->find(value) != NULL;
    }

    Node<T> *find(T value) {
        // Возвращает указатель на узел со значением value. Если такого нет, то возвращает NULL
        if (this->isEmpty()) {
            throw runtime_error("Error: search in empty list");
        }
        if (this->head->value == value) {
            return head;
        }
        Node<T> *curr = head->next;
        while (curr != head) {
            if (curr->value == value)
                return curr;
            curr = curr->next;
        }
        return NULL;
    }


    void print() {
        for (T item: this->to_vector()) {
            cout << item << " ";
        }
    }

    vector<T> to_vector() {
        vector<T> result = {};
        if (!this->isEmpty()) {
            result.push_back(head->value);
            Node<T> *curr = head->next;
            while (curr != head) {
                result.push_back(curr->value);
                curr = curr->next;
            }
        }
        return result;
    }

    string to_string(string (*to_str)(T&)) {
        string result = "";
        for (T &item: this->to_vector()) {
            result += to_str(item) + " <-> ";
        }
        return result;
    }
};