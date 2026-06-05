#include <iostream>
#include <vector>
#include <algorithm>
class big_integer{
    std::string numb{};
public:
    big_integer(const std::string& str){
        numb = str;
    }
    big_integer(big_integer&& numb_other){
        numb = numb_other.numb;
        numb_other.numb = "";
    }
    big_integer& operator = (big_integer&& numb_other){
        if(this != &numb_other) return numb_other;
        numb = numb_other.numb;
        numb_other.numb = "";
        return *this;
    }
    big_integer operator + (const big_integer& numb_other){
        std::string temp{};
        int in_mind{};
        int numb_1{};
        int numb_2{};
        int res{};
        for(int i = this->numb.size() -1, j = numb_other.numb.size() - 1; i >= 0 || j >= 0; --i,--j){
            if(i >= 0 && j >= 0){
                numb_1 = static_cast<int>(this->numb[i] - '0');
                numb_2 = static_cast<int>(numb_other.numb[j] - '0');
                res = numb_1 + numb_2;
                if(res >= 10){
                    temp.push_back(static_cast<char>((res % 10) + in_mind + '0'));
                    in_mind = res/10;
                }
                else{
                    temp.push_back(static_cast<char>(res + in_mind + '0'));
                    if(res + in_mind > 10) in_mind = 1;
                    else in_mind = 0;
                }
            }
            else{
                if(i >= 0){
                    numb_1 = static_cast<int>(this->numb[i] - '0');
                }
                else if (j >= 0){
                    numb_1 = static_cast<int>(numb_other.numb[j] - '0');
                }
                res = numb_1 + in_mind;
                if(res >= 10){
                    temp.push_back(static_cast<char>(res % 10 + '0'));
                    in_mind = res/10;
                }
                else{
                    temp.push_back(static_cast<char>(res + '0'));
                    if(res + in_mind > 10) in_mind = 1;
                    else in_mind = 0;
                }

            }
        }
        std::reverse(temp.begin(), temp.end());
        return std::move(big_integer(temp));
    }
    big_integer operator * (const big_integer& numb_other){
        int in_mind{};
        int numb_1{};
        int numb_2{};
        int res{};
        std::vector<std::string> mult{};
        for(int j = numb_other.numb.size() -1; j >= 0; --j){
            in_mind = 0;
            std::string temp{};
            numb_2 = static_cast<int>(numb_other.numb[j] - '0');
            for(int i = this->numb.size() - 1; i >= 0; --i){
                numb_1 = static_cast<int>(this->numb[i] - '0');
                res = numb_1 * numb_2;
                temp.push_back(static_cast<char>(res % 10 + in_mind + '0'));
                in_mind = res / 10;
            }
            mult.push_back(temp);
        }
        if(in_mind > 0){
            mult.push_back(std::to_string(in_mind));
        }
        std::string res_int = mult[0];
        in_mind = 0;
        for(int k = 1; k < mult.size(); ++k){

            for(int i = k, j = 0; i < res_int.size() || j < mult[k].size(); ++i, ++j){
                if(i < res_int.size() && j < mult[k].size()){
                    numb_1 = static_cast<int>(res_int[i] - '0');
                    numb_2 = static_cast<int>(mult[k][j] - '0');
                    res = numb_1 + numb_2;
                    if(res >= 10){
                        res_int[i] = (static_cast<char>((res % 10) + in_mind + '0'));
                        in_mind = res/10;
                    }
                    else{
                        res_int[i] = (static_cast<char>(res + in_mind + '0'));
                        if(res + in_mind > 10) in_mind = 1;
                        else in_mind = 0;
                    }
                }
                else{
                    if(i < res_int.size()){
                        numb_1 = static_cast<int>(res_int[i] - '0');
                    }
                    else if (j < mult[k].size()){
                        numb_1 = static_cast<int>(mult[k][j] - '0');
                    }
                    res = numb_1 + in_mind;
                    if(res >= 10){
                        if(i == res_int.size())
                            res_int.push_back(static_cast<char>(res % 10 + '0'));
                        else{
                            res_int = (static_cast<char>(res % 10 + '0'));
                        }
                        in_mind = res/10;
                    }
                    else{
                        if(i == res_int.size())
                            res_int.push_back(static_cast<char>(res + '0'));
                        else {
                            res_int=(static_cast<char>(res + '0'));
                        }
                        if(res + in_mind > 10) in_mind = 1;
                        else in_mind = 0;
                    }

                }
            }

        }
        std::reverse(res_int.begin(), res_int.end());
        return std::move(big_integer(res_int));
    }
    friend std::ostream& operator << (std::ostream& out, const big_integer& integer){
        out << integer.numb << std::endl;
        return out;
    }
};

int main()
{
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result; // 193099
    auto num1 = big_integer("12");
    auto num2 = big_integer("21");
    std::cout << num1*num2;
    return 0;
}