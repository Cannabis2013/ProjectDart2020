#ifndef TOURNAMENTSJSONDB_H
#define TOURNAMENTSJSONDB_H

#include "ModelsContext/imodelsdbcontext.h"
#include "abstractdartstournament.h"
#include "modelsdbioservices.h"
#include "modelsdbjsonservices.h"

class TournamentsJsonDb :
        public IModelsDbContext,
        public ModelsDbJsonServices,
        public ModelsDbIOServices
{
public:
    virtual void add(const IModel<QUuid> *model) override;
    virtual const IModel<QUuid> *model(const int &index) const override;
    virtual QVector<const IModel<QUuid>*> models() const override;
    virtual bool remove(const int &index) override;
    virtual int indexOf(const IModel<QUuid> *model) const override;
    virtual void replace(const int &index, const IModel<QUuid> *model) override;
    virtual void fetchModels() override;
    virtual void saveState() override;
private:
    const QString _fileName = "DartsTournaments";
    QVector<const IModel<QUuid>*> _models;
};

#endif // DARTSTOURNAMENTJSONDB_H
