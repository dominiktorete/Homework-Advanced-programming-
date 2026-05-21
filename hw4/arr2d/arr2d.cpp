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

    table& operator = (const table& other){
        if(this == &other)return *this;
        if(arr2d != nullptr){
            delete[] arr2d;
        }
        cols = other.cols;
        rows = other.rows;
        arr2d = new T[rows*cols];
        for(int i = 0; i < rows*cols; ++i){
            arr2d[i] = other.arr2d[i];
        }
        return *this;
    }
    table(const table& other){
        if(this == &other) return;
        if(arr2d != nullptr){
            delete[] arr2d;
        }
        cols = other.cols;
        rows = other.rows;
        arr2d = new T[rows*cols];
        for(int i = 0; i < rows*cols; ++i){
            arr2d[i] = other.arr2d[i];
        }
    }
    table(int _rows, int _cols) : rows(_rows), cols(_cols){
        if(rows > 0 && cols > 0){
            arr2d = new T[rows*cols];
        }
        else {
            throw std::invalid_argument("Incorrect values rows and cols!!!");
        }
    }
    std::pair<int, int> size(){
        return std::pair<int, int>(rows, cols);
    }

    ~table(){
        delete[] arr2d;
    }
};


using TESTCLASS = table<int>;

TEST_CASE("check TZ nonconst")
{
    auto t1 = TESTCLASS(2, 3);
    t1[0][0] = 4;
    CHECK(t1[0][0] == 4);
}

TEST_CASE("check TZ const")
{
    auto t1 = TESTCLASS(2, 3);
    t1[0][0] = 4;
    const auto& table_c = t1;
    CHECK(table_c[0][0] == 4);
}

TEST_CASE("check big three operator =")
{
    auto t1 = TESTCLASS(2, 3);
    auto t2 = t1;
}

TEST_CASE("check big three copy ctor")
{
    auto t1 = TESTCLASS(2, 3);
    auto t2(t1);
}

int main(int argc, char* argv[]) {
    auto test = table<int>(2, 3);
    test[0][0] = 4;
    std::cout << test[0][0] << std::endl;

    return Catch::Session().run(argc, argv);
}
