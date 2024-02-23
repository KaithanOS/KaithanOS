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


int main() {
    time(custom_push_back);
    time(standard_push_back);

    time(custom_pop_back);
    time(standard_pop_back);

//    Vector<int> intvec;
//    intvec.push_back(1);
//    intvec.push_back(2);
//    intvec.push_back(3);
//    intvec.push_back(4);
//    intvec.pop_front();
//    intvec.debug();
//    cout<<intvec.get(0)<<"\n";

//
//    Vector<int> intvec2;
//    intvec2.push_back(2);
//    intvec2.push_back(3);
//    intvec2.push_back(4);
//
//    cout<<(intvec==intvec2)<<"\n";
//
//    intvec.debug();
//    intvec2.debug();
//
//    cout<<intvec<<"\n";
//    int num = 1;
//    int* intptr = &num;
//    cout<<intvec.remove(intptr)<<"\n";
//    cout<<intvec.pop_back()<<"\n";
//    cout<<intvec<<"\n";
//    intvec.push_front(5);
//    intvec.push_front(6);
//    intvec.push_front(7);
//    cout<<intvec<<"\n";
//    intvec.pop_front();
//    cout<<intvec<<"\n";
//    intvec.pop_front();
//    cout<<intvec<<"\n";
//    cout<<intvec.poll_front()<<"\n";
//    cout<<intvec<<"\n";


//    Vector<string> stringvec;
//    stringvec.push_back("abc");
//    stringvec.push_back("a");
//    stringvec.push_back("b");
//    stringvec.push_back("c");
//    cout<<stringvec<<"\n";
//    string str = "abc";
//    string* strptr = &str;
//    cout<<stringvec.remove(strptr)<<"\n";
//    cout<<stringvec<<"\n";

}
