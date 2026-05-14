#include <iostream>
#include <exception>
class Smart_array{
private:
    int* ptr{nullptr};
    int size{};
    int current_size{};
public:
    Smart_array(int);
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
        arr.add_element(14);
        arr.add_element(15);
        std::cout << arr.get_element(1) << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}
