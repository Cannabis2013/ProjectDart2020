#ifndef SORTDARTSINPUTS_H
#define SORTDARTSINPUTS_H

#include <quuid.h>
#include <qvector.h>
#include <DartsModelsContext/Contracts/Input/isortinputmodels.h>

class SortDartsInputs : public ISortInputModels
{
public:
    QVector<IModel<QUuid>*> sort(const QVector<IModel<QUuid>*> &unsortedInputs,
                                       const IModelPredicate *predicate) const override;
private:
    class ComparePredicate
    {
    public:
        ComparePredicate(const IModelPredicate* predicate):
            _predicate(predicate){}
        bool operator()(IModel<QUuid>* _first, IModel<QUuid>* _second);
    private:
        const IModelPredicate* _predicate;
    };
};
#endif // GETORDEREDDARTSSCOREMODELS_H
