#include "jsondbcontext.h"

void JsonDbContext::fetchModels()
{
    QJsonObject jsonObject;
    // Extact content from file
    try {
        jsonObject = readJSONFromFile(_fileName);
    } catch (...) {
        return;
    }
    // Assemble json objects from content
    auto tournamentsJSONArray = jsonObject["FTPTournaments"].toArray();
    auto dartsPointsJsonArray = jsonObject["DartsPoints"].toArray();
    auto playerJSONArray = jsonObject["Players"].toArray();
    // Exctract models from json objects
    extractDartsTournamentModelsFromJSON(tournamentsJSONArray);
    extractScoreModelsFromJSON(dartsPointsJsonArray);
    extractPlayerModelsFromJSON(playerJSONArray);
}

void JsonDbContext::saveState()
{
    /*
     * Persist tournament models
     */
    QJsonObject modelJSON;
    /*
     * Persist 'first to post' tournaments
     */
    modelJSON["FTPTournaments"] = assembleDartsTournamentsJsonArray();
    modelJSON["DartsPoints"] = assembleDartsPointsJSONArray();
    modelJSON["Players"] = assemblePlayersJSONArray();
    writeJSONToFile(modelJSON,"Models");
}

void JsonDbContext::addTournament(const IModel<QUuid> *model)
{
    _dartsTournamentModels.append(model);
    saveState();
}

QVector<const IModel<QUuid>*> JsonDbContext::dartsTournaments()
{
    return _dartsTournamentModels;
}

void JsonDbContext::removeDartsTournamentModelFromId(const QUuid &id)
{
    for (auto i = _dartsTournamentModels.begin();i != _dartsTournamentModels.end();i++) {
        auto model = *i;
        auto modelId = model->id();
        if(modelId == id)
        {
            _dartsTournamentModels.removeOne(model);
            return;
        }
    }
}

void JsonDbContext::removeDartsTournamentModelFromId(const int &index)
{
    _dartsTournamentModels.removeAt(index);
    saveState();
}

int JsonDbContext::indexOfTournament(const IModel<QUuid> *model)
{
    auto index = _dartsTournamentModels.indexOf(model);
    return index;
}

void JsonDbContext::replaceTournament(const int &index, const IModel<QUuid> *tournament)
{
    _dartsTournamentModels.replace(index,tournament);
    saveState();
}

const IModel<QUuid> *JsonDbContext::dartsTournamentModelFromIndex(const int &index)
{
    auto model = _dartsTournamentModels.at(index);
    return model;
}

const IModel<QUuid> *JsonDbContext::dartsTournamentModelFromIndex(const QUuid &id)
{
    for (auto var = _dartsTournamentModels.begin(); var != _dartsTournamentModels.end(); ++var) {
        auto model = *var;
        if(model->id() == id)
            return model;
    }
    return nullptr;
}

void JsonDbContext::addScoreModel(const IModel<QUuid> *model)
{
    _dartsPointModels.append(model);
    saveState();
}

const IModel<QUuid> *JsonDbContext::scoreModel(const int &index)
{
    auto model = _dartsPointModels.at(index);
    return model;
}

QVector<const IModel<QUuid> *> JsonDbContext::dartsPointModels()
{
    return _dartsPointModels;
}

void JsonDbContext::replaceScoreModel(const int &index, const IModel<QUuid> *score)
{
    _dartsPointModels.replace(index,score);
    saveState();
}

int JsonDbContext::indexOfScoreModel(const IModel<QUuid> *score)
{
    auto index = _dartsPointModels.indexOf(score);
    return index;
}

void JsonDbContext::removeScoreModel(const int &index)
{
    _dartsPointModels.remove(index);
    saveState();
}

QJsonArray JsonDbContext::assembleDartsTournamentsJsonArray()
{
    auto tournamentsJSON = _dartsTournamentAssembler->assembleDartsTournamentsFromModels(dartsTournaments());
    return tournamentsJSON;
}

QJsonArray JsonDbContext::assembleDartsPointsJSONArray()
{
    auto jsonArray = _dartsInputAssembler->assembleDartsPointJson(dartsPointModels());
    return jsonArray;
}

QJsonArray JsonDbContext::assemblePlayersJSONArray()
{
    QJsonArray playersJSON = _playerModelsAssemblerService->assembleJsonArrayFromModels(playerModels());
    return playersJSON;
}

void JsonDbContext::extractDartsTournamentModelsFromJSON(const QJsonArray &arr)
{
    auto dartsTournaments = _dartsTournamentJsoNExstractorService->extractDartsTournamentFromJson(arr);
    _dartsTournamentModels << dartsTournaments;
}

void JsonDbContext::extractScoreModelsFromJSON(const QJsonArray &arr)
{
    for (auto i = arr.begin();i != arr.end();i++) {
        auto scoreModel = _dartsInputExtractor->extractDartsPointFromJson(*i);
        _dartsPointModels.append(scoreModel);
    }
}

void JsonDbContext::extractPlayerModelsFromJSON(const QJsonArray &arr)
{
    _playerModels << _playerJsonExtractorService->extractPlayerModelsFromJsonArray(arr);
}

QVector<const IModel<QUuid>*> JsonDbContext::playerModels()
{
    return _playerModels;
}

void JsonDbContext::addPlayerModel(const IModel<QUuid> *player)
{
    _playerModels.append(player);
    saveState();
}

void JsonDbContext::removePlayerModel(const QUuid &id)
{
    for (const auto& playerInterface : qAsConst(_playerModels)) {
        if(playerInterface->id() == id)
        {
            _playerModels.removeOne(playerInterface);
            return;
        }
    }
}

void JsonDbContext::removePlayerModel(const int &index)
{
    _playerModels.remove(index);
    saveState();
}

int JsonDbContext::indexOfPlayerModel(const IModel<QUuid> *player)
{
    auto index = _playerModels.indexOf(player);
    return index;
}

void JsonDbContext::replacePlayerModel(const int &index, const IModel<QUuid> *player)
{
    _playerModels.replace(index,player);
    saveState();
}

const IModel<QUuid>* JsonDbContext::playerModel(const int &index)
{
    auto count = _playerModels.count();
    if(index >= count)
        throw "Index out of range";
    auto model = _playerModels.at(index);
    return model;
}
