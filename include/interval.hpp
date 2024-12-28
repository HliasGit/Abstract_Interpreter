#ifndef INTERVAL_HPP
#define INTERVAL_HPP

class Interval{

public:
    static void join_intervals(std::pair<int, int>& interval1, std::pair<int, int>& interval2){
        interval1.first = std::min(interval1.first, interval2.first);
        interval1.second = std::max(interval1.second, interval2.second);
    }

};


#endif // INTERVAL_HPP