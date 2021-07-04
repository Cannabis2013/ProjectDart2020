#include "tournamentsjsondb.h"

void TournamentsJsonDb::fetchModels()
{
    try {
        _dartsTournamentModels << _createModelsFromJson->create(readJsonObjectFromFile(_fileName));
    } catch (...) {
        return;
    }
}

void TournamentsJsonDb::saveState()
{
    writeJsonObjectToFile(_createJsonFromModels->createJson(_dartsTournamentModels),_fileName);
}


TournamentsJsonDb::TournamentsJsonDb(const QString &fileName):
    _fileName(fileName)
{
}

void TournamentsJsonDb::add(const Model *model)
{
    _dartsTournamentModels.append(model);
    saveState();
}

const TournamentsJsonDb::Model *TournamentsJsonDb::model(const int &index) const
{
    auto model = _dartsTournamentModels.at(index);
    return model;
}

QVector<const TournamentsJsonDb::Model *> TournamentsJsonDb::models() const
{
    return _dartsTournamentModels;
}

bool TournamentsJsonDb::remove(const int &index)
{
    _dartsTournamentModels.removeAt(index);
    saveState();
    return true;
}

int TournamentsJsonDb::indexOf(const Model *model) const
{
    auto index = _dartsTournamentModels.indexOf(model);
    return index;
}

void TournamentsJsonDb::replace(const int &index, const Model *model)
{
    _dartsTournamentModels.replace(index,model);
    saveState();
}
