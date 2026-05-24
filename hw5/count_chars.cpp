#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
int main(){
    std::map<char, int> chars;
    std::string user{};
    std::cout << "[IN]: ";
    getline(std::cin, user);
    for(const char& a : user){
        ++chars[a];
    }
    std::vector<std::pair<char, int>> temp(chars.begin(), chars.end());
    std::sort(temp.begin(), temp.end(), []( const std::pair<char, int>& a,  const std::pair<char, int>& b){
        return a.second > b.second;
    });
    std::cout << "[OUT]:\n";
    for(const std::pair<char, int>& a : temp){
        std::cout << a.first << ": " << a.second << std::endl;
    }
    return 0;
}
