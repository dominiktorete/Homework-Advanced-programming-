#include <vector>
#include <iostream>
#include <set>
#include <list>
template<template<typename, typename> class Container, typename T, class Alloc>
void print_container(const Container<T, Alloc>& cont){
    for(const auto& el : cont){
        std::cout << el << " ";
    }
    std::cout << std::endl;
}


int main() {
    std::set<std::string> test_set = { "one", "two", "three", "four" };
    print_container(test_set); // four one three two. помните почему такой порядок? :) Из за того что Сэт складывает их поредяке возрастания,
    // то есть он сравнивает строки и сортирует, если так можно сказать.

    std::list<std::string> test_list = { "one", "two", "three", "four" };
    print_container(test_list); // one, two, three, four

    std::vector<std::string> test_vector = { "one", "two", "three", "four" };
    print_container(test_vector); // one, two, three, four
    return 0;

}