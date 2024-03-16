//
// Created by Zhiyang Lu on 15/03/24.
//

#ifndef KAITHANOS_PAIR_H
#define KAITHANOS_PAIR_H

#include <stdexcept>
#include <iostream>
#include <stdio.h>
#include <sstream>

using namespace std;

template<typename T, typename U>
class Pair {
private:
    T first;
    U second;

public:

    // Constructors and destructors

    Pair() : first(), second() {}

    Pair(const T& f, const U& s) : first(f), second(s) {}

    Pair(const Pair<T, U>& pair) {
        T first_copy(pair.first);
        U second_copy(pair.second);
        first = first_copy;
        second = second_copy;
    }

    // Accessors

    T& get_first() {
        return first;
    }

    U& get_second() {
        return second;
    }

    void set_first(T& f) {
        first = f;
    }

    void set_second(U& s) {
        second = s;
    }

    // Override operators

    friend ostream& operator<<(ostream& os, Pair<T, U>& pair) {
        os << "{" << pair.first << ", " << pair.second << "}";
        return os;
    }

    bool operator==(const Pair<T, U>& pair) const {
        return first == pair.first && second == pair.second;
    }

};


#endif //KAITHANOS_PAIR_H
