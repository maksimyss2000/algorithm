/* required c++ 20. Example:  g++ -std=c++20 1.1.cpp && ./a.out */

#include <iostream>
#include <stack>
#include <string>
#include <map>

int main() {
    bool                 error_close_bracket = false;
    int                  count  = 0; 
    int                  count_last_open = 0;
    char                 current;
    std::string          result = "Success";
    std::stack<char>     buf;
    std::map<char, char> brackets{{'(', ')'},
                                  {'{', '}'},
                                  {'[', ']'},
                                  };
    char last_open_bracket;
    std::string all_braskets;
    for (const auto& elem: brackets) {
        all_braskets += elem.first;
        all_braskets += elem.second;
    }
    while (std::cin >> current) {
        count++;
        if (all_braskets.find(current) == std::string::npos) {   /* it is not a bracket */
            continue;
        }
        if (brackets.contains(current)) {                        /* get an open bracket */
            if(buf.empty()) {
                count_last_open = count;
            }
            buf.push(current);            
        } else {
            if (!buf.empty()) {            /* check the current close bracket and the last open bracket */
                last_open_bracket = buf.top();
                buf.pop();
                if (brackets[last_open_bracket] != current) {
                    result = std::to_string(count);
                    error_close_bracket = true;
                    break;
                }
            } else {                       /* if we get close bracket and we dont have an open bracket, it is  an error */
                result = std::to_string(count);
                error_close_bracket = true;
                break;
            }
        }
    }
    if (!buf.empty() && !error_close_bracket)  {    /* for a handling same example "()({}" -> 3 */
        result = std::to_string(count_last_open);
    }
    std::cout << result << std::endl;
    return 0;
}