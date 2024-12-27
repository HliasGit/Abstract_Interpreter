#ifndef ABS_INT_HPP
#define ABS_INT_HPP

#include <iostream>
#include "interval_store.hpp"
#include "ast.hpp"

class AbstractInterpreter{
    using VType = std::variant<std::string, int, BinOp, LogicOp>;

    IntervalStore store;

public:
    AbstractInterpreter() = default;

public:
    void eval(const ASTNode& ast){
        std::cout << "Abstract Interpreter evaluating" << std::endl;

        traverse(ast);
    }

private:
    void handle_assignment(const ASTNode& node){
        std::string var = node.getChildernValueString(0);
        int lb = node.getChildernValueInt(1);
        int ub = node.getChildernValueInt(1);
        store.create_interval(var, lb, ub);
    }

    void op_val_val(BinOp op, int value1, int value2, std::pair<int, int> &interval){
        switch (op) {
            case BinOp::ADD:
                interval.first = value1+value2;
                interval.second = value1+value2;
                break;
            
            case BinOp::SUB:
                interval.first = value1-value2;
                interval.second = value1-value2;
                break;

            case BinOp::MUL:
                interval.first = value1*value2;
                interval.second = value1*value2;
                break;

            case BinOp::DIV:
                interval.first = value1/value2;
                interval.second = value1/value2;
                break;
            
            default:
                break;
        }
    }

    void op_int_val(BinOp op, std::pair<int, int> &interval, int value){
        switch (op) {
            case BinOp::ADD:
                interval.first += value;
                interval.second += value;
                break;
            
            case BinOp::SUB:
                interval.first -= value;
                interval.second -= value;
                break;

            case BinOp::MUL:
                interval.first *= value;
                interval.second *= value;
                break;

            case BinOp::DIV:
                interval.first /= value;
                interval.second /= value;
                break;
            
            default:
                break;
        }
    }

    void op_int_int(BinOp op, std::pair<int, int> &interval, std::pair<int, int> &interval2){
        switch (op) {
            case BinOp::ADD:
                interval.first += interval2.first;
                interval.second += interval2.second;
                break;
            
            case BinOp::SUB:
                interval.first -= interval2.first;
                interval.second -= interval2.second;
                break;

            case BinOp::MUL:
                interval.first *= interval2.first;
                interval.second *= interval2.second;
                break;

            case BinOp::DIV: //WHY??????
                interval.first /= interval2.second;
                interval.second /= interval2.first;
                break;
            
            default:
                break;
        }
    }

    void handle_ar_op(const ASTNode& node, std::pair<int, int> &interval){

        BinOp expression = node.getValueBinOp();                       // Operation to perform
        std::cout << "Exp: " << expression << std::endl;

        if(node.children[0].type == NodeType::ARITHM_OP){
            if(node.children[1].type == NodeType::INTEGER){
                handle_ar_op(node.children[0], interval);
                int value2 = node.children[1].getValueInt();
                op_int_val(expression, interval, value2);
            }
        }

        if(node.children[0].type == NodeType::ARITHM_OP){
            if(node.children[1].type == NodeType::VARIABLE){
                handle_ar_op(node.children[0], interval);
                //print interval
                std::cout << "Interval: [" << interval.first << ", " << interval.second << "]" << std::endl;
                std::string value2 = node.children[1].getValueString();
                std::pair<int, int> interval2 = store.get_interval(value2);
                op_int_int(expression, interval, interval2);
            }
        }

        if(node.children[1].type == NodeType::ARITHM_OP){
            if(node.children[0].type == NodeType::INTEGER){
                handle_ar_op(node.children[1], interval);
                int value1 = node.children[0].getValueInt();
                op_int_val(expression, interval, value1);
            }
        }

        if(node.children[0].type == NodeType::INTEGER){
            if(node.children[1].type == NodeType::INTEGER){
                int value1 = node.children[0].getValueInt();
                // std::cout << "first: " << value1 << std::endl;
                int value2 = node.children[1].getValueInt();
                // std::cout << "second : " << value2 << std::endl;
                interval.first = 0;
                interval.second = 0;
                op_val_val(expression, value1, value2, interval);
            }
        }

        if(node.children[0].type == NodeType::INTEGER){
            if(node.children[1].type == NodeType::VARIABLE){
                int value1 = node.children[0].getValueInt();
                std::string value2 = node.children[1].getValueString();
                std::pair<int, int> interval2 = store.get_interval(value2);
                interval.first = interval2.first;
                interval.second = interval2.second;
                op_int_val(expression, interval, value1);
            }
        }

        if(node.children[0].type == NodeType::VARIABLE){
            if(node.children[1].type == NodeType::INTEGER){
                std::string value1 = node.children[0].getValueString();
                std::pair<int, int> interval2 = store.get_interval(value1);
                interval.first = interval2.first;
                interval.second = interval2.second;
                int value2 = node.children[1].getValueInt();
                op_int_val(expression, interval, value2);
            }
        }
        
        if(node.children[0].type == NodeType::VARIABLE){
            if(node.children[1].type == NodeType::VARIABLE){
                std::string value1 = node.children[0].getValueString();
                std::pair<int, int> interval1 = store.get_interval(value1);
                interval.first = interval1.first;
                interval.second = interval1.second;
                std::string value2 = node.children[1].getValueString();
                std::pair<int, int> interval2 = store.get_interval(value2);
                op_int_int(expression, interval, interval2);
            }
        }
    }

    void traverse(const ASTNode& node){
        if (node.type == NodeType::PRE_CON){
            int lb = node.children[0].children[0].getValueInt();
            int ub = node.children[1].children[0].getValueInt();
            store.create_interval(node.children[0].children[1].getValueString(), lb, ub);
        }
        if (node.type == NodeType::ASSIGNMENT) {
            std::string val_to_ass = node.getChildernValueString(0);

            //Here I check if the node has an arithmetic operation
            bool ar_op = false;
            for (const auto& child : node.children){
                if (child.type == NodeType::ARITHM_OP){
                    std::cout << "AR OP" << std::endl;
                    std::pair<int, int> interval;
                    handle_ar_op(child, interval);
                    if(store.contains(val_to_ass)){
                        store.update_interval(val_to_ass, interval.first, interval.second);
                    }else{
                        store.create_interval(val_to_ass, interval.first, interval.second);
                    }
                    ar_op = true;
                }
            }

            // If the node has an arithmetic operation, handle it
            if(!ar_op){
                handle_assignment(node);
            }
        }
        for (const auto& child : node.children){
            traverse(child);
        }
    }
};

#endif // ABS_INT_HPP