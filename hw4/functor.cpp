#include <iostream>
#include <vector>
template<typename T>
class Functor{

    T get_sum(const std::vector<T>& vec){
        T sum{};
        for(const T& el : vec){
            if(el % 3 == 0)
                sum += el;
        }
        return sum;
    }
    T get_count(const std::vector<T>& vec){
        T count{};
        for(const T& el : vec){
            if(el % 3 == 0)
                count += 1;
        }
        return count;
    }
public:
    void operator()(const std::vector<T>& vec){
        std::cout << "get_sum() = " << get_sum(vec) << std::endl;
        std::cout << "get_count() = " << get_count(vec) << std::endl;
    }
};


int main(int argc, char* argv[]) {
    std::vector<int> vec {4, 1, 3, 6, 25, 54};
    Functor<int> f;
    f(vec);
    return 0;
}