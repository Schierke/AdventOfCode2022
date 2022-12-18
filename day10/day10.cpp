#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <unordered_set>
#include <cstdlib>
#include <queue>


int main() {
    std::ifstream input( "input.txt" );
    std::string line;
    
    int cycle = 0;
    int reg_x = 1;
    int ret1 = 0;
    std::string ret2;
    while(std::getline(input, line))
    {   
        if(std::abs(cycle%40 - reg_x) < 2) {
            ret2 += "#";
        } else {
            ret2 += ".";
        }
        
        if(line == "noop") { 
            cycle++;
            if(cycle%40 == 0 && cycle > 0) {
                ret2 += "\n";
            }
            if((cycle-20)%40 == 0) {  ret1 += cycle * reg_x; }
        } 
        else
        {
            cycle++;
            if((cycle-20)%40 == 0) {  ret1 += cycle * reg_x; }
            if(std::abs(cycle%40 - reg_x) < 2) {
                ret2 += "#";
            } else {
                ret2 += ".";
            }
            if(cycle%40 == 0) {
                ret2 += "\n";
            }
            cycle++;
            if((cycle-20)%40 == 0) {  ret1 += cycle * reg_x; }
            reg_x += std::stoi(line.substr(5));
             if(cycle%40 == 0 && cycle > 0) {
                ret2 += "\n";
            }
        } 
    }

    std::cout << cycle << " " << reg_x << " " << ret1 << std::endl;

    std::cout << ret2;

    return 0;
}


