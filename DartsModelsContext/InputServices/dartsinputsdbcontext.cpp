#include "DartsModelsContext/InputServices/dartsinputsdbcontext.h"

#include "AsyncUtils/runnable.h"
DartsInputsDbContext::DartsInputsDbContext(FileReaderInterface *fileReader, FileWriteInterface *fileWriter)
{
    fileReader->setFileName(_fileName);
    fileWriter->setFileName(_fileName);
    setReadJsonFromFile(fileReader);
    setWriteJsonToFile(fileWriter);
}

DartsInputsDbContext *DartsInputsDbContext::add(IModel<QUuid> *model)
{
    QMutexLocker locker(&_mutex);
    _dartsScoreModels << model;
    return this;
}

IModel<QUuid> *DartsInputsDbContext::model(const int &index) const
{
    auto model = _dartsScoreModels.at(index);
    return model;
}

QVector<IModel<QUuid> *> DartsInputsDbContext::models() const
{
    QVector<IModel<QUuid>*> list;
    for (const auto& model : _dartsScoreModels)
        list << model;
    return list;
}

DartsInputsDbContext *DartsInputsDbContext::remove(const int& index)
{
    QMutexLocker locker(&_mutex);
    _dartsScoreModels.remove(index);
    return this;
}

int DartsInputsDbContext::indexOf(IModel<QUuid> *model) const
{
    auto indexOfModel = _dartsScoreModels.indexOf(model);
    return indexOfModel;
}

DartsInputsDbContext *DartsInputsDbContext::replace(const int& index, IModel<QUuid> *model)
{
    _dartsScoreModels.replace(index,model);
    return this;
}

bool DartsInputsDbContext::fetchModels(const IDartsInputBuilder *modelBuilder)
{
    auto future = readJson()->read();
    Runnable::runLater([=]{
        _dartsScoreModels << modelBuilder->createInputs(future.result());
    },future);
    return true;
}

QFuture<bool> DartsInputsDbContext::saveChanges(const IDartsInputJsonBuilder *jsonBuilder)
{
    QMutexLocker locker(&_mutex);
    auto json = jsonBuilder->json(_dartsScoreModels);
    return saveJson()->save(json);
}
