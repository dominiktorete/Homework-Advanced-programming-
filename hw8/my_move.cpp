#include <iostream>
#include <vector>
template<typename T>
void my_move(std::vector<T>& vec1, std::vector<T>& vec2){
    if(&vec1!=&vec2){
        vec2 = std::move(vec1);
    }else{
        std::cout << "Error: erroneous self-assignment\n";
    }
}
int main()
{
    std::vector <std::string> one = { "test_string1", "test_string2" };
    std::vector <std::string> two;
    my_move(one, two);
    for(const auto& it : two){
        std::cout << it << " ";
    }
    return 0;
}