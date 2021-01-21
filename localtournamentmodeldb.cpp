#include "localtournamentmodeldb.h"

LocalTournamentModelDB::LocalTournamentModelDB(const QString &orgName, const QString &appName):
    AbstractPersistence(orgName,appName)
{
    read();
}

LocalTournamentModelDB::~LocalTournamentModelDB()
{
    write();
}

bool LocalTournamentModelDB::addModel(const QString &type, const ModelInterface<QUuid> *model)
{
    if(!acceptedModelTypes.contains(type))
        return false;
    _models.insert(type,model);
    return true;
}

bool LocalTournamentModelDB::removeModel(const QString &type, const int &indexOfModel)
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

bool LocalTournamentModelDB::replaceModel(const QString &type, const int &indexOfModel, const ModelInterface<QUuid> *newModel)
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

const ModelInterface<QUuid> *LocalTournamentModelDB::model(const QString &type, const int &index)
{
    if(!acceptedModelTypes.contains(type))
        throw "Type provided not covered by this context";
    auto modelsAssociatedToProvidedKey = _models.values( type);
    auto model = modelsAssociatedToProvidedKey.at(index);
    return model;
}

int LocalTournamentModelDB::indexOfModel(const QString &type, const ModelInterface<QUuid> *model)
{
    if(!acceptedModelTypes.contains(type))
        return -1;
    auto models = _models.values(type);
    auto index = models.indexOf(model);
    return index;
}

int LocalTournamentModelDB::countOfModels(const QString &type)
{
    if(!acceptedModelTypes.contains(type))
        return -1;
    auto count = _models.count(type);
    return count;
}

QList<const ModelInterface<QUuid> *> LocalTournamentModelDB::models(const QString &type)
{
    if(!acceptedModelTypes.contains(type))
        QList<const ModelInterface<QUuid>*>();
    auto models = _models.values(type);
    return models;
}

void LocalTournamentModelDB::read()
{

}

void LocalTournamentModelDB::write()
{

}

QJsonArray LocalTournamentModelDB::assembleTournamentsJSONArray()
{

    QJsonArray tournamentsJSON;
    auto tournamentModels = models("Tournament");
    for (auto model : tournamentModels) {
        auto tournamentModel = dynamic_cast<const FTPTournament*>(model);
        QJsonObject obj;
        auto id = tournamentModel->id();
        obj["ID"] = id.toString();
        obj["Title"] = tournamentModel->title();
        obj["KeyPoint"] = tournamentModel->keyPoint();
        obj["GameMode"] = tournamentModel->gameMode();
        obj["TableViewHint"] = tournamentModel->modelTableViewHint();
        obj["InputMode"] = tournamentModel->inputMode();
        obj["Winner"] = tournamentModel->winner().toString();
        obj["Throws"] = tournamentModel->numberOfThrows();
        auto players = tournamentModel->assignedPlayerIdentities();

        QJsonArray playersJSON;
        auto count = players.count();
        for (int j = 0; j < count; ++j) {
            auto playerID = players.at(j).toString();
            QJsonObject playerObj;
            playerObj["ID"] = playerID;
            playersJSON.append(playerObj);
        }
        obj["Players"] = playersJSON;
        tournamentsJSON.append(obj);
    }
    return tournamentsJSON;
}

QJsonArray LocalTournamentModelDB::assembleScoresJSONArray()
{

}

void LocalTournamentModelDB::extractTournamentModelsFromJSON(const QJsonArray &arr)
{

}

void LocalTournamentModelDB::extractScoreModelsFromJSON(const QJsonArray &arr)
{

}
