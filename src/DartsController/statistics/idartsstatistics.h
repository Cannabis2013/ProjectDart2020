#ifndef IDARTSSTATISTICS_H
#define IDARTSSTATISTICS_H

#include "src/DartsController/statistics/statistics.h"

#include <QString>
class IDartsStatistics {
public:
        virtual Statistics statistics(const QString& name) const = 0;
};

#endif // IDARTSSTATISTICS_H
