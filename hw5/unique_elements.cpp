#include <iostream>
#include <set>

int main(){
    std::set<int, std::greater<int>> numbers;
    int countnumb{};
    std::cout << "[IN]:\n";
    std::cin >> countnumb;
    std::cin.ignore();
    int num{};
    for(int i = 0; i < countnumb; i++){
        std::cin >> num;
        std::cin.ignore();
        numbers.insert(num);
    }
    std::cout << "[OUT]:\n";
    for(const int& el : numbers){
        std::cout << el << std::endl;
    }
    return 0;
}