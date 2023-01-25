#include <cassert>
#include <iostream>
#include <memory>

class Fibonacci final {
  public:
      static int get_with_array(int n) {
        assert(n >= 0);
            if (n < 2) {
            return n;
        }
        auto array = std::make_unique<int[]>(n + 1);
        array[0] = 0;
        array[1] = 1;
        for (int i = 2; i < n + 1;i++ ) {
            array[i] = array[i-1] + array[i-2];
        }
        assert(array[n] == get(n));
        return array[n];
      }

      static int get(int n) {
        assert(n >= 0);
        if (n < 2) {
            return n;
        }
        int fib0 = 0;
        int fib1 = 1;
        int fibn;
        for (int i = 2; i < n + 1; i++) {
            fibn = (fib0 + fib1) % 10;
            fib0 = fib1;
            fib1 = fibn;
        }
        return fibn;
      }
};

int main(void) {
    int n;
    std::cin >> n;
    std::cout << Fibonacci::get(n) << std::endl;
    return 0;
}
