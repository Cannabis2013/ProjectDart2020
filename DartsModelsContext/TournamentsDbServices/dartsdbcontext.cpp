#include "DartsModelsContext/TournamentsDbServices/dartsdbcontext.h"

void DartsDbContext::fetchModels(const IDartsBuilder *modelBuilder)
{
    _models = modelBuilder->createTournaments(readJsonFromFile()->read());
}

void DartsDbContext::saveChanges(const IDartsJsonBuilder *jsonBuilder)
{
    writeJsonToFile()->write(jsonBuilder->tournamentsjson(_models));
}

DartsDbContext::DartsDbContext(FileReaderInterface *fileReader, FileWriteInterface *fileWriter)
{
    fileReader->setFileName(_fileName);
    fileWriter->setFileName(_fileName);
    setReadJsonFromFile(fileReader);
    setWriteJsonToFile(fileWriter);
}

DartsDbContext *DartsDbContext::add(IModel<QUuid> *model)
{
    _models.append(model);
    return this;
}

IModel<QUuid> *DartsDbContext::model(const int &index) const
{
    auto model = _models.at(index);
    return model;
}

QVector<IModel<QUuid> *> DartsDbContext::models() const
{
    return _models;
}

DartsDbContext *DartsDbContext::remove(const int &index)
{
    _models.removeAt(index);
    return this;
}

IDartsDbContext *DartsDbContext::remove(const QVector<int> &indexes)
{
    QVector<IModel<QUuid>*> models;
    for (int i = 0; i < _models.count(); ++i) {
        if(!indexes.contains(i))
            models << _models.at(i);
    }
    _models = models;
    return this;
}

int DartsDbContext::indexOf(IModel<QUuid> *model) const
{
    auto index = _models.indexOf(model);
    return index;
}

DartsDbContext *DartsDbContext::replace(const int &index, IModel<QUuid> *model)
{
    _models.replace(index,model);
    return this;
}
