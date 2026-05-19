#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <exception>

template<typename T>
class table{
private:
    T* arr2d{};
    int rows{}, cols{};
public:
    class Arr{
    private:
        T* arr{};
        int size{};
    public:
        Arr(T* _arr, int _size) : arr(_arr), size(_size){}
        T& operator [](int index){
            if(index < size){
                return arr[index];
            }
            else throw std::out_of_range("Error: incorrect index!!!");
        }
        const T& operator [](int index) const{
            if(index < size){
                return arr[index];
            }
            else throw std::out_of_range("Error: incorrect index!!!");
        }
        friend std::ostream& operator << (std::ostream& out, const Arr& obj){
            out << obj.arr;
            return out;
        }
    };
    table(int _rows, int _cols) : rows(_rows), cols(_cols){
        if(rows > 0 && cols > 0){
            arr2d = new T[rows*cols];
        }
        else {
            throw std::invalid_argument("Incorrect values rows and cols!!!");
        }
    }
    Arr operator [](int index){
        if(index < rows){
            return Arr(arr2d + index * cols, cols);
        }
        else throw std::out_of_range("Error: incorrect index!!!");
    }
    const Arr operator [](int index) const{
        if(index < rows){
            return Arr(arr2d + index * cols, cols);
        }
        else throw std::out_of_range("Error: incorrect index!!!");
    }
    std::pair<int, int> size(){
        return std::pair<int, int>(rows, cols);
    }

    ~table(){
        delete[] arr2d;
    }
};


TEST_CASE("TestArr2d") {
    SECTION("Size") {
        table<int> test(3, 5);
        CHECK_THROWS_AS(test[3][4], std::out_of_range);
        CHECK_THROWS_AS(test[2][5], std::out_of_range);
        CHECK(test.size() == std::pair<int, int>(3, 5));
    }
    SECTION("Value") {
        table<int> test(3, 5);
        test[2][3] = 3;
        CHECK(test[2][3] == 3);
    }
}

int main(int argc, char* argv[]) {
    auto test = table<int>(2, 3);
    test[0][0] = 4;
    std::cout << test[0][0] << std::endl;
    return Catch::Session().run(argc, argv);
}