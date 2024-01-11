#ifndef IDARTSSTATISTICS_H
#define IDARTSSTATISTICS_H

#include <QString>
class IDartsStatistics {
public:
        virtual QByteArray report() const = 0;
};

#endif // IDARTSSTATISTICS_H
