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


//int main() {
////    time(custom_push_back);
////    time(standard_push_back);
////
////    time(custom_pop_back);
////    time(standard_pop_back);
//
////    time(custom_push_back);
////    time(custom_remove);
//
////    time(standard_push_back);
////    time(standard_remove);
////
////    time(custom_push_back);
////    time(custom_remove_ptr);
//
<<<<<<< HEAD
    cout << intvec << "\n";
=======
//    Vector<int> intvec;
//    for (int i = 0; i < 5; i++) {
//        intvec.push_back(i);
//    }
////    intvec.push_back(1);
////    intvec.push_back(2);
////    intvec.push_back(3);
////    intvec.push_back(4);
>>>>>>> 59109f65d9bce2e774daac0596160516c384f97b
//
//    for (int i : intvec) {
//        cout << i << "\n";
//    }
////
////    cout << intvec[2] << "\n";
////
////    intvec.debug();
////    cout<<intvec<<"\n";
////
////    intvec.push_front(5);
////    intvec.push_front(6);
////    intvec.push_front(7);
////    intvec.push_front(8);
////
////    intvec.debug();
////    cout<<intvec<<"\n";
////
////    intvec.pop_back();
////    intvec.pop_back();
////    intvec.pop_back();
////    intvec.pop_back();
////    intvec.pop_back();
////
////    intvec.debug();
////    cout<<intvec<<"\n";
////
////    Vector<int> intvec2;
////    intvec2.push_back(8);
////    intvec2.push_back(7);
////    intvec2.push_back(6);
////
////    cout<<(intvec==intvec2)<<"\n";
//
////    Vector<int> vec2(intvec);
////    cout<<vec2<<"\n";
////    intvec.pop_front();
////    intvec.debug();
////    cout<<intvec.pop_front()<<"\n";
//
////
////    Vector<int> intvec2;
////    intvec2.push_back(2);
////    intvec2.push_back(3);
////    intvec2.push_back(4);
////
////    cout<<(intvec==intvec2)<<"\n";
////
////    intvec.debug();
////    intvec2.debug();
////
////    cout<<intvec<<"\n";
////    int num = 2;
////    int* intptr = &num;
////    cout<<intvec.remove(intptr)<<"\n";
////    cout<<intvec<<"\n";
////    intvec.push_front(5);
////    intvec.push_front(6);
////    intvec.push_front(7);
////    cout<<intvec<<"\n";
////    intvec.pop_front();
////    cout<<intvec<<"\n";
////    intvec.pop_front();
////    cout<<intvec<<"\n";
////    cout<<intvec.poll_front()<<"\n";
////    cout<<intvec<<"\n";
//
//
////    Vector<string> stringvec;
////    stringvec.push_back("abc");
////    stringvec.push_back("a");
////    stringvec.push_back("b");
////    stringvec.push_back("c");
////    cout<<stringvec<<"\n";
////    string str = "abc";
////    string* strptr = &str;
////    cout<<stringvec.remove(strptr)<<"\n";
////    cout<<stringvec<<"\n";
//
//}
