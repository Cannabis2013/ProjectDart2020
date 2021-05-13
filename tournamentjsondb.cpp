#include "tournamentjsondb.h"


void DartsTournamentJSonDb::addTournament(const IDartsTournament *model)
{
    _dartsTournamentModels.append(model);
    saveState();
}

const IDartsTournament *DartsTournamentJSonDb::dartsTournamentModelFromIndex(const int &index) const
{
    auto model = _dartsTournamentModels.at(index);
    return model;
}

QVector<const IDartsTournament *> DartsTournamentJSonDb::dartsTournaments() const
{
    return _dartsTournamentModels;
}

void DartsTournamentJSonDb::removeDartsTournamentModelByIndex(const int &index)
{
    _dartsTournamentModels.removeAt(index);
    saveState();
}

int DartsTournamentJSonDb::indexOfTournament(const IDartsTournament *model) const
{
    auto index = _dartsTournamentModels.indexOf(model);
    return index;
}

void DartsTournamentJSonDb::replaceTournament(const int& index, const IDartsTournament *tournament)
{
    _dartsTournamentModels.replace(index,tournament);
    saveState();
}

void DartsTournamentJSonDb::setDartsTournamentsExtractor(JsonExtractor *dartsTournamentsExtractor)
{
    _dartsTournamentsExtractor = dartsTournamentsExtractor;
}

void DartsTournamentJSonDb::setDartsTournamentAssembler(JsonAssembler *dartsTournamentAssembler)
{
    _dartsTournamentAssembler = dartsTournamentAssembler;
}

DartsTournamentJSonDb *DartsTournamentJSonDb::createInstance(DartsTournamentJSonDb::JsonExtractor *jsonExtractor, DartsTournamentJSonDb::JsonAssembler *jsonAssembler)
{
    auto db = new DartsTournamentJSonDb;
    db->setDartsTournamentsExtractor(jsonExtractor);
    db->setDartsTournamentAssembler(jsonAssembler);
    db->fetchModels();
    return db;
}

void DartsTournamentJSonDb::fetchModels()
{
    QJsonObject jsonObject;
    // Extact content from file
    try {
        jsonObject = readJsonObjectFromFile(_fileName);
    } catch (...) {
        return;
    }
    _dartsTournamentModels << _dartsTournamentsExtractor->service(jsonObject);
}

void DartsTournamentJSonDb::saveState()
{
    QJsonObject jsonObject = _dartsTournamentAssembler->service(dartsTournaments());
    writeJsonObjectToFile(jsonObject,_fileName);
}
