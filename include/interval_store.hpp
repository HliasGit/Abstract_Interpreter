#ifndef INTERVAL_STORE_HPP
#define INTERVAL_STORE_HPP

#include <map>
#include <string>
#include <iostream>

class IntervalStore{
    std::map<std::string, std::pair<int, int>> store;

public:
    void create_interval(const std::string& var, int lb, int ub){
        store.insert({var, {lb, ub}}); 
        std::cout << "Created interval for " << var << " : [" << lb << ", " << ub << "]" << std::endl;
    }    

    void add_interval(const std::string& var, int lb, int ub){
        store[var] = {store[var].first + lb, store[var].second + ub};
        std::cout << "Added interval for " << var << " : [" << store[var].first << ", " << store[var].second << "]" << std::endl;
    }

    void sub_interval(const std::string& var, int lb, int ub){
        store[var] = {store[var].first - ub, store[var].second - lb};
        std::cout << "Subtracted interval for " << var << " : [" << store[var].first << ", " << store[var].second << "]" << std::endl;
    }

    void mul_interval(const std::string& var, int lb, int ub){
        store[var] = {store[var].first * lb, store[var].second * ub};
        std::cout << "Multiplied interval for " << var << " : [" << store[var].first << ", " << store[var].second << "]" << std::endl;
    }

    void div_interval(const std::string& var, int lb, int ub){
        store[var] = {store[var].first / lb, store[var].second / ub};
        std::cout << "Divided interval for " << var << " : [" << store[var].first << ", " << store[var].second << "]" << std::endl;
    }

    void update_interval(const std::string& var, int lb, int ub){
        store[var] = {lb, ub};
        std::cout << "Updated interval for " << var << " : [" << store[var].first << ", " << store[var].second << "]" << std::endl;
    }

    std::pair<int,int> get_interval(const std::string& var){
        return store[var];
    }

    void remove_interval(const std::string& var){
        store.erase(var);
    }

    bool contains(const auto& value_f) const {
    for (const auto& inte : store) {
        if (inte.first == value_f) {
            return true;
        }
    }
    return false;
}

    void print(){
        for (auto& [var, interval] : store){
            std::cout << var << " : [" << interval.first << ", " << interval.second << "]" << std::endl;
        }
    }
};

#endif // INTERVAL_STORE_HPP