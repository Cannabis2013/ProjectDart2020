#ifndef IDARTSINPUTSFILTER_H
#define IDARTSINPUTSFILTER_H

#include "src/input/models/input.h"
class IDartsInputsFilter {
public:
        virtual QList<Input> valids(const QString& name) const = 0;
        virtual int validCount(const QString& name) const = 0;
        virtual bool anyInputs(const QString& name, const int& throwId) const = 0;
};

#endif // IDARTSINPUTSFILTER_H
