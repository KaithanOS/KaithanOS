#include "Heap.h"

int main() {
    Heap<int> h;
    h.push(5);
    h.push(2);
    h.push(15);
    h.push(3);
    std::cout << h.poll() << std::endl;
    std::cout << h.poll() << std::endl;
    std::cout << h.poll() << std::endl;
    std::cout << h.poll() << std::endl;
}