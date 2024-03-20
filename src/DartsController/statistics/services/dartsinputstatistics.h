#ifndef DARTSINPUTSTATISTICS_H
#define DARTSINPUTSTATISTICS_H

#include "iinputstatistics.h"
#include "src/DartsController/input/models/Input.h"

class ServiceCollection;

class DartsInputStatistics : public IInputStatistics {
public:
        DartsInputStatistics(ServiceCollection* services);

        double middle(const QString& name) const override;
        int lowest(const QString& name) const override;
        int highest(const QString& name) const override;

private:
        ServiceCollection* _services;
        int findValueByComparison(const QList<Input>& inputs, int target, const std::function<bool(const int&, const int&)>& predicate) const;
};

#endif // DARTSINPUTSTATISTICS_H
