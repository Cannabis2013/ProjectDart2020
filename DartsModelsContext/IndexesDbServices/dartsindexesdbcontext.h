#ifndef DARTSINDEXESDBCONTEXT_H
#define DARTSINDEXESDBCONTEXT_H

#include "modelsdbioservices.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindexesdbcontext.h"
#include "DartsModelsContext/IndexesDbSLAs/dartsindexdbslas.h"

class DartsIndexesDbContext : public IDartsIndexesDbContext,
                              protected ModelsDbIOSLAs
{
public:
    DartsIndexesDbContext(FileReaderInterface *fileReader, FileWriteInterface *fileWriter)
    {
        fileReader->setFileName(_fileName);
        fileWriter->setFileName(_fileName);
        setReadJsonFromFile(fileReader);
        setWriteJsonToFile(fileWriter);
    }
    virtual DartsIndexesDbContext *add(IModel<QUuid> *model)
    {
        _indexesModels << model;
        return this;
    }
    virtual IModel<QUuid> *model(const int &index) const
    {
        return _indexesModels.at(index);
    }
    virtual QVector<IModel<QUuid>*> models() const
    {
        return _indexesModels;
    }
    virtual DartsIndexesDbContext *remove(const int &index)
    {
        _indexesModels.remove(index);
        return this;
    }
    virtual int indexOf(IModel<QUuid> *model) const
    {
        for (int i = 0; i < _indexesModels.count(); ++i) {
            auto indexModel = _indexesModels.at(i);
            if (indexModel->id() == model->id())
                return i;
        }
        return -1;
    }
    virtual DartsIndexesDbContext *replace(const int &index, IModel<QUuid> *model)
    {
        _indexesModels.replace(index,model);
        return this;
    }
    virtual void fetchModels(const IDartsIndexesBuilder* modelBuilder)
    {
        _indexesModels = modelBuilder->indexes(readJsonFromFile()->read());
    }
    virtual void saveChanges(const IDartsIndexesJsonBuilder *jsonBuilder)
    {
        writeJsonToFile()->write(jsonBuilder->indexesModelsJson(_indexesModels));
    }
private:
    const QString _fileName = "DartsTournamentIndexes";
    QVector<IModel<QUuid>*> _indexesModels;
};
#endif // DARTSINDEXESDBCONTEXT_H
