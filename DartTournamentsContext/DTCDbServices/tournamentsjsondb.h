#ifndef TOURNAMENTSJSONDB_H
#define TOURNAMENTSJSONDB_H

#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"
#include "DartsModelsContext/DMCTournamentSLAs/abstractdartstournament.h"
#include "modelsdbioservices.h"
#include "ModelsContext/MCJsonSLAs/modelsdbjsonslas.h"

class TournamentsJsonDb :
        public IModelsDbContext,
        public ModelsDbJsonSLAs,
        public ModelsDbIOSLAs
{
public:
    TournamentsJsonDb(const QString &fileName):
        _fileName(fileName){}
    virtual void add(const IModel<QUuid> *model) override;
    virtual const IModel<QUuid> *model(const int &index) const override;
    virtual QVector<const IModel<QUuid>*> models() const override;
    virtual bool remove(const int &index) override;
    virtual int indexOf(const IModel<QUuid> *model) const override;
    virtual void replace(const int &index, const IModel<QUuid> *model) override;
    virtual void fetchModels() override;
    virtual void saveState() override;
protected:
    const QString _fileName;
private:
    QVector<const IModel<QUuid>*> _models;
};

#endif // DARTSTOURNAMENTJSONDB_H
