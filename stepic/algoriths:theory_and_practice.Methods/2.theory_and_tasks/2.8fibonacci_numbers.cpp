#include <cassert>
#include <iostream>
#include <memory>
/* Macro is just for fun. It is must be reworked to a function*/
#define START_PERIOD(current, previous) ((current == 1) && (previous == 0))    /* The series always begins with 01 */  
class Fibonacci final {
    public:
        static int get_remainder(uint64_t n, int m) {
            int max_len_series = 6 * m + 1;
            auto array = std::make_unique<uint64_t[]>(max_len_series);
            array[0] = 0;
            array[1] = 1;
            uint64_t previous = array[0];
            uint64_t current  = array[1];
            uint64_t new_current;
            int index;
            for (int i = 2; i < max_len_series;i++ ) {
                new_current = (current + previous) % m;
                previous    = current;
                current     = new_current;
                array[i]    = new_current;
                if (START_PERIOD(array[i],array[i - 1])) { 
                    index = i -1;
                    break;
                }
            }
            return array[n % index];
        }
};

int main(void) {
    uint64_t n;
    int m;
    std::cin >> n >> m;
    std::cout << Fibonacci::get_remainder(n, m) << std::endl;
    return 0;
}