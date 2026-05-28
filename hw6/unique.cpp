#include <vector>
#include <iostream>
#include <algorithm>

void unique_vec(std::vector<int>& vec){
    auto it = std::unique(vec.begin(), vec.end());
    vec.erase(it, vec.end());
}


int main() {
    std::vector<int> vec{ 1, 1, 2, 5, 6, 1, 2, 4};
    std::cout << "[IN]: ";
    for(const int& el : vec){
        std::cout << el << " ";
    }
    std::sort(vec.begin(), vec.end());
    std::cout << std::endl;
    unique_vec(vec);
    std::cout << "[OUT]: ";
    for(const int& el : vec){
        std::cout << el << " ";
    }
    return 0;

}