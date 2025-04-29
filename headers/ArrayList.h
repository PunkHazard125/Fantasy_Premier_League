#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <bits/stdc++.h>

using namespace std;

#define ln "\n"

template <typename T>

class ArrayList {

private:

    T* array;
    int size;
    int capacity;
    const int64_t MAX_ARRAY_CAPACITY = 1e6;

    void merge(int left, int mid, int right, bool descending) {

        int n1 = mid - left + 1;
        int n2 = right - mid;

        T* L = new T[n1];
        T* R = new T[n2];

        for (int i = 0; i < n1; i++)
        {
            L[i] = array[left + i];
        }
        
        for (int i = 0; i < n2; i++)
        {
            R[i] = array[mid + 1 + i];
        }

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2)
        {
            if (descending ? (L[i] >= R[j]) : (L[i] <= R[j]))
            {
                array[k] = L[i];
                i++;
            }
            else
            {
                array[k] = R[j];
                j++;
            }
            
            k++;
        }
        
        while (i < n1) 
        {
            array[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) 
        {
            array[k] = R[j];
            j++;
            k++;
        }

        delete[] L;
        delete[] R;

    }

    void merge_sort(int left, int right, bool descending) {

        if (left >= right)
        {
            return;
        }
        
        int mid = left + (right - left) / 2;

        merge_sort(left, mid, descending);
        merge_sort(mid + 1, right, descending);
        merge(left, mid, right, descending);

    }

    void manage_capacity() {

        if (size < capacity / 4) 
        {
            if (capacity / 2 < 8)
            {
                return;
            }

            capacity /= 2;
            T* temp = new T[capacity];
    
            for (int i = 0; i < size; i++) 
            {
                temp[i] = array[i];
            }
    
            delete[] array;
            array = temp;
        }

    }

public:

    ArrayList() {

        capacity = 8;
        size = 0;
        array = new T[8];

    }

    ArrayList(int capacity) {

        if (capacity > MAX_ARRAY_CAPACITY)
        {
            throw runtime_error("Maximum capacity exceeded!\n");
        }

        if (capacity < 8)
        {
            throw runtime_error("Cannot have below minimum capacity!\n");
        }

        this->capacity = capacity;
        this->size = 0;
        array = new T[capacity];

    }

    ArrayList<T>& operator=(const ArrayList<T>& other) {

        if (this != &other)
        {
            delete[] array;
            
            capacity = other.capacity;
            size = other.size;

            array = new T[capacity];

            for (int i = 0; i < size; i++)
            {
                array[i] = other.array[i];
            }
        }
        
        return *this;

    }

    ~ArrayList() {

        size = 0;
        capacity = 0;
        delete[] array;

    }

    void push_back(T element) {

        if (size + 1 >= capacity)
        {
            if (capacity * 2 > MAX_ARRAY_CAPACITY) 
            {
                throw runtime_error("Max array capacity exceeded!\n");
            }

            capacity = capacity * 2;

            T* temp = new T[capacity];

            for (int i = 0; i < size; i++)
            {
                temp[i] = array[i];
            }

            delete[] array;
            array = temp;
        }

        array[size++] = element;

    }

    void push_front(T element) {

        if (size + 1 >= capacity)
        {
            if (capacity * 2 > MAX_ARRAY_CAPACITY) 
            {
                throw runtime_error("Max array capacity exceeded!\n");
            }
            capacity = capacity * 2;
        }

        T* temp = new T[capacity];

        for (int i = 1; i < size + 1; i++)
        {
            temp[i] = array[i - 1];
        }

        delete[] array;
        array = temp;
        array[0] = element;
        size++;

    }

    void insert(int position, T element) {

        if (position < 0 || position >= size)
        {
            throw runtime_error("Index out of bounds!\n");
        }

        if (size + 1 >= capacity)
        {
            if (capacity * 2 > MAX_ARRAY_CAPACITY) 
            {
                throw runtime_error("Max array capacity exceeded!\n");
            }
            capacity = capacity * 2;
        }

        T* temp = new T[capacity];
        bool flag = false;

        for (int i = 0; i < size + 1; i++)
        {
            if (i == position)
            {
                temp[i] = element;
                flag = true;
            }
            
            if (flag)
            {
                temp[i] = array[i - 1];
            }
            else
            {
                temp[i] = array[i];
            }
        }

        delete[] array;
        array = temp;
        size++;

    }

    bool contains(T element) {

        for (int i = 0; i < size; i++)
        {
            if (array[i] == element)
            {
                return true;
            }
        }

        return false;

    }

    int get_size() {

        return size;

    }

    int get_capacity() {

        return capacity;

    }

    bool is_empty() {

        return (size == 0);

    }

    T get(int position) {

        if (position < 0 || position >= size)
        {
            throw runtime_error("Index out of bounds!\n");
        }
        
        return array[position];

    }

    int index_of(T element) {
        
        for (int i = 0; i < size; i++)
        {
            if (array[i] == element)
            {
                return i;
            }
        }

        return -1;

    }

    void pop_front() {

        if (size == 0)
        {
            throw runtime_error("Array is empty!\n");
        }

        for (int i = 0; i < size - 1; i++)
        {
            array[i] = array[i + 1];
        }

        size--;

        manage_capacity();

    }

    void pop_back() {

        if (size == 0)
        {
            throw runtime_error("Array is empty!\n");
        }

        size--;

        manage_capacity();

    }

    void remove(int position) {

        if (size == 0)
        {
            throw runtime_error("Array is empty!\n");
        }

        if (position < 0 || position >= size)
        {
            throw runtime_error("Index out of bounds!\n");
        }

        for (int i = position; i < size - 1; i++)
        {
            array[i] = array[i + 1];
        }

        size--;

        manage_capacity();

    }

    void reverse() {

        T* temp = new T[capacity];
        int j = size - 1;
    
        for (int i = 0; i < size; i++) {
            temp[i] = array[j];
            j--;
        }
    
        delete[] array;
        array = temp;

    }

    void sort(bool descending = false) {

        if (size > 1)
        {
            merge_sort(0, size - 1, descending);
        }

    }

    T& operator[](int index) {

        if (index < 0 || index >= size)
        {
            throw runtime_error("Index out of bounds!\n");
        }

        return array[index];

    }

};

#endif
