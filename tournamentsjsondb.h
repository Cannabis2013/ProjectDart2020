#ifndef TOURNAMENTSJSONDB_H
#define TOURNAMENTSJSONDB_H

#include "idbservice.h"
#include "idartstournament.h"
#include <quuid.h>
#include "jsonpersistence.h"
#include "icreatedartstournamentsfromjson.h"
#include "icreatejsonfromdartstournaments.h"


class TournamentsJsonDb :
        public IDbService,
        public JSONPersistence
{
public:
    TournamentsJsonDb(const QString &fileName);
    virtual void add(const IModel<QUuid> *model) override;
    virtual const IModel<QUuid> *model(const int &index) const override;
    virtual QVector<const IModel<QUuid>*> models() const override;
    virtual bool remove(const int &index) override;
    virtual int indexOf(const IModel<QUuid> *model) const override;
    virtual void replace(const int &index, const IModel<QUuid> *model) override;
    // IPersistence interface
    virtual void fetchModels() override;
    virtual void saveState() override;
    // Set service methods
protected:
    // Json services
    ICreateDartsTournamentModelsFromJson *_createModelsFromJson;
    ICreateJsonFromDartsTournaments* _createJsonFromModels;
private:
    const QString _fileName = "DartsTournaments";
    QVector<const IModel<QUuid>*> _dartsTournamentModels;
};

#endif // DARTSTOURNAMENTJSONDB_H
