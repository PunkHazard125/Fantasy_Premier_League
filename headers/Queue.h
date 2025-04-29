#ifndef QUEUE_H
#define QUEUE_H

#include <bits/stdc++.h>
#include "Node.h"

using namespace std;

#define ln "\n"

template <typename T>

class Queue {

private:

    Node<T>* head;
    Node<T>* tail;
    int size;
    const int MAX_QUEUE_SIZE = 1e6;

public:

    Queue() {

        head = nullptr;
        tail = nullptr;
        size = 0;

    }

    Queue(const Queue<T>& other) {

        head = nullptr;
        tail = nullptr;
        size = 0;

        Node<T>* current = other.head;

        while (current != nullptr)
        {
            enqueue(current->data);
            current = current->next;
        }

    }

    Queue<T>& operator=(const Queue<T>& other) {

        if (this != &other)
        {
            clear();

            Node<T>* current = other.head;

            while (current != nullptr)
            {
                enqueue(current->data);
                current = current->next;
            }
        }
        
        return *this;

    }

    ~Queue() {

        Node<T>* current = head;

        while (current != nullptr)
        {
            Node<T>* temp = current;
            current = temp->next;
            delete temp;
        }
        
        head = nullptr;
        tail = nullptr;
        size = 0;

    }

    void enqueue(T value) {

        if (size + 1 > MAX_QUEUE_SIZE)
        {
            throw runtime_error("Queue overflow! Maximum Queue size reached.");
        }

        Node<T>* new_node = new Node<T>(value);

        if (is_empty())
        {
            head = tail = new_node;
            size++;
            return;
        }

        tail->next = new_node;
        tail = new_node;

        size++;

    }

    T dequeue() {

        if (is_empty())
        {
            throw runtime_error("Queue underflow! Queue is empty.");
        }

        Node<T>* current = head;
        T value = current->data;

        head = head->next;
        delete current;

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
            dequeue();
        }
    }

    T peek() {

        if (is_empty())
        {
            throw runtime_error("Queue underflow! Queue is empty.");
        }

        return head->data;

    }

    T back() {

        if (is_empty())
        {
            throw runtime_error("Queue underflow! Queue is empty.");
        }

        return tail->data;

    }

};

#endif
