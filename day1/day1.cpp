#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

int main() {
    std::ifstream input( "input1.txt" );
    std::string line;
    uint64_t ret = 0;
    uint64_t current = 0;

    uint64_t first = 0;
    uint64_t second = 0;
    uint64_t third = 0;

    std::vector<int> test;
    while(getline(input, line)) {
        if(line.empty()) {
            ret = std::max(ret, current);
            test.push_back(current);
            
            if(first <= current) {
                third = second;
                second = first;
                first = ret;
            } else if(second <= current) {
                third = second;
                second = current;
            } else if(third <= current) {
                third = current;
            }

            current = 0;
        } else {
            uint64_t t = std::stoull(line);
            current += t;
        }
    }
    
    // part 1 res:
    std::cout << ret << std::endl;

    // part 2:
    std::cout << first << " " << second << " " << third << " " << first + second + third << std::endl;

    // double checking:
    std::sort(test.begin(), test.end(), std::greater<int>());
    int l = test.size();
    std::cout << test[0] << " " << test[1] << " " << test[2] << " " << test[0] + test[1] + test[2] << std::endl;

    return 0;
}