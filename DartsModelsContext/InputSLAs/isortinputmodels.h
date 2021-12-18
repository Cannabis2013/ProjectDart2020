#ifndef ISORTINPUTMODELS_H
#define ISORTINPUTMODELS_H
class IModelPredicate;
template<typename T>
class QVector;
template<typename T>
class IModel;
class QUuid;
class ISortInputModels
{
public:
    virtual QVector<IModel<QUuid>*> sort(const QVector<IModel<QUuid>*>& unsortedInputs,
                                         const IModelPredicate *predicate) const = 0;
};

#endif // ISORTINPUTMODELS_H
