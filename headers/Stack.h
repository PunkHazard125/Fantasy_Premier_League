#ifndef STACK_H
#define STACK_H

#include <bits/stdc++.h>
#include "Node.h"

using namespace std;

#define ln "\n"

template <typename T>
class Stack {

private:

    Node<T>* head;
    int size;
    const int MAX_STACK_SIZE = 1e6;

public:

    Stack() {

        head = nullptr;
        size = 0;

    }

    Stack(const Stack<T>& other) {

        head = nullptr;
        size = 0;

        Node<T>* current = other.head;

        while (current != nullptr)
        {
            push(current->data);
            current = current->next;
        }

    }

    Stack<T>& operator=(const Stack<T>& other) {

        if (this != &other)
        {
            clear();

            Node<T>* current = other.head;

            while (current != nullptr)
            {
                push(current->data);
                current = current->next;
            }
        }
        
        return *this;

    }

    ~Stack() {

        Node<T>* current = head;

        while (current != nullptr)
        {
            Node<T>* temp = current;
            current = temp->next;
            delete temp;
        }
        
        head = nullptr;
        size = 0;

    }

    void push(T value) {

        if (size + 1 > MAX_STACK_SIZE)
        {
            throw runtime_error("Stack overflow! Maximum stack size reached.");
        }

        Node<T>* new_node = new Node<T>(value);
        new_node->next = head;
        head = new_node;

        size++;

    }

    T pop() {

        if (size == 0)
        {
            throw runtime_error("Error: Stack underflow! No element to pop.");
        }

        Node<T>* current = head;
        T value = current->data;

        head = head->next;
        delete current;

        size--;

        return value;

    }

    T peek() {

        if (size == 0)
        {
            throw runtime_error("Error: Stack underflow! No element to peek.");
        }

        return head->data;

    }

    int get_size() {

        return size;

    }

    bool is_empty() {

        if (size == 0)
        {
            return true;
        }
        
        return false;

    }

    void clear() {

        while (!is_empty()) 
        {
            pop();
        }
    }

};

#endif
