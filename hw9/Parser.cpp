#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <stack>


class Parser{
    std::ifstream file;
    int line{0};
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> content;
    void delete_whitespace(std::string& temp){ //DELETE WHITESPACES before and after string
        temp.erase(0, temp.find_first_not_of(" "));
        temp.erase(temp.find_last_not_of(" ") + 1);
    }
public:
    Parser(const std::string& filename){
        file.open(filename);
        if(!file.is_open()){
            throw std::invalid_argument("The file isn't exist");
        }
        read();
    }
    void syntax(const std::string& str){
        if(str.find('=') == std::string::npos){
            if(str[0] != '[' || str[str.size()-1] != ']')throw std::invalid_argument("Syntax error. line: " + std::to_string(line));
        }
        else {
            std::string name_value = str.substr(0, str.find('='));
            delete_whitespace(name_value);
            if(name_value[0] >= '0' && name_value[0] <= '9')throw std::invalid_argument("Syntax error. line: " + std::to_string(line));
            else if(name_value.find(" ") != std::string::npos)throw std::invalid_argument("Syntax error. line: " + std::to_string(line));
        }
    }
    void read(){
        std::string temp{};
        std::string section_curr{};
        while(getline(file, temp)){
            ++line;
            if(temp.find(';') != std::string::npos){
                temp = temp.substr(0, temp.find(';'));
            }
            delete_whitespace(temp);
            if(temp.empty())continue;
            try{
                syntax(temp);
            }
            catch(std::invalid_argument& err){
                throw err;
            }
            if(temp.find('[') != std::string::npos){
                temp = temp.substr(temp.find('[') + 1, temp.find(']')-1);
                section_curr = temp;
                content.insert({section_curr, {{"", ""}}});
            }
            else if(temp.find('=') != std::string::npos){
                std::string name_value = temp.substr(0, temp.find('='));
                delete_whitespace(name_value);
                std::string value = temp.substr(temp.find('=')+1);
                delete_whitespace(value);
                content[section_curr][name_value] = value;
            }
        }
    }
    template<typename T>
    T return_value(const std::string& value){
        return value;
    }

    template<typename T>
    T get_value(const std::string& get_section_and_value){

        std::string section = get_section_and_value.substr(0,  get_section_and_value.find('.'));
        std::string variable = get_section_and_value.substr(get_section_and_value.find('.')+1);
        if(content.find(section) == content.end()){
            throw std::invalid_argument("The section isn't exist");
        }
        else{
            if(content[section].find(variable) == content[section].end()){
                std::cout << "Perhaps you meant:" << std::endl;
                for(auto it = content[section].begin(); it != content[section].end(); ++it){
                    std::cout << it->first << std::endl;
                }
            }
            else if(content[section][variable].empty()){
                throw std::invalid_argument("The value this variable isn't exist");
            }
        }
        return return_value<T>(content[section][variable]);
    }

    void print_file(){
        for(auto it = content.begin(); it != content.end(); ++it){
            std::cout << it->first << std::endl;
            for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2){
                if(!it2->first.empty())
                    std::cout << it2->first << "=" << it2->second << std::endl;
            }
        }
    }
};
template<>
int Parser::return_value(const std::string& value){
    int value_return{};
    try{
        value_return = std::stoi(value);
    }
    catch(std::invalid_argument& err){
        throw err;
    }
    catch(std::out_of_range& err){
        throw err;
    }
    return value_return;
}
template<>
double Parser::return_value(const std::string& value){
    double value_return{};
    try{
        value_return = std::stod(value);
    }
    catch(std::invalid_argument& err){
        throw err;
    }
    catch(std::out_of_range& err){
        throw err;
    }
    return value_return;
}
int main()
{
    try{
        Parser ini("ini.txt");
        ini.print_file();
        std::cout << ini.get_value<int>("Section1.var1");
        std::cout << ini.get_value<double>("Section1.var1");
        std::cout << ini.get_value<std::string>("Section1.var2");
    }
    catch(std::exception& ex){
        std::cout << ex.what();
    }
    return 0;
}