#include <cassert>
#include <cstdint>
#include <iostream>

template <class Int>
Int gcd(Int a, Int b) {
    assert(a > 0 && b > 0);
    // optimize this function
    while (a != 0 && b != 0) {
        if (a >= b) {
            a = a % b;
        } else {
            b = b % a;
        } 
    }
    if (a == 0) return b;
    if (b == 0) return a;
    //return a + b;
}

int main(void) {
    std::int32_t a, b;
    std::cin >> a >> b;
    std::cout << gcd(a, b) << std::endl;
    return 0;
}