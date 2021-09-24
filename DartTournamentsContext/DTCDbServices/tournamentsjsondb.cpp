#include "DartTournamentsContext/DTCDbServices/tournamentsjsondb.h"

void TournamentsJsonDb::fetchModels()
{
    _models = createModelsFromJson()->create(readJsonFromFile()->read());
}

void TournamentsJsonDb::saveState()
{
    writeJsonToFile()->write(createJsonFromModels()->toJson(_models));
}

void TournamentsJsonDb::add(const IModel<QUuid> *model)
{
    _models.append(model);
    saveState();
}

const IModel<QUuid> *TournamentsJsonDb::model(const int &index) const
{
    auto model = _models.at(index);
    return model;
}

QVector<const IModel<QUuid> *> TournamentsJsonDb::models() const
{
    return _models;
}

bool TournamentsJsonDb::remove(const int &index)
{
    _models.removeAt(index);
    saveState();
    return true;
}

int TournamentsJsonDb::indexOf(const IModel<QUuid> *model) const
{
    auto index = _models.indexOf(model);
    return index;
}

void TournamentsJsonDb::replace(const int &index, const IModel<QUuid> *model)
{
    _models.replace(index,model);
    saveState();
}
