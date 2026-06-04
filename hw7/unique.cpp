#include <iostream>

template<typename T>
class Unique_ptr
{
    T* ptr{};
public:
    T& operator *(){
        return *ptr;
    }
    Unique_ptr(T* _ptr) : ptr{ _ptr } {std::cout << "Unique create\n";};
    Unique_ptr(const Unique_ptr<T>&) = delete;
    T& operator =(const Unique_ptr<T>&) = delete;

    T* release(){
        T* pt = ptr;
        ptr = nullptr;
        return pt;
    }
    Unique_ptr(Unique_ptr<T>&& other){
        if(this->ptr != nullptr)delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
        std::cout << "Move semantic\n";
    }
    Unique_ptr& operator = (Unique_ptr<T>&& other){
        if(this == other) return *this;
        if(ptr)delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
        std::cout << "Move operation = \n";
        return *this;
    }
    ~Unique_ptr() {
        if(ptr)delete ptr;
        std::cout << "Unique delete\n";
    }
};

int main()
{
    int* pt = new int(5);
    Unique_ptr<int> uniq(pt);
    std::cout << *uniq << std::endl;
    Unique_ptr<int> pt2 = std::move(uniq);
    std::cout << *pt2 << std::endl;
    Unique_ptr<int> pt3(std::move(pt2));
    *pt3 = 10;
    std::cout << *pt3 << std::endl;
    int* p = pt3.release();
    *p = 7;
    std::cout << *p << std::endl;
    delete p;
    return 0;
}