#ifndef SCORECALCULATORINTERFACE_H
#define SCORECALCULATORINTERFACE_H

#include <qvector.h>

template<typename TModelsInterface>
class IPointCalculatorService{
public:
    typedef TModelsInterface ModelsInterface;
    virtual const TModelsInterface* calculateScoreFromDartsPoint(const ModelsInterface* model) const= 0;
    virtual void addCalculatedScoreToDartsPoints(const QVector<const ModelsInterface*>& models) const = 0;
};

#endif // SCORECALCULATORINTERFACE_H
