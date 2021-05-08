#ifndef MODELCONTEXTINTERFACE_H
#define MODELCONTEXTINTERFACE_H

#include "abstractmodelsservice.h"
#include "iplayermodelsservice.h"
#include "iunaryservice.h"
#include "ibinaryservice.h"
#include "idartsmodelsservice.h"
#include "dartsmodelsservicescollection.h"
#include "iplayermodel.h"
#include <QVariantList>

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

    LocalModelsService *setAssembleDartsTournamentFromJson(IUnaryService<const QByteArray &, const IDartsTournament*> *assembleDartsTournamentFromJson);

    LocalModelsService *setDartsModelsService(IDartsModelsService *dartsModelsService);
    LocalModelsService *setPlayerModelsService(IPlayerModelsService *playerModelsContext);
    LocalModelsService *setGetPlayerIndexesFromJson(IUnaryService<const QByteArray &,
                                     QVector<int> > *getPlayerIndexesFromJson);
    LocalModelsService *setAssembleJsonFromTournamentDartsPoints(IBinaryService<const QUuid &, const IDartsModelsService *, QByteArray> *JsonArrayFromDartsPoints);

    LocalModelsService *setAssembleJsonFromOrderedDartsPointModels(IBinaryService<const QVector<const IDartsPointInput<QUuid> *> &,
                                                                   const IPlayerModelsService *, const QByteArray> *assembleJsonFromOrderedDartsPointModels);
    LocalModelsService *setAssembleJsonFromDartsTournamentModel(IBinaryService<const IDartsTournament *,
                                                                const IPlayerModelsService*, const QByteArray> *assembleJsonFromDartsTournamentModel);
    LocalModelsService* setAssembleJsonDartsTournamentModels(IBinaryService<const IDartsModelsService *, const IPlayerModelsService*, const QByteArray> *assembleJsonDartsTournamentModels);
    LocalModelsService* setAssembleJsonDartsIndexes(IUnaryService<const IDartsPointIndexes *, QByteArray> *assembleJsonDartsIndexes);
    LocalModelsService* setAssembleJsonFromPlayerNamesAndIds(IBinaryService<const QVector<QUuid> &, const QVector<QString> &, QByteArray> *assembleJsonFromPlayerNamesAndIds);
    LocalModelsService* setAssembleJsonFromPlayerIdAndName(IBinaryService<const QUuid &, const QString &, QByteArray> *assembleJsonFromPlayerIdAndName);
    LocalModelsService* setAssembleJSonBasicTournamentValues(IUnaryService<const IDartsTournament *, QByteArray> *assembleJSonFromDartsTournamentModel);
    LocalModelsService* setGetTournamentIndexesFromJson(IUnaryService<const QByteArray &, QVector<int> > *getTournamentIndexesFromJson);
    LocalModelsService* setGetDeletePlayerIndexFromJson(IUnaryService<const QByteArray &, int> *getDeletePlayerIndexFromJson);
    LocalModelsService* setAssembleDartsPointModelFromJson(AssembleDartsPointService *assembleDartsPointModelFromJson);
    LocalModelsService* setAssemblePlayerModelFromJson(AssemblePlayerModelService *assemblePlayerModelFromJson);
    LocalModelsService* setAssignPlayerIdsToDartsTournament(AssignPlayerIdsService *assignPlayerIdsToDartsTournament);

    LocalModelsService* setAddPlayerNameToJsonPointModel(IBinaryService<const QByteArray &,
                                                                        const IPlayerModelsService *,
                                                                        QByteArray> *addPlayerNameToJsonPointModel);

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
    virtual void assembleDartsPointIndexes(const QUuid &tournament) override;
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
    void assembleAssignedPlayerEntities(const QUuid &tournamentId) override;
    void assembleAssignedPlayerPoints(const QUuid &tournamentId) override;
    void assembleDartsTournamentWinnerIdAndName(const QUuid &tournamentId) override;

private:
    /*
     * Services
     */
    IUnaryService<const QByteArray&,
                  const IDartsTournament*>* _assembleDartsTournamentFromJson;
    IUnaryService<const QByteArray&,QVector<int>>* _getPlayerIndexesFromJson;
    IUnaryService<const IDartsPointIndexes*,QByteArray>* _assembleJsonDartsIndexes;
    IBinaryService<const QVector<QUuid>&,
                   const QVector<QString>&,
                   QByteArray>* _assembleJsonFromPlayerNamesAndIds;
    IBinaryService<const QUuid&,
                   const IDartsModelsService*,
                   QByteArray>* _assembleJsonFromTournamentDartsPoints;
    IBinaryService<const QUuid&,
                   const IDartsModelsService*,
                   QJsonArray>* _JsonArrayFromDartsScores;
    IBinaryService<const QVector<const IDartsPointInput<QUuid>*>&,
                   const IPlayerModelsService*,const QByteArray>* _assembleJsonOrderedDartsPointModels;
    IBinaryService<const IDartsTournament*,
                   const IPlayerModelsService*,
                   const QByteArray>* _assembleJsonDartsTournamentModel;
    IBinaryService<const IDartsModelsService*,
                   const IPlayerModelsService*,
                   const QByteArray>* _assembleJsonDartsTournamentModels;
    IBinaryService<const IDartsModelsService*,
                   const IPlayerModelsService*,
                   const QByteArray>* _assembleJsonFromDartsIndexesAndPoints;
    IBinaryService<const QUuid&,const QString&,QByteArray>* _assembleJsonFromPlayerIdAndName;
    IUnaryService<const IDartsTournament*,QByteArray>* _assembleJSonFromDartsTournamentModel;
    IUnaryService<const QByteArray&,QVector<int>>* _getDeleteTournamentIndexesFromJson;
    IUnaryService<const QByteArray&,int>* _getDeletePlayerIndexFromJson;
    AssembleDartsPointService* _assembleDartsPointModelFromJson;
    AssemblePlayerModelService* _assemblePlayerModelFromJson;
    AssignPlayerIdsService* _assignPlayerIdsToDartsTournament;
    IBinaryService<const QByteArray&,
                   const IPlayerModelsService*,
                   QByteArray>* _addPlayerNameToJsonPointModel;
    // Model services
    IDartsModelsService* _dartsModelsService;
    IPlayerModelsService* _playerModelsService;
};

#endif // MODELCONTEXTINTERFACE_H
