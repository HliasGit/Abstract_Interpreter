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

    void update_interval(const std::string &var, std::pair<int, int> &interval){
        store[var] = {interval.first, interval.second};
        std::cout << "Updated interval" << std::endl;
    }

    void remove_interval(const std::string &var){
        store.erase(var);
        std::cout << "Removed interval" << std::endl;
    }

    std::pair<int,int> get_interval(const std::string& var){
        return store[var];
    }

    bool contains(const auto& value_f) const {
        for (const auto& inte : store) {
            if (inte.first == value_f) {
                return true;
            }
        }
        return false;
    }

    void deepCopyInt(std::pair<int, int>& interval, const std::pair<int, int>& interval2){
        interval.first = interval2.first;
        interval.second = interval2.second;
    }

    void print(){
        for (auto& [var, interval] : store){
            std::cout << var << " : [" << interval.first << ", " << interval.second << "]" << std::endl;
        }
    }
};

#endif // INTERVAL_STORE_HPP