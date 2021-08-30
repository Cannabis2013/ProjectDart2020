#ifndef SCORECALCULATORINTERFACE_H
#define SCORECALCULATORINTERFACE_H

#include <qvector.h>

template<typename TModelsInterface>
class IPointCalculatorService{
public:
    typedef TModelsInterface ModelsInterface;
    virtual int calculateScore(const ModelsInterface* model) const= 0;
    virtual void addScoreValuesToDartsPointModels(const QVector<ModelsInterface*>& models) const = 0;
};

#endif // SCORECALCULATORINTERFACE_H
