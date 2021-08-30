#ifndef IDCMODELCREATOR_H
#define IDCMODELCREATOR_H

#include <qvector.h>

template<typename TModel, typename TJson, typename  TUuid, typename TString>
class IDCModelCreator
{
public:
    virtual TModel* createModel(const TJson& json) const = 0;
    virtual TModel* createModel(const int& point, const int& score, const int& modKeyCode) const = 0;
    virtual QVector<TModel*> createModels(const TJson& json) const = 0;
};
#endif // ICONTROLLERPOINTBUILDER_H
