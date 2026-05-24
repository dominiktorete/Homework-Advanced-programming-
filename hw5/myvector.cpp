#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
template<typename T>
class Vector{
private:
    T* arr{};
    int size{};
    int capacity{};
public:
    Vector(){
        capacity = 10;
        arr = new T[capacity];
        size = 0;
    };
    Vector(int _capacity){
        if(_capacity >= 0){
            capacity = _capacity;
            arr = new T[capacity];
            size = 0;
        }
        else {
            throw std::invalid_argument("The capacity must be greater or equal zero");
        }
    };
    Vector(std::initializer_list<T> ls){
        capacity = ls.size() * 2;
        size = ls.size();
        arr = new T[capacity];
        int i = 0;
        for(const T& it : ls){
            arr[i] = it;
            ++i;
        }
    };
    Vector& operator = (const Vector& other){
        if(this == &other)return *this;
        else{
            if(arr != nullptr){
                delete[] arr;
            }
            size = other.size;
            capacity = other.capacity;
            arr = new T[capacity];
            for(int i = 0; i < size; ++i){
                arr[i] = other.arr[i];
            }
            return *this;
        }
    }
    Vector& operator = (Vector&& other){
        if(this == &other)return *this;
        else{
            if(arr != nullptr){
                delete[] arr;
            }
            size = other.size;
            capacity = other.capacity;
            arr = other.arr;
            other.arr = nullptr;
            return *this;
        }
    }
    Vector(const Vector& other){
        if(this == &other)return;
        else{
            if(arr != nullptr){
                delete[] arr;
            }
            size = other.size;
            capacity = other.capacity;
            arr = new T[capacity];
            for(int i = 0; i < size; ++i){
                arr[i] = other.arr[i];
            }
        }
    }
    Vector(Vector&& other){
        if(this == &other)return;
        else{
            if(arr != nullptr){
                delete[] arr;
            }
            size = other.size;
            capacity = other.capacity;
            arr = other.arr;
            other.arr = nullptr;
        }
    }
    void push_back(T value){
        if(size < ((capacity * 2) / 3)){
            arr[size] = value;
        }
        else {
            capacity = capacity * 2;
            T* new_arr = new T[capacity];
            for(int i = 0; i < size; ++i){
                new_arr[i] = arr[i];
            }
            new_arr[size] = value;
            delete[] arr;
            arr = new_arr;
            new_arr = nullptr;
        }
        ++size;
    }
    T& at(int index){
        if(index < size && index >= 0 && arr != nullptr){
            return arr[index];
        }
        else throw std::out_of_range("The Index must be greater equal zero and less than size");
    }
    const T& at(int index)const {
        if(index < size && index >= 0 && arr != nullptr){
            return arr[index];
        }
        else throw std::out_of_range("The Index must be greater equal zero and less than size");
    }
    void shrink_to_fit(){
        if(size < capacity){
            capacity = size;
            T* new_arr = new T[capacity];
            for(int i = 0; i < size; ++i){
                new_arr[i] = arr[i];
            }
            delete[] arr;
            arr = new_arr;
            new_arr = nullptr;
        }
    }
    int get_size()const{
        return size;
    }
    int get_capacity()const{
        return capacity;
    }
    ~Vector(){
        delete[] arr;
        arr = nullptr;
    }
};

TEST_CASE("TestVector") {
    SECTION("Testcreated") {
        Vector<int> v;
        CHECK(v.get_capacity() == 10);
        CHECK(v.get_size() == 0);
        CHECK_THROWS_AS(Vector<int>(-10), std::invalid_argument);
        Vector<int> v2(15);
        CHECK(v2.get_capacity() == 15);
        Vector<int> v3({1, 2, 3, 4, 5});
        CHECK(v3.get_capacity() == 10);
        CHECK(v3.get_size() == 5);
        v = v3;
        CHECK(v.get_capacity() == 10);
        CHECK(v.get_size() == 5);
    }
    SECTION("Testpush") {
        Vector<int> v(5);
        CHECK(v.get_capacity() == 5);
        CHECK(v.get_size() == 0);
        v.push_back(10);
        v.push_back(5);
        v.push_back(6);
        v.push_back(10);
        v.push_back(5);
        CHECK(v.get_capacity() == 10);
        CHECK(v.get_size() == 5);
    }
    SECTION("Testindex") {
        Vector<int> v(5);
        CHECK(v.get_capacity() == 5);
        CHECK(v.get_size() == 0);
        v.push_back(10);
        v.push_back(5);
        v.push_back(6);
        v.push_back(10);
        v.push_back(5);
        CHECK(v.get_capacity() == 10);
        CHECK(v.get_size() == 5);
        CHECK(v.at(0) == 10);
        CHECK_THROWS_AS(v.at(-1), std::out_of_range);
        CHECK_THROWS_AS(v.at(5), std::out_of_range);
    }
    SECTION("TestCopyAndMove") {
        Vector<int> v1(5);
        Vector<int> v2(v1);
        CHECK(v1.get_capacity() == 5);
        CHECK(v1.get_size() == 0);
        CHECK(v2.get_capacity() == 5);
        CHECK(v2.get_size() == 0);
        Vector<int> v3(std::move(v1));
        Vector<int> v4({1,2,3,4,5});
        Vector<int> v5 = std::move(v4);
        CHECK(v3.get_capacity() == 5);
        CHECK(v3.get_size() == 0);
        CHECK_THROWS(v1.at(1));//Здесь возникает предупреждение из за move
        CHECK(v5.get_capacity() == 10);
        CHECK(v5.get_size() == 5);
        CHECK(v5.at(0) == 1);
        CHECK(v5.at(4) == 5);
    }
}



int main(int argc, char* argv[]) {
    return Catch::Session().run(argc, argv);

}