#ifndef IDSCMODELBUILDER_H
#define IDSCMODELBUILDER_H

#include <qvector.h>

template<typename TModel, typename TUuid,typename TString, typename TJsonFormat>
class IDSCModelBuilder
{
public:
    typedef TModel Model;
    typedef TUuid Id;
    typedef TString String;
    typedef TJsonFormat Json;
    virtual const Model* createModel(const Json& json) const = 0;
    virtual const Model* createModel(const Id &id, const String &stringValue) const = 0;
    virtual QVector<const Model*> createModels(const Json& json) = 0;
};

#endif // IDARTSPLAYERBUILDERSERVICE_H
