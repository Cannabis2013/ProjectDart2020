#include "localtournamentmodeldb.h"

LocalTournamentModelDB::LocalTournamentModelDB()
{

}

bool LocalTournamentModelDB::addModel(const QString &type, const IModel<QUuid> *model)
{
    if(!acceptedModelTypes.contains(type))
        return false;
    _models->insert(type,model);
    return true;
}

bool LocalTournamentModelDB::removeModel(const QString &type, const int &indexOfModel)
{
    if(!acceptedModelTypes.contains(type))
        return false;
    auto subList = _models->values(type);
    subList.removeAt(indexOfModel);
    _models->remove(type);
    for (auto model : subList)
        _models->insert(type,model);
    return true;
}

bool LocalTournamentModelDB::replaceModel(const QString &type, const int &indexOfModel, const IModel<QUuid> *newModel)
{
    if(!acceptedModelTypes.contains(type))
        return false;
    auto subList = _models->values(type);
    subList.replace(indexOfModel,newModel);
    _models->remove(type);
    for (auto model : subList)
        _models->insert(type,model);
    return true;
}

const IModel<QUuid> *LocalTournamentModelDB::model(const QString &type, const int &index)
{
    if(!acceptedModelTypes.contains(type))
        throw "Type provided not covered by this context";
    auto modelsAssociatedToProvidedKey = _models->values( type);
    auto model = modelsAssociatedToProvidedKey.at(index);
    return model;
}

int LocalTournamentModelDB::indexOfModel(const QString &type, const IModel<QUuid> *model) const
{
    if(!acceptedModelTypes.contains(type))
        return -1;
    auto models = _models->values(type);
    auto index = models.indexOf(model);
    return index;
}

QList<const IModel<QUuid> *> LocalTournamentModelDB::models(const QString &type)
{
    if(!acceptedModelTypes.contains(type))
        QList<const IModel<QUuid>*>();
    auto models = _models->values(type);
    return models;
}
