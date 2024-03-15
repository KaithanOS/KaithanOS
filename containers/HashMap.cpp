//
// Created by Zhiyang Lu on 15/03/24.
//

#include "HashMap.h"
#include <iostream>
#include <unordered_map>

using namespace std;

HashMap<int, string> custom_hashmap;
unordered_map<int, string> standard_hashmap;

void time(void (*func)()) {
    std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
    func();
    std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();

    std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;
}

void custom_add() {
    for (int i = 0; i < 2048; i++) {
        custom_hashmap.put(i, "hello");
    }
}

void standard_add() {
    for (int i = 0; i < 2048; i++) {
        standard_hashmap[i] = "hello";
    }
}

void custom_remove() {
    for (int i = 0; i < 1024; i++) {
        custom_hashmap.remove(i);
    }
}

void standard_remove() {
    for (int i = 0; i < 1024; i++) {
        standard_hashmap.erase(i);
    }
}



int main() {
    time(custom_add);
    time(standard_add);
    time(custom_remove);
    time(standard_remove);
//    cout << custom_hashmap << "\n";
    cout << custom_hashmap[1900] << "\n";
}
