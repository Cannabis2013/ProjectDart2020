#ifndef DARTSDBCTX_H
#define DARTSDBCTX_H

#include "DartsModelsContext/TournamentModelsSLAs/abstractdartstournament.h"
#include "ModelsContext/DbSLAs/modelsdbioservices.h"
#include "DartsModelsContext/TournamentsDbSLAs/dartstournamentdbslas.h"
#include "DartsModelsContext/TournamentsDbSLAs/IDartsDbContext.h"
#include "AsyncUtils/runlater.h"
class DartsDbCtx :
        public IDartsDbContext,
        public ModelsDbIOSLAs
{
public:
    DartsDbCtx(FileReaderInterface *fileReader, FileWriteInterface *fileWriter);
    virtual DartsDbCtx *add(IModel<QUuid> *model) override;
    virtual IModel<QUuid> *model(const int &index) const override;
    IModel<QUuid>* model(std::function<bool (IModel<QUuid>*)> predFunct) const override;
    virtual QVector<IModel<QUuid>*> models() const override;
    virtual QVector<IModel<QUuid>*> models(std::function<bool (IModel<QUuid> *)> predFunct) const override;
    virtual DartsDbCtx *remove(const int &index) override;
    virtual IDartsDbContext *remove(const QVector<int> &indexes) override;
    virtual int indexOf(IModel<QUuid> *model) const override;
    virtual DartsDbCtx *replace(const int &index, IModel<QUuid> *model) override;
    virtual bool fetch(const IDartsBuilder *modelBuilder) override;
    virtual QFuture<bool> saveChanges(const IDartsJsonBuilder *jsonBuilder) override;
private:
    const QString _fileName = "DartsTournamentModels";
    QVector<IModel<QUuid>*> _models;
};

#endif // DARTSTOURNAMENTJSONDB_H
