#include <iostream>
#include <vector>
#include <algorithm>
class Functor{
    int sum{};
    int count{};
public:
    int get_sum(){
        return sum;
    }
    int get_count(){
        return count;
    }
    void operator()(int num){
        if(num % 3 == 0){
            ++count;
            sum+=num;
        }
    }
};
int main(){

    return 0;


}