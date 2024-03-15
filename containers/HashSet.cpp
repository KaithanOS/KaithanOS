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
    for (int i = 0; i < 2048; i++) {
        custom_hashset.add(i);
    }
}

void standard_add() {
    for (int i = 0; i < 2048; i++) {
        standard_hashset.insert(i);
    }
}

void custom_remove() {
    for (int i = 0; i < 1024; i++) {
        custom_hashset.remove(i);
    }
}

void standard_remove() {
    for (int i = 0; i < 1024; i++) {
        standard_hashset.erase(i);
    }
}



int main() {
    time(custom_add);
    time(standard_add);
    time(custom_remove);
    time(standard_remove);
//    cout << custom_hashset << "\n";

    HashSet<int> set1;
    set1.add(1);
    set1.add(2);
    set1.add(3);
    set1.add(3);

    HashSet<int> set2;
    set2.add(3);
    set2.add(1);
    set2.add(2);
    set2.add(2);

//    cout << (set1 == set2) << "\n";
}
