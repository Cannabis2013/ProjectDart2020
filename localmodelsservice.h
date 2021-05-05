#ifndef MODELCONTEXTINTERFACE_H
#define MODELCONTEXTINTERFACE_H

#include <QVariantList>
#include "abstractmodelsservice.h"
#include "dartsmodelsservice.h"
#include "localplayermodelscontext.h"
#include "playermodelbuilder.h"
#include "playersjsondb.h"
#include "ibinaryservice.h"
#include "iunaryservice.h"
#include "assembledartstournamentmodelfromjson.h"
#include "assembleplayerindexesfromjson.h"
#include "assemblejsondartsindexes.h"
#include "jsonarrayfromplayernamesandids.h"
#include "jsonarrayfromdartspoints.h"
#include "getordereddartspointmodels.h"
#include "assemblejsonfromordereddartspointmodels.h"
#include "assembledartstournamentmodelfromjson.h"

class LocalModelsService : public AbstractModelsService
{
public:
    /*
     * Public types
     */
    enum TournamentModelsContextResponse{
        TournamentCreatedOK = 0x32,
        TournamentDeletedOK = 0x35,
        EndOfTransmission = 0x10,
        ModelsStatePersisted = 0x47
    };
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = HiddenHint | DisplayHint
    };
    /*
     * Destructor
     *  - Delete contexts to persists changes
     */
    ~LocalModelsService();
    /*
     * Create instance
     */
    static LocalModelsService* createInstance();

    LocalModelsService *setAssembleDartsTournamentFromJson(IUnaryService<const QByteArray &, const IDartsTournament<QUuid, QString> *> *assembleDartsTournamentFromJson);

    void setDartsModelsService(IDartsModelsService *dartsModelsService);
    void setPlayerModelsService(IPlayerModelsService *playerModelsContext);
    void setGetPlayerIndexesFromJson(IUnaryService<const QByteArray &,
                                     QVector<int> > *getPlayerIndexesFromJson);
    void setAssembleJsonObjectFromTournamentIndexes(IUnaryService<const QVector<int> &,
                                                    QJsonObject> *assembleJsonObjectFromTournamentIndexes);
    void setJsonArrayFromPlayerNamesAndIds(IBinaryService<const QVector<QUuid> &,
                                           const QVector<QString> &,
                                           QJsonArray> *JsonObjectFromPlayerNamesAndIds);
    void setJsonArrayFromDartsPoints(IBinaryService<const QUuid &,
                                     const IDartsModelsService *,
                                     QJsonArray> *JsonArrayFromDartsPoints);

    LocalModelsService *setAssembleJsonFromOrderedDartsPointModels(IBinaryService<const QVector<const IDartsPointInput<QUuid> *> &, const IPlayerModelsService *, const QByteArray> *assembleJsonFromOrderedDartsPointModels);

    LocalModelsService *setAssembleJsonFromDartsTournamentModel(IBinaryService<const IDartsTournament<QUuid, QString> *, const IPlayerModelsService *, const QByteArray> *assembleJsonFromDartsTournamentModel);

public slots:
    /*
     * General tournaments methods
     */
    void assignPlayersToTournament(const QUuid &tournament, const QList<QUuid> &playersID) override;
    void deleteTournaments(const QByteArray &json) override;
    void handleRequestGameMode(const int &index) override;
    void handleRequestTournaments() override;
    void resetTournament(const QUuid &tournament) override;
    /*
     * Darts tournaments methods
     */
    void addDartsTournament(const QByteArray &json) override;
    void getOrderedDartsPoints(const QUuid &tournamentId) override;
    void assembleDartsTournamentDataFromId(const QUuid& tournamentId) override;
    void addDartsPoint(const QByteArray& json) override;
    void addDartsScore(const QByteArray &json) override;
    /*
     * Send tournament values
     */
    void assembleDartsKeyValues(const QUuid& tournament) override;
    /*
     * Assemble First To Post tournament indexes and playerscores
     */
    virtual void assembleDartsIndexesAndPoints(const QUuid &tournament) override;
    virtual void assembleDartsIndexesAndScores(const QUuid &tournament) override;
    /*
     * Player models context related methods
     */
    void createPlayer(const QByteArray &json) override;
    void deletePlayerFromIndex(const QByteArray& json) override;

    void deletePlayersFromIndexes(const QByteArray& json) override;
    void handleRequestPlayersDetails() override;

    void hideDartsPoint(const QUuid& tournamentId,
                            const QUuid& playerId,
                            const int& roundIndex,
                            const int& attemptIndex) override;
    void revealPoint(const QUuid& tournamentId,
                         const QUuid& playerId,
                         const int& roundIndex,
                         const int& attemptIndex) override;
    void hideDartsScore(const QUuid &tournamentId, const QUuid &playerId, const int &roundIndex) override;
    void revealScore(const QUuid &tournamentId, const QUuid &playerId, const int &roundIndex) override;

private:
    /*
     * Services
     */
    IUnaryService<const QByteArray&,
                  const IDartsTournament<QUuid,QString>*>* _assembleDartsTournamentFromJson;
    IUnaryService<const QByteArray&,QVector<int>>* _getPlayerIndexesFromJson;
    IUnaryService<const QVector<int>&,QJsonObject>* _assembleJsonDartsIndexes;
    IBinaryService<const QVector<QUuid>&,const QVector<QString>&, QJsonArray>* _JsonArrayFromPlayerNamesAndIds;
    IBinaryService<const QUuid&,const IDartsModelsService*,QJsonArray>* _JsonArrayFromDartsPoints;
    IBinaryService<const QUuid&,const IDartsModelsService*,QJsonArray>* _JsonArrayFromDartsScores;
    IBinaryService<const QVector<const IDartsPointInput<QUuid>*>&,
                   const IPlayerModelsService*,const QByteArray>* _assembleJsonFromOrderedDartsPointModels;
    IBinaryService<const IDartsTournament<QUuid,QString>*,
                   const IPlayerModelsService*,
                   const QByteArray>* _assembleJsonFromDartsTournamentModel;
    IDartsModelsService* _dartsModelsService;
    IPlayerModelsService* _playerModelsService;
};

#endif // MODELCONTEXTINTERFACE_H
