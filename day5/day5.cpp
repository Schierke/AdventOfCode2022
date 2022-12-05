#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <sstream>

std::string solver1(std::vector<std::vector<char> >&& crates, std::vector<std::string>&& sec2) {
    for(auto ins : sec2) {
        std::stringstream ss(ins);
        std::string temp;
        int found;
        std::vector<int> zz;

        while(!ss.eof()) {
            ss>> temp;
            if (std::stringstream(temp) >> found) {
                zz.push_back(found);
            }
        }
        
        int nbCrate = zz[0];
        int from = zz[1] - 1;
        int to = zz[2] - 1;
        std::cout<<nbCrate << " "<<from<< " " <<to << " "; 
        while(nbCrate > 0 && !crates[from].empty()) {
            std::cout<<crates[from].back();
            crates[to].push_back(crates[from].back());
            crates[from].pop_back();
            nbCrate--;
        }
        std::cout<<std::endl;
    }

    std::string ret;
    for(auto crate : crates) {
        if(!crate.empty()) {
            ret += crate.back();
        }
        
    }

    return ret;
}

std::string solver2(std::vector<std::vector<char> >&& crates, std::vector<std::string>&& sec2) {
    for(auto ins : sec2) {
        std::stringstream ss(ins);
        std::string temp;
        int found;
        std::vector<int> zz;

        while(!ss.eof()) {
            ss>> temp;
            if (std::stringstream(temp) >> found) {
                zz.push_back(found);
            }
        }
        
        int nbCrate = zz[0];
        int from = zz[1] - 1;
        int to = zz[2] - 1;
        if(nbCrate < crates[from].size() ) {
            crates[to].insert(crates[to].end(), crates[from].end() - nbCrate, crates[from].end());
            crates[from].erase(crates[from].end() - nbCrate, crates[from].end());
        } else {
            crates[to].insert(crates[to].end(), crates[from].begin(), crates[from].end());
            crates[from].clear();
        }
        
        for(auto i : crates[to]) {
            std::cout<<i;
        }
        std::cout<<std::endl;
    }

    std::string ret;
    for(auto crate : crates) {
        if(!crate.empty()) {
            ret += crate.back();
        }
        
    }

    return ret;
}

int main() {
    std::ifstream input( "input.txt" );
    std::string line;

    std::vector<std::string> sec1;
    std::vector<std::string> sec2;
    int nbCrate = 0;
    while(getline(input, line)) {
        auto pos = line.find_first_not_of(' ');
        if(line[pos] == '[') {
            sec1.push_back(line);
        } else if(line[pos] == 'm') {
            sec2.push_back(line);
        } else {
            nbCrate = 9;
        }          
    }
    
    std::vector<std::vector<char> > crates(nbCrate, std::vector<char>());
    
    for(auto i = sec1.rbegin(); i != sec1.rend(); i++) {
        line = *i;
        int idx = 0;
        while(idx < nbCrate) {
            char c = line[idx*4+1];
            if(c!=' ') {
                crates[idx].push_back(c);
            }
            
            idx++;
        }
    }

    std::string p1 = solver2(std::move(crates), std::move(sec2));
    std::cout << p1 << std::endl;
    return 0;
}

