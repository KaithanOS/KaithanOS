//
// Created by Kailash Gautham on 13/3/24.
//

#ifndef KAITHANOS_HEAP_H
#define KAITHANOS_HEAP_H

#include <stdexcept>
#include <iostream>
#include <cstdio>
#include <Vector.h>
#include <sstream>

template <typename T>
class Heap {

private:
    Vector<T> heap;

public:

    // Custom constructors and destructors
    Heap() {
        heap = Vector<T> {};
    }

    ~Heap() {
        delete heap;
    }

    // Accessors

    int size() {
        return heap.size();
    }





};

#endif //KAITHANOS_HEAP_H
