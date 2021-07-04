#ifndef TOURNAMENTSJSONDB_H
#define TOURNAMENTSJSONDB_H

#include "idartstournamentdb.h"

#include "idartstournament.h"
#include <quuid.h>
#include "jsonpersistence.h"
#include "icreatedartstournamentsfromjson.h"
#include "icreatejsonfromdartstournaments.h"


class TournamentsJsonDb :
        public IDartsTournamentDb,
        public JSONPersistence
{
public:
    TournamentsJsonDb(const QString &fileName);
    virtual void add(const Model *model) override;
    virtual const Model *model(const int &index) const override;
    virtual QVector<const Model *> models() const override;
    virtual bool remove(const int &index) override;
    virtual int indexOf(const Model *model) const override;
    virtual void replace(const int &index, const Model *model) override;
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
    QVector<const ITournament*> _dartsTournamentModels;
};

#endif // DARTSTOURNAMENTJSONDB_H
