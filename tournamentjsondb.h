#ifndef DARTSTOURNAMENTJSONDB_H
#define DARTSTOURNAMENTJSONDB_H

#include "idartstournamentdb.h"

#include "idartstournament.h"
#include <quuid.h>
#include "abstractjsonpersistence.h"
#include "iunaryservice.h"

class DartsTournamentJSonDb :
        public IDartsTournamentDb<IDartsTournament>,
        public AbstractJSONPersistence
{
public:
    typedef IUnaryService<const QJsonObject&,QVector<const IDartsTournament*>> JsonExtractor;
    typedef IUnaryService<const QVector<const IDartsTournament*>&,QJsonObject> JsonAssembler;
    static DartsTournamentJSonDb* createInstance(JsonExtractor* jsonExtractor,
                                                 JsonAssembler* jsonAssembler);
    void fetchModels() override;
    void saveState() override;
    void addTournament(const IDartsTournament *model) override;
    const IDartsTournament *dartsTournamentModelFromIndex(const int &) override;
    QVector<const IDartsTournament *> dartsTournaments() override;
    void removeDartsTournamentModelByIndex(const int &index) override;
    int indexOfTournament(const IDartsTournament *model) override;
    void replaceTournament(const int &index, const IDartsTournament *tournament) override;
    // Set service methods
    void setDartsTournamentsExtractor(JsonExtractor* dartsTournamentsExtractor);
    void setDartsTournamentAssembler(JsonAssembler* dartsTournamentAssembler);
private:
    const QString _fileName = "DartsTournaments";
    // Json services
    JsonExtractor* _dartsTournamentsExtractor;
    JsonAssembler* _dartsTournamentAssembler;
    QVector<const IDartsTournament*> _dartsTournamentModels;

};

#endif // DARTSTOURNAMENTJSONDB_H
