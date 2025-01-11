#ifndef INTERVAL_HPP
#define INTERVAL_HPP

class Interval{

    static const int64_t int_min = -2147483648;
    static const int64_t int_max = 2147483647;

public:
    static void join_intervals(std::pair<int, int>& interval1, std::pair<int, int>& interval2){
        interval1.first = std::min(interval1.first, interval2.first);
        interval1.second = std::max(interval1.second, interval2.second);
        // std::cout << "In the join " << interval1.first << "; " << interval1.second << std::endl;
    }

    static void op_int_int(BinOp op, std::pair<int, int> &interval, std::pair<int, int> &interval2){
        switch (op) {
            case BinOp::ADD:
                if((int64_t)interval.second > int_max - (int64_t)interval2.second){
                    std::cout << "Overflow detected add" << std::endl;
                    break;
                }
                interval.first += interval2.first;
                interval.second += interval2.second;
                break;
            
            case BinOp::SUB:
                if((int64_t)interval.first < int_min + (int64_t)interval2.first){
                    std::cout << "Overflow detected sub" << std::endl;
                    break;
                }
                interval.first -= interval2.first;
                interval.second -= interval2.second;
                break;

            case BinOp::MUL:
                if((int64_t)interval.first < int_min / (int64_t)interval2.first || (int64_t)interval.second > int_max / (int64_t)interval2.second){
                    std::cout << "Overflow detected mul" << std::endl;
                    break;
                }
                interval.first *= interval2.first;
                interval.second *= interval2.second;
                break;

            case BinOp::DIV: // Division of the first with the second and vice versa 
                if(interval2.first == 0 || interval2.second == 0){
                    std::cout << "Division by zero" << std::endl;
                    break;
                }

                if((int64_t)interval.first < int_min * (int64_t)interval2.first || (int64_t)interval.second > int_max * (int64_t)interval2.second){
                    std::cout << "Overflow detected div" << std::endl;
                    break;
                }

                interval.first /= interval2.second;
                interval.second /= interval2.first;
                break;
            
            default:
                break;
        }
    }

    static void op_val_val(BinOp op, int value1, int value2, std::pair<int, int> &interval){
        switch (op) {
            case BinOp::ADD:
                if((int64_t)value1 > int_max-(int64_t)value2){
                    std::cout << "Overflow add" << std::endl;
                    break;
                }
                interval.first = value1+value2;
                interval.second = value1+value2;
                break;
            
            case BinOp::SUB:
                if((int64_t)value1 < int_min+(int64_t)value2){
                    std::cout << "Overflow sub" << std::endl;
                    break;
                }
                interval.first = value1-value2;
                interval.second = value1-value2;
                break;

            case BinOp::MUL:
                if((int64_t)value1 < int_min / (int64_t)value2 || (int64_t)value1 > int_max / (int64_t)value2){
                    std::cout << "Overflow mul" << std::endl;
                    break;
                }
                interval.first = value1*value2;
                interval.second = value1*value2;
                break;

            case BinOp::DIV:
                if(value2 == 0){
                    std::cout << "Division by zero" << std::endl;
                    break;
                }

                if((int64_t)value1 < int_min * (int64_t)value2 || (int64_t)value1 > int_max * (int64_t)value2){
                    std::cout << "Overflow detected div" << std::endl;
                    break;
                }
                interval.first = value1/value2;
                interval.second = value1/value2;
                break;
            
            default:
                break;
        }
    }

    static void op_int_val(BinOp op, std::pair<int, int> &interval, int value){
        switch (op) {
            case BinOp::ADD:
                if((int64_t)interval.first > int_max-(int64_t)value){
                    std::cout << "Overflow add" << std::endl;
                    break;
                }
                interval.first += value;
                interval.second += value;
                break;
            
            case BinOp::SUB:
                if((int64_t)interval.first < int_min+(int64_t)value){
                    std::cout << "Overflow sub" << std::endl;
                    break;
                }
                interval.first -= value;
                interval.second -= value;
                break;

            case BinOp::MUL:
                if((int64_t)interval.first < int_min / (int64_t)value || (int64_t)interval.second > int_max / (int64_t)value){
                    std::cout << "Overflow mul" << std::endl;
                    break;
                }
                interval.first *= value;
                interval.second *= value;
                break;

            case BinOp::DIV:
                if(value == 0){
                    std::cout << "Division by zero" << std::endl;
                    break;
                }

                if((int64_t)interval.first < int_min * (int64_t)value || (int64_t)interval.second > int_max * (int64_t)value){
                    std::cout << "Overflow detected div" << std::endl;
                    break;
                }
                interval.first /= value;
                interval.second /= value;
                break;
            
            default:
                break;
        }
    }

};


#endif // INTERVAL_HPP