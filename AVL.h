#pragma once

#include <iostream>
#include "List.h"

using namespace std;

template<typename T1, typename T2>
class AVL {
public:

    class Node {
    public:
        T1 key;
        List<T2> chain;
        int height;
        Node *left;
        Node *right;

        Node(T1 val_1, T2 val_2) {
            height = 1;
            key = val_1;
            chain.add(val_2);
            left = NULL;
            right = NULL;
        }
    };

    Node *root = NULL;
    int n;

    void insert(T1 val_1, T2 val_2) {
        root = insertUtil(root, val_1, val_2);
    }

    void remove(T1 val_1, T2 val_2) {
        if (!this->has(val_1, val_2)) {
            throw runtime_error("Error: Removing non-existing value from tree");
        }
        root = removeUtil(root, val_1, val_2);
    }

    Node *search(T1 val_1) {
        return searchUtil(root, val_1);
    }

    bool has(T1 val_1) {
        Node *node = this->search(val_1);
        return node != nullptr;
    }

    bool has(T1 val_1, T2 val_2) {
        Node *node = this->search(val_1);
        return (node != nullptr && node->chain.has(val_2));
    }

    /**
     * Переводит дерево в строку
     * Принимает две функции, переводящие T1 и T2 в строку
     */
    string to_string(string (*to_str_1)(T1 &), string (*to_str_2)(T2 &)) {
        string result = "";
        this->_to_string(to_str_1, to_str_2, this->root, 0, result);
        return result;
    }

    void clear() {
        this->_clear(this->root);
        this->root = NULL;
    }

    /**
     * Возвращает узлы, значения которых больше val_1
     */
    vector<Node*> get_nodes_higher(T1 val_1) {
        vector<Node*> result = {};
        this->_get_nodes_higher(val_1, this->root, result);
        return result;
    }

    /**
     * Возвращает все вторые(T2) значения дерева
     */
    vector<T2> to_vector_second_value() {
        vector<T2> result = {};
        _to_vector_second_value(this->root, result);
        return result;
    }

private:
    int height(Node *head) {
        if (head == NULL) return 0;
        return head->height;
    }

    Node *rightRotation(Node *head) {
        Node *newhead = head->left;
        head->left = newhead->right;
        newhead->right = head;
        head->height = 1 + max(height(head->left), height(head->right));
        newhead->height = 1 + max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    Node *leftRotation(Node *head) {
        Node *newhead = head->right;
        head->right = newhead->left;
        newhead->left = head;
        head->height = 1 + max(height(head->left), height(head->right));
        newhead->height = 1 + max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    Node *insertUtil(Node *head, T1 val_1, T2 val_2) {
        if (head == NULL) {
            n += 1;
            Node *temp = new Node(val_1, val_2);
            return temp;
        }
        if (val_1 < head->key) head->left = insertUtil(head->left, val_1, val_2);
        else if (val_1 > head->key) head->right = insertUtil(head->right, val_1, val_2);

        else head->chain.add(val_2);  // Добавляем дубликат (по val_1)

        head->height = 1 + max(height(head->left), height(head->right));
        int bal = height(head->left) - height(head->right);
        if (bal > 1) {
            if (val_1 < head->left->key) {
                return rightRotation(head);
            } else {
                head->left = leftRotation(head->left);
                return rightRotation(head);
            }
        } else if (bal < -1) {
            if (val_1 > head->right->key) {
                return leftRotation(head);
            } else {
                head->right = rightRotation(head->right);
                return leftRotation(head);
            }
        }
        return head;
    }

    Node *removeUtil(Node *head, T1 val_1, T2 val_2) {
        if (head == NULL) return NULL;
        if (val_1 < head->key) {
            head->left = removeUtil(head->left, val_1, val_2);
        } else if (val_1 > head->key) {
            head->right = removeUtil(head->right, val_1, val_2);
        } else {
            if (head->chain.to_vector().size() > 1) {  // Если в узле есть дубликаты
                head->chain.remove(val_2);
            } else {
                Node *r = head->right;
                if (head->right == NULL) {
                    Node *l = head->left;
                    delete (head);
                    head = l;
                } else if (head->left == NULL) {
                    delete (head);
                    head = r;
                } else {
                    while (r->left != NULL) r = r->left;
                    head->key = r->key;         //
                    head->chain = r->chain;     // Переносим значения из мин. левого в удаляемый узел
                    r->chain = List<T2>();  // На мин. левом ставим значения гарантированного удаления
                    head->right = removeUtil(head->right, r->key, val_2);
                }
            }
        }
        if (head == NULL) return head;
        head->height = 1 + max(height(head->left), height(head->right));
        int bal = height(head->left) - height(head->right);
        if (bal > 1) {
            if (height(head->left) >= height(head->right)) {
                return rightRotation(head);
            } else {
                head->left = leftRotation(head->left);
                return rightRotation(head);
            }
        } else if (bal < -1) {
            if (height(head->right) >= height(head->left)) {
                return leftRotation(head);
            } else {
                head->right = rightRotation(head->right);
                return leftRotation(head);
            }
        }
        return head;
    }

    Node *searchUtil(Node *head, T1 val_1) {
        if (head == NULL) return NULL;
        T1 k = head->key;
        if (k == val_1) return head;
        if (k > val_1) return searchUtil(head->left, val_1);
        if (k < val_1) return searchUtil(head->right, val_1);
        return NULL;
    }

    void _to_string(string (*to_str_1)(T1 &), string (*to_str_2)(T2 &), Node *curr, int h, string &result) {
        if (curr != nullptr) {
            _to_string(to_str_1, to_str_2, curr->right, h + 10, result);
            for (int i = 0; i < h; i++) {
                result += " ";
            }
            result += to_str_1(curr->key) + ": ";
            result += curr->chain.to_string(to_str_2);
            result += "\n";
            _to_string(to_str_1, to_str_2, curr->left, h + 10, result);
        }
    }

    void _clear(Node *curr) {
        if (curr == NULL) return;
        _clear(curr->left);
        _clear(curr->right);
        delete curr;
    }

    /**
     * Рекурсивно идёт по дереву и засовывает в result узлы, которые больше val_1
     */
    void _get_nodes_higher(T1 target, Node *curr, vector<Node*>& result) {
        if (curr == NULL) return;
        if (curr->key >= target) {  // Если узел подходит по условие
            this->_get_nodes_higher(target, curr->left, result);
            result.push_back(curr);
            this->_get_nodes_higher(target, curr->right, result);
        } else {
            this->_get_nodes_higher(target, curr->right, result);  // Ничего не делаем с узлом, рассматриваем более правые
        }
    }

    /**
     * Рекурсивно идёт по дереву и засовывает в result все вторые(T2) значения
     */
    void _to_vector_second_value(Node *curr, vector<T2>& result) {
        if (curr == NULL) return;
        _to_vector_second_value(curr->left, result);
        for (T2 value: curr->chain.to_vector()) {
            result.push_back(value);
        }
        _to_vector_second_value(curr->right, result);
    }
};