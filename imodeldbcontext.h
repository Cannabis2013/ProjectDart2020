#ifndef IMODELDBCONTEXT_H
#define IMODELDBCONTEXT_H

#include <qlist.h>

template<class TModel, class TStringIdentifier>
class IModelDBContext
{
public:
    virtual bool addModel(const TStringIdentifier &type,const TModel *model) = 0;
    virtual bool removeModel(const TStringIdentifier &type, const int &indexOfModel) = 0;
    virtual bool replaceModel(const TStringIdentifier &type, const int &indexOfModel, const TModel *model) = 0;
    virtual const TModel *model(const TStringIdentifier &type, const int &index) = 0;
    virtual int indexOfModel(const TStringIdentifier &type, const TModel *model) const = 0;
    virtual QList<const TModel*> models(const TStringIdentifier &type) = 0;
};

#endif // IMODELDBCONTEXT_H
