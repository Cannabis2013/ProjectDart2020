#include "DartsModelsContext/InputServices/dartsinputsdbcontext.h"

#include "AsyncUtils/runlater.h"
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
    _models << model;
    return this;
}

IModel<QUuid> *DartsInputsDbContext::model(const int &index) const
{
    auto model = _models.at(index);
    return model;
}

IModel<QUuid> *DartsInputsDbContext::model(std::function<bool (IModel<QUuid> *)> predFunct) const
{
    for (const auto &model : _models) {
        if(predFunct(model))
            return model;
    }
    return nullptr;
}

QVector<IModel<QUuid> *> DartsInputsDbContext::models() const
{
    QVector<IModel<QUuid>*> list;
    for (const auto& model : _models)
        list << model;
    return list;
}

QVector<IModel<QUuid> *> DartsInputsDbContext::models(std::function<bool (IModel<QUuid> *)> predFunct) const
{
    QVector<IModel<QUuid>*> models;
    for (const auto &model : _models) {
        if(predFunct(model))
            models << model;
    }
    return models;
}

DartsInputsDbContext *DartsInputsDbContext::remove(const int& index)
{
    QMutexLocker locker(&_mutex);
    _models.remove(index);
    return this;
}

int DartsInputsDbContext::indexOf(IModel<QUuid> *model) const
{
    auto indexOfModel = _models.indexOf(model);
    return indexOfModel;
}

DartsInputsDbContext *DartsInputsDbContext::replace(const int& index, IModel<QUuid> *model)
{
    _models.replace(index,model);
    return this;
}

bool DartsInputsDbContext::fetch(const IDartsInputBuilder *modelBuilder)
{
    RunLater::run<QByteArray>(readJson()->read(),[=](const QByteArray &result){
        _models << modelBuilder->createInputs(result);
    });
    return true;
}

QFuture<bool> DartsInputsDbContext::saveChanges(const IDartsInputJsonBuilder *jsonBuilder)
{
    QMutexLocker locker(&_mutex);
    auto json = jsonBuilder->json(_models);
    return saveJson()->saveAsync(json);
}
