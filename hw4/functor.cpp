#include <iostream>
#include <vector>
#include <algorithm>
class Functor{
    int sum{};
    int count{};
public:
    int get_sum(){
        return sum;
    }
    int get_count(){
        return count;
    }
    void operator()(int num){
        if(num % 3 == 0){
            ++count;
            sum+=num;
        }
    }
};

int main(int argc, char* argv[]) {
    std::vector<int> numbers = { 4, 1, 3, 6, 25, 54 };
    Functor counter = std::for_each(numbers.begin(), numbers.end(), Functor());
    std::cout << "[OUT]: get_sum() = " << counter.get_sum() << std::endl;
    std::cout << "[OUT]: get_count() = " << counter.get_count() << std::endl;
    return 0;
}
