#include "DartsModelsContext/TournamentsDbServices/dartsdbctx.h"
bool DartsDbCtx::fetch(const IDartsBuilder *modelBuilder)
{
    RunLater::run<QByteArray>(readJson()->read(),[=](const QByteArray &b){
        _models = modelBuilder->createTournaments(b);
    });
    return true;
}

QFuture<bool> DartsDbCtx::saveChanges(const IDartsJsonBuilder *jsonBuilder)
{
    return saveJson()->saveAsync(jsonBuilder->tournamentsjson(_models));
}

DartsDbCtx::DartsDbCtx(FileReaderInterface *fileReader, FileWriteInterface *fileWriter)
{
    fileReader->setFileName(_fileName);
    fileWriter->setFileName(_fileName);
    setReadJsonFromFile(fileReader);
    setWriteJsonToFile(fileWriter);
}

DartsDbCtx *DartsDbCtx::add(IModel<QUuid> *model)
{
    _models.append(model);
    return this;
}

IModel<QUuid> *DartsDbCtx::model(const int &index) const
{
    auto model = _models.at(index);
    return model;
}

IModel<QUuid> *DartsDbCtx::model(std::function<bool (IModel<QUuid> *)> predFunct) const
{
    for (const auto &model : _models) {
        if(predFunct(model))
            return model;
    }
    return nullptr;
}

QVector<IModel<QUuid> *> DartsDbCtx::models() const
{
    return _models;
}

QVector<IModel<QUuid> *> DartsDbCtx::models(std::function<bool (IModel<QUuid> *)> predFunct) const
{
    QVector<IModel<QUuid>*> models;
    for (const auto &model : _models) {
        if(predFunct(model))
            models << model;
    }
    return models;
}

DartsDbCtx *DartsDbCtx::remove(const int &index)
{
    _models.removeAt(index);
    return this;
}

IDartsDbContext *DartsDbCtx::remove(const QVector<int> &indexes)
{
    QVector<IModel<QUuid>*> models;
    for (int i = 0; i < _models.count(); ++i) {
        if(!indexes.contains(i))
            models << _models.at(i);
    }
    _models = models;
    return this;
}

int DartsDbCtx::indexOf(IModel<QUuid> *model) const
{
    auto index = _models.indexOf(model);
    return index;
}

DartsDbCtx *DartsDbCtx::replace(const int &index, IModel<QUuid> *model)
{
    _models.replace(index,model);
    return this;
}
