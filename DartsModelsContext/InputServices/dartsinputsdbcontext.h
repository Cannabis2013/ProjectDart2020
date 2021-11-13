#ifndef DARTSINPUTSDBCONTEXT_H
#define DARTSINPUTSDBCONTEXT_H
#include "DartsModelsContext/TournamentsDbSLAs/dartstournamentdbslas.h"
#include "ModelsContext/DbSLAs/modelsdbioservices.h"
#include "DartsModelsContext/InputsDbSLAs/IDartsInputsDbContext.h"
#include <QMutexLocker>
#include <qmutex.h>
#include <qdebug.h>
#include <QtConcurrent/QtConcurrent>
class DartsInputsDbContext :
        public IDartsInputsDbContext,
        protected ModelsDbIOSLAs
{
public:
    DartsInputsDbContext(FileReaderInterface *fileReader, FileWriteInterface *fileWriter);
    DartsInputsDbContext *add(IModel<QUuid> *model) override;
    IModel<QUuid> *model(const int &index) const override;
    QVector<IModel<QUuid>*> models() const override;
    DartsInputsDbContext *remove(const int &index) override;
    int indexOf(IModel<QUuid>* model) const override;
    DartsInputsDbContext *replace(const int &index, IModel<QUuid> *model) override;
protected:
    bool fetchModels(const IDartsInputBuilder *modelBuilder) override;
    QFuture<bool> saveChanges(const IDartsInputJsonBuilder *jsonBuilder) override;
private:
    const QString _fileName = "DartsInputModels";
    QVector<IModel<QUuid>*> _dartsScoreModels;
    QMutex _mutex;
};
#endif // DARTSSCOREDB_H
