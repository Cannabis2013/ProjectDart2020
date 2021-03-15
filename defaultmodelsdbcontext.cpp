#include "defaultmodelsdbcontext.h"

DefaultModelsDbContext::DefaultModelsDbContext()
{
}

DefaultModelsDbContext::~DefaultModelsDbContext()
{
}

bool DefaultModelsDbContext::addModel(const QString &type, const ModelInterface<QUuid> *model)
{
    if(!acceptedModelTypes.contains(type))
        return false;
    _models.insert(type,model);
    return true;
}

bool DefaultModelsDbContext::removeModel(const QString &type, const int &indexOfModel)
{
    if(!acceptedModelTypes.contains(type))
        return false;
    auto subList = _models.values(type);
    subList.removeAt(indexOfModel);
    _models.remove(type);
    for (auto model : subList)
        _models.insert(type,model);
    return true;
}

bool DefaultModelsDbContext::replaceModel(const QString &type, const int &indexOfModel, const ModelInterface<QUuid> *newModel)
{
    if(!acceptedModelTypes.contains(type))
        return false;
    auto subList = _models.values(type);
    subList.replace(indexOfModel,newModel);
    _models.remove(type);
    for (auto model : subList)
        _models.insert(type,model);
    return true;
}

const ModelInterface<QUuid> *DefaultModelsDbContext::model(const QString &type, const int &index)
{
    if(!acceptedModelTypes.contains(type))
        throw "Type provided not covered by this context";
    auto modelsAssociatedToProvidedKey = _models.values( type);
    auto model = modelsAssociatedToProvidedKey.at(index);
    return model;
}

int DefaultModelsDbContext::indexOfModel(const QString &type, const ModelInterface<QUuid> *model)
{
    if(!acceptedModelTypes.contains(type))
        return -1;
    auto models = _models.values(type);
    auto index = models.indexOf(model);
    return index;
}

int DefaultModelsDbContext::countOfModels(const QString &type)
{
    if(!acceptedModelTypes.contains(type))
        return -1;
    auto count = _models.count(type);
    return count;
}

QVector<const ModelInterface<QUuid> *> DefaultModelsDbContext::models(const QString &type)
{
    if(!acceptedModelTypes.contains(type))
        return QVector<const ModelInterface<QUuid>*>();
    auto values = _models.values(type);
    auto models = values.toVector();
    return models;
}
