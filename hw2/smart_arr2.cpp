#include <iostream>
#include <exception>
class Smart_array{
private:
    int* ptr{nullptr};
    int size{};
    int current_size{};
public:
    Smart_array(int);
    Smart_array& operator = (const Smart_array& other){
        try{
            if(&other == this) return *this;
            if(ptr)delete[] ptr;
            ptr = new int[other.size];
            for(int i = 0; i < other.current_size; ++i){
                ptr[i] = other.ptr[i];
            }
            size = other.size;
            current_size = other.size;
            return *this;
        }
        catch(const std::exception& ex){
            std::cout << "Error in operator \' = \'" << std::endl;
            throw;
        }
    }
    void add_element(int);
    int get_element(int) const;
    ~Smart_array();
};
Smart_array::Smart_array(int _size) try {
    ptr = new int[_size];
    size = _size;
}
catch(const std::exception& ex){
    std::cout << "Error in Constructor!" << std::endl;
    throw;
}

void Smart_array::add_element(int value){
    if(current_size < size){
        ptr[current_size] = value;
        ++current_size;
    }
    else {
        throw std::out_of_range("Error: The limit of the array has been reached");
    }
}
int Smart_array::get_element(int index) const{
    if(index < current_size && index >= 0){
        return ptr[index];
    }
    else {
        throw std::invalid_argument("Error: The index is incorrect");
    }
}
Smart_array::~Smart_array(){
    if(ptr){
        delete[] ptr;
        ptr = nullptr;
        size = 0;
        current_size = 0;
    }
}
int main(){
    try {
        Smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);

        Smart_array new_array(2);
        new_array.add_element(44);
        new_array.add_element(34);

        arr = new_array; // если не делаеть своего оператора присваивания копированием, то происходит double free одной области памяти
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}

