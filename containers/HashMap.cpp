//
// Created by Zhiyang Lu on 23/02/24.
//

#include "HashSet.h"
#include <iostream>
#include <unordered_set>

using namespace std;

HashSet<int> custom_hashset;
unordered_set<int> standard_hashset;

void time(void (*func)()) {
    std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
    func();
    std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();

    std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;
}

void custom_add() {
    for (int i = 0; i < 8192; i++) {
        custom_hashset.add(i);
    }
}

void standard_add() {
    for (int i = 0; i < 8192; i++) {
        standard_hashset.insert(i);
    }
}

void custom_remove() {
    for (int i = 0; i < 4096; i++) {
        custom_hashset.remove(i);
    }
}

void standard_remove() {
    for (int i = 0; i < 4096; i++) {
        standard_hashset.erase(i);
    }
}



int main() {
    time(custom_add);
    time(standard_add);
    time(custom_remove);
    time(standard_remove);
    cout << custom_hashset.size();
}
