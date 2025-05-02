#ifndef DEQUE_H
#define DEQUE_H

#include <bits/stdc++.h>
#include "Node.h"

using namespace std;

template <typename T>

class Deque {

private:

    Node<T>* head;
    Node<T>* tail;
    int size;
    const int MAX_DEQUE_SIZE = 1e6;

public:

    Deque() {

        head = nullptr;
        tail = nullptr;
        size = 0;

    }

    Deque(const Deque<T>& other) {

        head = nullptr;
        tail = nullptr;
        size = 0;

        Node<T>* current = other.head;

        while (current != nullptr)
        {
            push_back(current->data);
            current = current->next;
        }

    }

    Deque<T>& operator=(const Deque<T>& other) {

        if (this != &other)
        {
            clear();

            Node<T>* current = other.head;

            while (current != nullptr)
            {
                push_back(current->data);
                current = current->next;
            }
        }
        
        return *this;

    }

    ~Deque() {

        Node<T>* current = head;

        while (current != nullptr)
        {
            Node<T>* temp = current;
            current = temp->next;
            delete temp;
        }
        
        head = tail = nullptr;
        size = 0;

    }

    void push_front(T value) {

        Node<T>* new_node = new Node<T>(value);

        if (head == nullptr)
        {
            head = tail = new_node;
        }
        else
        {
            new_node->next = head;
            head = new_node;
        }

        size++;

    }

    void push_back(T value) {

        Node<T>* new_node = new Node<T>(value);

        if (head == nullptr)
        {
            head = tail = new_node;
        }
        else
        {
            tail->next = new_node;
            tail = new_node;
        }

        size++;

    }

    T pop_front() {

        if (is_empty())
        {
            throw runtime_error("List is empty!");
        }

        T value = head->data;

        if (size == 1)
        {
            delete head;
            head = tail = nullptr;
            size--;
            return value;
        }

        Node<T>* temp = head;
        head = head->next;

        delete temp;
        size--;

        return value;

    }

    T pop_back() {

        if (is_empty())
        {
            throw runtime_error("List is empty!");
        }

        T value = tail->data;

        if (size == 1)
        {
            delete head;
            head = tail = nullptr;
            size--;
            return value;
        }

        Node<T>* current = head;

        while (current->next != tail)
        {
            current = current->next;
        }
        
        delete tail;
        tail = current;
        tail->next = nullptr;
        size--;

        return value;

    }

    int get_size() {

        return size;

    }

    bool is_empty() {

        return (size == 0);

    }

    void clear() {

        while (!is_empty()) 
        {
            pop_front();
        }
    }

};

#endif
