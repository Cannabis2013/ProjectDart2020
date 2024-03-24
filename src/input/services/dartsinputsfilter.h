#ifndef DARTSINPUTSFILTER_H
#define DARTSINPUTSFILTER_H

#include "idartsinputsfilter.h"

class ServiceCollection;

class DartsInputsfilter : public IDartsInputsFilter {
public:
        DartsInputsfilter(ServiceCollection* services);

        QList<DartsInput> valids(const QString& name) const override;
        int validCount(const QString& name) const override;
        bool anyInputs(const QString& name, const int& turnId) const override;

private:
        typedef QList<DartsInput> Inputs;
        ServiceCollection* _services;
};
#endif // DARTSINPUTSFILTER_H
