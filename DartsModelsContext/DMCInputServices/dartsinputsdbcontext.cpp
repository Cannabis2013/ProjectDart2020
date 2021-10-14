#include "DartsModelsContext/DMCInputServices/dartsinputsdbcontext.h"

DartsInputsDbContext::DartsInputsDbContext(FileReaderInterface *fileReader, FileWriteInterface *fileWriter)
{
    fileReader->setFileName(_fileName);
    fileWriter->setFileName(_fileName);
    setReadJsonFromFile(fileReader);
    setWriteJsonToFile(fileWriter);
}

DartsInputsDbContext *DartsInputsDbContext::add(IModel<QUuid> *model)
{
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

void DartsInputsDbContext::fetchModels(const IDartsInputBuilder *modelBuilder)
{
    try {
        _dartsScoreModels << modelBuilder->createInputs(readJsonFromFile()->read());
    }  catch (...) {
        return;
    }
}

void DartsInputsDbContext::saveChanges(const IDartsInputJsonBuilder *jsonBuilder)
{
    writeJsonToFile()->write(jsonBuilder->dartsInputsJson(_dartsScoreModels));
}
