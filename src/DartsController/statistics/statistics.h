#ifndef STATISTICS_H
#define STATISTICS_H

class Statistics {
public:
        explicit Statistics(double average, int low, int high)
            : average(average)
            , low(low)
            , high(high)
        {
        }
        double average;
        int low;
        int high;
};

#endif // STATISTICS_H
