#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <iostream>
template<typename T>
void power(T& numb){
    numb *= numb;
}
template<typename T>
void power(std::vector<T>& vec){
    for(T& element : vec){
        element *= element;
    }
}

TEST_CASE("Testtempfunc") {
    SECTION("Number") {
        int num = 5;
        power(num);
        CHECK(num == 25);
    }
    SECTION("Vec numbers") {
        std::vector<int> vec{1,2,3,4,5};
        power(vec);
        std::vector<int> vec2{1,4,9,16,25};
        CHECK(vec == vec2);
    }
}

int main(int argc, char* argv[]) {

    int n = 21;
    power(n);
    std::cout << n << std::endl;
    std::vector<int> vec{-1, 4, 8};
    power(vec);
    for(const int& element : vec){
        std::cout << element << " ";
    }
    //return Catch::Session().run(argc, argv);
    return 0;
}