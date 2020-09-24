#ifndef IMODELDBCONTEXT_H
#define IMODELDBCONTEXT_H

#include <qlist.h>

template<class TModel, class TKey>
class IModelDBContext
{
public:
    virtual bool addModel(const TKey &type,const TModel *model) = 0;
    virtual bool removeModel(const TKey &type, const int &indexOfModel) = 0;
    virtual bool replaceModel(const TKey &type, const int &indexOfModel, const TModel *model) = 0;
    virtual const TModel *model(const TKey &type, const int &index) = 0;
    virtual int indexOfModel(const TKey &type, const TModel *model) = 0;
    virtual int countOfModels(const TKey &type) = 0;
    virtual QList<const TModel*> models(const TKey &type) = 0;
};

#endif // IMODELDBCONTEXT_H
