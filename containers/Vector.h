//
// Created by Zhiyang Lu on 23/02/24.
//

#ifndef KAITHANOS_VECTOR_H
#define KAITHANOS_VECTOR_H

#include <stdexcept>
#include <iostream>
#include <stdio.h>
#include <sstream>
using namespace std;

template <typename T>
class Vector {
private:
    T* vector;
    int start;
    int curr_len;
    int max_len;

public:

    // Constructors

    Vector() {
        start = 0;
        curr_len = 0;
        vector = new T[16];
        max_len = 16;
    }

    Vector(int size, T val) {
        start = 0;
        curr_len = size;
        max_len = 1;
        while (max_len < size) {
            max_len *= 2;
        }
        vector = new T[max_len];
        for (int i = 0; i < size; i++) {
            vector[i] = val;
        }
    }

    Vector(Vector<T>& v) {
        start = 0;
        curr_len = v.curr_len;
        max_len = v.max_len;
        vector = new T[max_len];
        for (int i = 0; i < curr_len; i++) {
            vector[i] = v.vector[(start + i) % v.max_len];
        }
    }

    // Accessors

    int size() {
        return curr_len;
    }

    bool empty() {
        return curr_len == 0;
    }

    T get(int i) {
        if (i < 0 || i >= curr_len) {
            throw runtime_error("Index out of bounds");
        } else {
            return vector[(start + i) % max_len];
        }
    }

    // Modifiers

    void resize(int i) {
        if (i < curr_len) {
            throw runtime_error("Invalid resizing");
        }
        T* new_vector = new T[i];
        for (int i = 0; i < curr_len; i++) {
            new_vector[i] = vector[(start + i) % max_len];
        }
        delete[] vector;
        vector = new_vector;
        max_len = i;
        start = 0;
    }

    T remove(int index) {
        T result = get(index);
        for (int i = index; i < curr_len - 1; i++) {
            vector[(start + i) % max_len] = vector[(start + i + 1) % max_len];
        }
        curr_len--;
        return result;
    }

    bool remove(T* elem) {
        bool result = false;
        for (int i = 0; i < curr_len; i++) {
            if (result) {
                vector[(start + i - 1) % max_len] = vector[(start + i) % max_len];
            } else if (vector[(start + i) % max_len] == *elem) {
                result = true;
            }
        }
        if (result) {
            curr_len--;
        }
        return result;
    }

    // Push & pop

    void push_back(T elem) {
        if (curr_len + 1 > (3 * max_len) / 4) {
            resize(max_len * 2);
        }
        vector[(start + curr_len) % max_len] = elem;
        curr_len++;
    }

    T pop_back() {
        if (curr_len <= 0) {
            throw runtime_error("Popping from empty vector");
        }
        if (max_len > 16 && curr_len - 1 < max_len / 4) {
            resize(max_len / 2);
        }
        T result = vector[start + curr_len - 1];
        curr_len--;
        return result;
    }

    T peek_back() {
        if (curr_len <= 0) {
            throw runtime_error("Polling from empty vector");
        } else {
            return vector[(start + curr_len - 1) % max_len];
        }
    }

    void push_front (T elem) {
        if (curr_len + 1 > (3 * max_len) / 4) {
            resize(max_len * 2);
        }
        start = start != 0 ? start - 1 : max_len - 1;
        vector[start] = elem;
        curr_len++;
    }

    T pop_front() {
        if (curr_len <= 0) {
            throw runtime_error("Popping from empty vector");
        }
        if (max_len > 16 && curr_len - 1 < max_len / 4) {
            resize(max_len / 2);
        }
        T result = vector[start];
        start = start != max_len - 1 ? start + 1 : 0;
        curr_len--;
        return result;
    }

    T peek_front() {
        if (curr_len <= 0) {
            throw runtime_error("Polling from empty vector");
        } else {
            return vector[start];
        }
    }

    // Override operators

    friend ostream& operator<<(ostream& os, Vector<T>& vec) {
        if (vec.curr_len == 0) {
            return os << "[]";
        }
        os << "[" << vec.vector[vec.start];
        for (int i = 1; i < vec.curr_len; i++) {
            os << ", " << vec.vector[(vec.start + i) % vec.max_len];
        }
        os << "]";
        return os;
    }

    bool operator==(const Vector<T>& vec) const {
        if (curr_len != vec.curr_len) {
            return false;
        } else {
            for (int i = 0; i < curr_len; i++) {
                if (vector[(start + i) % max_len] != vec.vector[(vec.start + i) % vec.max_len]) {
                    return false;
                }
            }
            return true;
        }
    }

    // Debugging output

    void debug() {
        cout << "start: " << start << "\n";
        cout << "curr_len: " << curr_len << "\n";
        cout << "max_len: " << max_len << "\n";
    }
};

#endif //KAITHANOS_VECTOR_H