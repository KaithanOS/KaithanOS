//
// Created by Zhiyang Lu on 23/02/24.
//

#include "Vector.h"
#include <iostream>
#include <vector>

using namespace std;

Vector<int> custom_vector;
vector<int> standard_vector;

void time(void (*func)()) {
    std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
    func();
    std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();

    std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;
}

void custom_push_back() {
    for (int i = 0; i < 8192; i++) {
        custom_vector.push_back(i);
    }
}

void standard_push_back() {
    for (int i = 0; i < 8192; i++) {
        standard_vector.push_back(i);
    }
}

void custom_pop_back() {
    for (int i = 0; i < 4096; i++) {
        custom_vector.pop_back();
    }
}

void standard_pop_back() {
    for (int i = 0; i < 4096; i++) {
        standard_vector.pop_back();
    }
}

void custom_peek_back() {
    for (int i = 0; i < 4096; i++) {
        custom_vector.peek_back();
    }
}

void custom_remove() {
    for (int i = 8191; i >=0; i--) {
        custom_vector.remove(0);
    }
}

void standard_remove() {
    for (int i = 8191; i >=0; i--) {
        standard_vector.erase(standard_vector.begin() + 0);
    }
}

void custom_remove_ptr() {
//    for (int i = 8191; i >=0; i--)
    for (int i = 0; i < 8192; i++){
        custom_vector.remove(&i);
    }
}

void custom_set() {
    for (int i = 0; i < 8192; i++) {
        custom_vector.set(i, 5);
    }
}


int main() {
//    time(custom_push_back);
//    time(standard_push_back);
//
//    time(custom_pop_back);
//    time(standard_pop_back);

    time(custom_push_back);
    time(custom_remove);

    time(standard_push_back);
    time(standard_remove);

    time(custom_push_back);
    time(custom_remove_ptr);

    Vector<int> intvec;
    for (int i = 0; i < 5; i++) {
        intvec.push_back(i);
    }

    intvec.debug();
    cout<<intvec<<"\n";
}
