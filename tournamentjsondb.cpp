#include "tournamentjsondb.h"


void DartsTournamentJSonDb::addTournament(const IDartsTournament<QUuid, QString> *model)
{
    _dartsTournamentModels.append(model);
    saveState();
}

const IDartsTournament<QUuid, QString> *DartsTournamentJSonDb::dartsTournamentModelFromIndex(const int &index)
{
    auto model = _dartsTournamentModels.at(index);
    return model;
}

QVector<const IDartsTournament<QUuid, QString> *> DartsTournamentJSonDb::dartsTournaments()
{
    return _dartsTournamentModels;
}

void DartsTournamentJSonDb::removeDartsTournamentModelByIndex(const int &index)
{
    _dartsTournamentModels.removeAt(index);
    saveState();
}

int DartsTournamentJSonDb::indexOfTournament(const IDartsTournament<QUuid, QString> *model)
{
    auto index = _dartsTournamentModels.indexOf(model);
    return index;
}

void DartsTournamentJSonDb::replaceTournament(const int& index, const IDartsTournament<QUuid, QString> *tournament)
{
    _dartsTournamentModels.replace(index,tournament);
    saveState();
}

void DartsTournamentJSonDb::setDartsTournamentsExtractor(IUnaryService<const QJsonArray &, QVector<const IDartsTournament<QUuid, QString> *> > *dartsTournamentsExtractor)
{
    _dartsTournamentsExtractor = dartsTournamentsExtractor;
}

void DartsTournamentJSonDb::setDartsTournamentAssembler(IUnaryService<const QVector<const IDartsTournament<QUuid,QString>*>&,QJsonArray> *dartsTournamentAssembler)
{
    _dartsTournamentAssembler = dartsTournamentAssembler;
}


void DartsTournamentJSonDb::fetchModels()
{
    QJsonObject jsonObject;
    // Extact content from file
    try {
        jsonObject = readJSONFromFile(_fileName);
    } catch (...) {
        return;
    }
    auto jsonArray = jsonObject["FTPTournaments"].toArray();
    _dartsTournamentModels << _dartsTournamentsExtractor->service(jsonArray);
}

void DartsTournamentJSonDb::saveState()
{
    QJsonObject modelJSON;
    modelJSON["FTPTournaments"] = _dartsTournamentAssembler->service(dartsTournaments());
}
