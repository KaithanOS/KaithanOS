//
// Created by Kailash Gautham on 13/3/24.
//

#ifndef KAITHANOS_HEAP_H
#define KAITHANOS_HEAP_H

#include <stdexcept>
#include <iostream>
#include <cstdio>
#include "Vector.h"
#include <sstream>

// Max heap implementation, custom comparator function supported.

template <typename T>
class Heap {

private:
    Vector<T> heap_array;
    bool (*comparator)(const T&, const T&);
    static bool default_less(const T& a, const T& b) { return a < b; }
    static bool default_greater(const T& a, const T& b) { return a > b; }

public:
    static Heap heapify(Vector<T> vector) {
        Heap<T> newHeap;
        for (T& i : vector) {
            newHeap.push(i);
        }
        return newHeap;
    }

    // Custom constructors and destructors
    Heap() : comparator(default_greater) {
        heap_array = Vector<T>(1, T{});
    }

    explicit Heap(bool isMaxHeap) : comparator(isMaxHeap ? default_greater : default_less) {
        heap_array = Vector<T>(1, T{});
    }

    explicit Heap(bool (*customComparator)(const T&, const T&)) : comparator(customComparator) {
        heap_array = Vector<T>(1, T{});
    }

    // Accessors

    int size() {
        return heap_array.size() - 1;
    }

    bool empty() {
        return heap_array.size() == 1;
    }

    T& peek() {
        if (empty()) {
            throw runtime_error("Index out of bounds");
        } else {
            return heap_array[1];
        }
    }

    T poll() {
        if (empty()) {
            throw runtime_error("Index out of bounds");
        } else {
            T polledValue = heap_array[1];
            heap_array[1] = heap_array[size()];
            heap_array.pop_back();
            bubble_down(1);
            return polledValue;
        }
    }

    void bubble_down(int root) {

        if (root > size()) return;
        int left_child = root * 2;
        int right_child = left_child + 1;
        if (left_child > size() && right_child > size()) return;

        if ((left_child <= size() && !comparator(heap_array[root], heap_array[left_child])) ||
        (right_child <= size() && !comparator(heap_array[root], heap_array[right_child]))) {
            if (right_child > size() || (left_child <= size() && comparator(heap_array[left_child], heap_array[right_child]))) {
                T& temp = heap_array[left_child];
                heap_array[left_child] = heap_array[root];
                heap_array[root] = temp;
                bubble_down(left_child);
            }
            if (left_child > size() || (right_child <= size() && comparator(heap_array[right_child], heap_array[left_child]))) {
                T& temp = heap_array[right_child];
                heap_array[right_child] = heap_array[root];
                heap_array[root] = temp;
                bubble_down(right_child);
            }
        }
    }

    void bubble_up(int position) {
        int parent = position / 2;
        if (parent >= 1 && parent != position) {
            if (comparator(heap_array[position], heap_array[parent])) {
                swap(heap_array[position], heap_array[parent]);
                bubble_up(parent);
            }
        }
    }

    void push(const T& val) {
        heap_array.push_back(val);
        bubble_up(size());
    }
};

#endif //KAITHANOS_HEAP_H
