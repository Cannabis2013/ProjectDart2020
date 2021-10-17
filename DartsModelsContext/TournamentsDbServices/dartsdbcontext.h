#ifndef DARTSDBCONTEXT_H
#define DARTSDBCONTEXT_H

#include "DartsModelsContext/TournamentsSLAs/abstractdartstournament.h"
#include "modelsdbioservices.h"
#include "DartsModelsContext/TournamentsDbSLAs/dartstournamentdbslas.h"
#include "DartsModelsContext/TournamentsDbSLAs/IDartsDbContext.h"
class DartsDbContext :
        public IDartsDbContext,
        public ModelsDbIOSLAs
{
public:
    DartsDbContext(FileReaderInterface *fileReader, FileWriteInterface *fileWriter);
    virtual DartsDbContext *add(IModel<QUuid> *model) override;
    virtual IModel<QUuid> *model(const int &index) const override;
    virtual QVector<IModel<QUuid>*> models() const override;
    virtual DartsDbContext *remove(const int &index) override;
    virtual IDartsDbContext *remove(const QVector<int> &indexes) override;
    virtual int indexOf(IModel<QUuid> *model) const override;
    virtual DartsDbContext *replace(const int &index, IModel<QUuid> *model) override;
    virtual void fetchModels(const IDartsBuilder *modelBuilder) override;
    virtual void saveChanges(const IDartsJsonBuilder *jsonBuilder) override;
private:
    const QString _fileName = "DartsTournamentModels";
    QVector<IModel<QUuid>*> _models;
};

#endif // DARTSTOURNAMENTJSONDB_H
