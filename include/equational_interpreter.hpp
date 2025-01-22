#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <vector>
#include <string>
#include <iostream>
#include "ast.hpp"
#include "interval_store.hpp"  

class Location{
    std::string name;

public:
    IntervalStore store;

public:
    Location(std::string name): name(name) {}

    virtual ~Location() = default; 

    std::string get_name(){
        return name;
    }

    void print_location(){
        std::cout << "Location: " << name << std::endl;
        store.print();
    }

    virtual bool eval(IntervalStore &store_other)=0;
};



class PreconLocation: public Location{

public:
    PreconLocation(): Location("PRE_CON") {}

    bool eval(IntervalStore &store_other) override {
        //This must be an update
        std::cout << "Precondition location" << std::endl;
        return true;
    }
};

class DeclaLocation: public Location{

public:
    DeclaLocation(std::string var): Location("Declaration") {}

    bool eval(IntervalStore &store_other) override {
        std::cout << "Declaration location" << std::endl;
        store.create_interval("var", INT64_MIN, INT64_MAX);
        return true;
    }    
};

class AssignLocation: public Location{
    std::string var;
    int value;

public:
    AssignLocation(std::string var, int value): Location("Assign"), var(var), value(value) {}

    bool eval(IntervalStore &store_other) override {
        //This must be an update
        std::cout << "Assignment location" << std::endl;
        std::pair<int, int> interval(value, value); //new interval
        
        store.update_interval(var, interval);

        bool res = true; //Has not changed

        for(auto & [key, value] : store.store){
            if(store_other.store[key].first != value.first || store_other.store[key].second != value.second){
                res = false;
            }
        }

        return res;
    }    
};

class EquationalInterpreter {
    
    std::vector<std::shared_ptr<Location>> locations;

public:
    void create_locations(const ASTNode &node){

        if(node.type == NodeType::DECLARATION){
            locations.push_back(std::make_shared<DeclaLocation>(node.children[0].getValueString()));
        }

        if(node.type == NodeType::PRE_CON){
            locations.push_back(std::make_shared<PreconLocation>());
        }

        if(node.type == NodeType::ASSIGNMENT){
            locations.push_back(std::make_shared<AssignLocation>(node.children[0].getValueString(), node.children[1].getValueInt()));
        }

        for(auto &child : node.children){
            create_locations(child);
        }
    }

    bool eval_all(){
        
        bool has_not_changed = true;

        for(int i = 0; i<locations.size(); i++){
            if(locations[i]->get_name() == "Declaration"){
                continue;
            }
            has_not_changed = has_not_changed && locations[i]->eval(locations[i-1]->store);
        }
        return has_not_changed;
    }

    void eval_declaration(){
        for(int i = 0; i<locations.size(); i++){
            if(locations[i]->get_name() == "Declaration"){
                locations[i]->eval(locations[i]->store);
            }
        }
    }

    void engine_fixpoint(){

        bool has_not_changed = false;
        int iter = 0;

        eval_declaration();

        while(!has_not_changed){
            has_not_changed = eval_all();
            std::cout << "Iteration " << iter << std::endl;
            iter++;

            if(iter == 100)
                exit(1);
        }
        std::cout << "Fixpoint reached" << std::endl;

        
    }

    void print_locations(){
        std::cout << "Locations:" << std::endl;
        for(const auto &loc : locations){
            std::cout << loc->get_name() << std::endl;
        }
    }
};;

#endif // LOCATION_HPP