#ifndef NODE_H
#define NODE_H

#include <bits/stdc++.h>

using namespace std;

#define ln "\n"

template <typename T>

class Node {

public:

    T data;
    Node* next;

    Node(T value) {

        data = value;
        next = nullptr;

    }

};

#endif
