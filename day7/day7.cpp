#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <cctype>

// let's build a tree dir!
struct Dir {
    Dir() {
        totalSize = 0;
        parent = nullptr;
    };
    Dir(std::string dirName) : dirName(dirName), totalSize(0), parent(nullptr){};
    std::string dirName;
    std::unordered_map<std::string, std::shared_ptr<Dir> > children;
    std::shared_ptr<Dir> parent;
    std::vector<int> files;
    int totalSize;
};

int part1 = 0;
int part2 = INT32_MAX;
constexpr int maxSize = 70000000;
constexpr int unused = 30000000;


void postOrder(std::shared_ptr<Dir> node) {
    if(node == nullptr) {
        return;
    }

    for(auto const& [childName, child] : node->children) {
        postOrder(child);
    }

    for(auto const& [childName, child] : node->children) {
        node->totalSize += child->totalSize;
    }

    if(node->totalSize <= 100000) {
        part1 += node->totalSize;
    }
}

void inOrder(std::shared_ptr<Dir> node, int size) {
    if(node->totalSize < size) {
        return;
    }
    part2 = std::min(node->totalSize, part2);

    for(auto const& [childName, child] : node->children) {
        inOrder(child, size);
    }

}

int main() {
    std::ifstream input( "input.txt" );
    std::string line;

    auto root = std::make_shared<Dir>("/");
    auto current = root;

    bool isls = false;
    while (std::getline(input, line))
    {
        if (line == "$ cd /") {
            current = root;
        }

        if (line.rfind("dir", 0) == 0) { 
            std::string dirName = line.substr(4);
            // s starts with prefix
            auto newDir = std::make_shared<Dir>(dirName);
            current->children[dirName] = newDir;
            newDir->parent = current;
        }

        if(isdigit(line[0])) {
            int fileSize = std::stoi(line);
            current->files.push_back(fileSize);
            current->totalSize += fileSize;
        }

        if(line.rfind("$ cd", 0) == 0 && line.back() != '/') {
            std::string folder = line.substr(line.rfind(" ") + 1);

            if(folder == "..") {
                if(current->parent != nullptr) {
                    current = current->parent;
                }
            } else {
                auto child = current->children[folder];
                current = child;
            }
        }
    }


    // now simple postorder traversal:
    current = root;
    postOrder(current);
    current = root;
    // now preOrder
    int size = root->totalSize + unused - maxSize;
    inOrder(current, size);

    
    std::cout << part1 << std::endl;
    std::cout << part2 << std::endl;

}
