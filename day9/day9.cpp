#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <unordered_set>
#include <cstdlib>

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;  
    }
};

bool ifNearby(std::pair<int, int> a, std::pair<int, int> b) {
    return std::abs(a.first - b.first) <= 1 && std::abs(a.second - b.second) <= 1;
}

void move(std::pair<int, int> a, std::pair<int, int>& b) {
        if(std::abs(a.first - b.first) > 1 || std::abs(a.second - b.second) > 1) {
            if(a.first != b.first) b.first += (b.first < a.first ? 1 : -1);
            if(a.second != b.second) b.second += (b.second < a.second ? 1 : -1);
        }
}

int main() {
    std::ifstream input( "input.txt" );
    std::string line;
    auto pt = std::make_pair<int, int>(0, 0);
    auto ph = std::make_pair<int, int>(0, 0);
    std::unordered_set<std::pair<int, int>, pair_hash > visited1;
    visited1.insert(std::make_pair<int, int>(0, 0));
    int part1 = 1;
    int part2 = 1;

    std::vector<std::pair<int, int>> tails(9, std::make_pair<int, int>(0, 0));
    std::unordered_set<std::pair<int, int>, pair_hash > visited2;
    visited2.insert(std::make_pair<int, int>(0, 0));
    while(getline(input, line)) {
        int steps = std::stoi(line.substr(1));
        char dir = line[0];
        std::cout << steps << " " << dir << std::endl;
        while (steps > 0)
        {
            switch (dir)
            {
            case 'L':
                ph.second -= 1;
                break;
            case 'R':
                ph.second += 1;
                break;
            case 'U':
                ph.first += 1;
                break;
            case 'D':
                ph.first -= 1;
                break;
            default:
                break;
            }
            //part 1:
            move(ph, pt);
            if(visited1.find(pt) == visited1.end()) {
                part1++;
                visited1.insert(pt);
            }
            

            // part 2:
            auto knotToCompare = ph;
            for(auto& knot : tails) {
                move(knotToCompare, knot);
                knotToCompare = knot;
                
            }

            if(visited2.find(tails.back()) == visited2.end()) {
                part2++;
                visited2.insert(tails.back());
            }

            steps--;
        }
    }

    for(auto& knot : tails) {
            std::cout << knot.first << " " << knot.second << std::endl;

    }

    std::cout << part1 << std::endl;
    std::cout << part2 << std::endl;
   

    return 0;
}


