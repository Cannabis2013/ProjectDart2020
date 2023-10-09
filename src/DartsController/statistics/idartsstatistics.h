#ifndef IDARTSSTATISTICS_H
#define IDARTSSTATISTICS_H

#include "src/DartsController/statistics/statistics.h"
class IDartsStatistics {
public:
        virtual Statistics statistics() const = 0;
};

#endif // IDARTSSTATISTICS_H
