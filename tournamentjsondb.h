#ifndef DARTSTOURNAMENTJSONDB_H
#define DARTSTOURNAMENTJSONDB_H

#include "idartstournamentdb.h"

#include "idartstournament.h"
#include <quuid.h>
#include "abstractjsonpersistence.h"
#include "iunaryservice.h"

class DartsTournamentJSonDb :
        public IDartsTournamentDb<IDartsTournament<QUuid,QString>>,
        public AbstractJSONPersistence
{
public:
    void fetchModels() override;
    void saveState() override;
    void addTournament(const IDartsTournament<QUuid,QString> *model) override;
    const IDartsTournament<QUuid,QString> *dartsTournamentModelFromIndex(const int &) override;
    QVector<const IDartsTournament<QUuid,QString> *> dartsTournaments() override;
    void removeDartsTournamentModelByIndex(const int &index) override;
    int indexOfTournament(const IDartsTournament<QUuid,QString> *model) override;
    void replaceTournament(const int &index, const IDartsTournament<QUuid,QString> *tournament) override;
    // Set service methods
    void setDartsTournamentsExtractor(IUnaryService<const QJsonArray &, QVector<const IDartsTournament<QUuid, QString> *> > *dartsTournamentsExtractor);
    void setDartsTournamentAssembler(IUnaryService<const QVector<const IDartsTournament<QUuid, QString>*>&, QJsonArray> *dartsTournamentAssembler);

private:
    const QString _fileName = "DartsTournaments";
    // Json services
    IUnaryService<const QJsonArray&,QVector<const IDartsTournament<QUuid,QString>*>>* _dartsTournamentsExtractor;
    IUnaryService<const QVector<const IDartsTournament<QUuid,QString>*>&,QJsonArray>* _dartsTournamentAssembler;
    QVector<const IDartsTournament<QUuid,QString>*> _dartsTournamentModels;

};

#endif // DARTSTOURNAMENTJSONDB_H
