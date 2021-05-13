#ifndef TOURNAMENTMODELCONTEXT_H
#define TOURNAMENTMODELCONTEXT_H

#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qfile.h>

#include "imodelsdbcontext.h"
#include "idartsmodelsservice.h"
#include "abstractjsonpersistence.h"
#include "idartspointinput.h"
#include "idartsscoreinput.h"
#include "idartstournamentdb.h"
#include "idartspointdb.h"
#include "iunaryservice.h"
#include "ibinaryservice.h"
#include "iternaryservice.h"
#include "idartspointindexes.h"
#include "idartsscoredb.h"
#include "idartsscoreindexes.h"

#define THROW_OBJECT_WITH_ID_NOT_FOUND(x) QString("Model with ID: '%1' does not exists in the current context").arg(x).toStdString();
#define THROW_OBJECT_WITH_INDEX_NOT_FOUND(x) QString("Model with index: '%1' does not exists in the current context").arg(x).toStdString();

/*
 * Context responsibilities
 *  - Get and modify data values from data storage class containers
 *  - Build and persist data storage class containers by the help of appropriate services
 */

class DartsModelsService :
        public IDartsModelsService
{
public:
    /*
     * Public types
     */
    enum GameModes {
        FirstToPost = 0x1,
        RoundLimit =0x2,
        Circular = 0x3,
        Cricket = 0x4
    };

    enum ModelsContextResponse{
        TournamentCreatedOK = 0x32,
        TournamentDeletedOK = 0x35,
        EndOfTransmission = 0x10,
        TournamentDetailsFailed
    };
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = 0x3
    };
    typedef IBinaryService<const int&,const IDartsTournamentDb*,const IDartsTournament*> GetTournamentByIndexService;
    typedef QVector<const IDartsScoreInput*> ScoreModels;
    typedef IBinaryService<const QUuid &,
                           const IDartsPointDb*,
                           QVector<const IDartsPointInput*>> GetOrderedDartsPointService;
    typedef IBinaryService<const QUuid &,
                           const IDartsScoreDb*,
                           QVector<const IDartsScoreInput*>> GetOrderedDartsScoreService;
    typedef ITernaryService<const QVector<const IDartsPointInput *> &,
                            const IDartsTournament *,
                            const int &,
                            const IDartsPointIndexes *> GetPointIndexesFromDartsTournamentService;
    typedef ITernaryService<const QVector<const IDartsScoreInput*>&,
                            const IDartsTournament*,
                            const int&,
                            const IDartsScoreIndexes*> GetScoreIndexesByDartsTournamentService;
    typedef ITernaryService<const QUuid&,const int&, const IDartsScoreDb*,int> CountScoresByTournamentAndHint;
    typedef IBinaryService<const ScoreModels&,const QUuid&,ScoreModels> GetScoreModelsByTournamentId;
    typedef IBinaryService<const ScoreModels&,const QUuid&,ScoreModels> GetScoreModelsByPlayerId;
    typedef IBinaryService<const ScoreModels&,const int&,ScoreModels> GetScoreModelsByRoundIndex;
    typedef IBinaryService<const ScoreModels&,const int&,ScoreModels> GetScoreModelsByHintService;
    typedef IBinaryService<const IDartsScoreInput*,const int&,const IDartsScoreInput*> SetDartsModelHint;
    /*
     * Create and setup instance
     */
    static DartsModelsService *createInstance();
    DartsModelsService* setup();

    /*
     * Darts tournament related section
     */
    const IDartsTournament *dartsTournamentModelById(const QUuid &tournamentId) const override;
    const IDartsTournament *dartsTournamentByIndex(const int &index) const override;
    QVector<const IDartsTournament *> dartsTournamentModels() const override;
    bool removeTournamentsByIndexes(const QVector<int>& indexes) const override;
    QUuid tournamentIdFromIndex(const int &index) const override;
    QVector<QUuid> tournaments() const override;
    void tournamentSetWinnerId(const QUuid &tournament,
                               const QUuid &winner) override;
    void tournamentAssignPlayer(const QUuid &tournament,
                                  const QUuid &player) override;
    void tournamentAssignPlayers(const QUuid &tournament,
                                  const QVector<QUuid> &players) override;
    void tournamentUnAssignPlayer(const QUuid &tournament,
                                const QUuid &player) override;
    QUuid addDartsTournamentToDb(const IDartsTournament *tournament) override;
    const IDartsPointIndexes *dartsPointIndexes(const QUuid &tournament) const override;
    /*
     * Points related section
     */
    const IDartsPointInput* getDartsPointModelById(const QUuid& id) const override;
    void addDartsPoint(const IDartsPointInput *model) override;
    QVector<const IDartsPointInput*> getDartsPointModelsOrdedByIndexes(const QUuid& tournamentId) const override;
    QUuid getDartsPointId(const QUuid &tournament,
                          const QUuid &player ,
                          const int &round,
                          const int &throwIndex,
                          const int &hint) const override;
    virtual QUuid getDartsPointId(const QUuid &tournament,
                           const QUuid &player ,
                           const int &round,
                           const int &attemptIndex) const override;
    QVector<QUuid> dartsPointIds() const override;
    QVector<QUuid> dartsPointIds(const QUuid &tournament) const override;
    QVector<QUuid> dartsPointIds(const QUuid &tournament,
                        const int &roundID) const override;
    QVector<QUuid> dartsPointIds(const QUuid &tournament,
                        const int &roundID,
                        const int &setID) override;
    QVector<QUuid> dartsPointIds(const int &hint,
                        const QUuid &tournament) override;
    QVector<QUuid> pointsByPlayerId(const QUuid &tournament,
                              const QUuid &player,
                              const int &hint) const override;
    int dartsPointsCount(const QUuid& tournamentId,const int &hint) const override;
    const IDartsPointInput* setDartsPointHint(const QUuid &point,
                       const int &hint) override;
    int dartsPointRoundIndex(const QUuid &playerScore) const override;
    int dartsPointSetIndex(const QUuid &playerScore) const override;
    int dartsPointAttemptIndex(const QUuid &playerScore) const override;
    int pointValueFromPointId(const QUuid &playerScore) const override;
    QUuid tournamentIdFromPointId(const QUuid &playerScore) const override;
    QUuid playerIdFromPointId(const QUuid &playerScore) const override;
    int pointHint(const QUuid &scoreID) const override;
    int pointKeyCode(const QUuid &scoreID) const  override;
    void removePointById(const QUuid &point) override;

    void removeHiddenPoints(const QUuid &tournament) override;

    int point(const QUuid &tournament,
              const QUuid &playerId) const override;
    QVector<QUuid> pointModels(const QUuid &player) override;
    void removePointsByTournamentId(const QUuid &tournament) override;
    void removePointModel(const QUuid &playerScore) override;
    QVector<int> dartsPointValuesByTournamentId(const QUuid &tournament) const override;
    /*
     * Scores methods
     */
    QVector<const IDartsScoreInput *> dartsScoreModelsByTournamentIdAndHint(const QUuid &tournamentId, const int &hint) const override;
    void addDartsScore(const IDartsScoreInput *pointModel) override;
    QUuid getDartsScoreId(const QUuid &tournamentId,
                          const QUuid &playerId,
                          const int &roundIndex) const override;
    QVector<QUuid> dartsScoreIds() const override;
    QVector<QUuid> dartsScoreIds(const QUuid &tournament) const override;
    QVector<QUuid> dartsScoreIds(const QUuid &tournamentId, const int &roundIndex) const override;
    QVector<QUuid> dartsScoreIds(const QUuid &tournamentId, const int &roundIndex, const int &setIndex) const override;
    QVector<QUuid> dartsScoreIds(const int &hint, const QUuid &tournamentId) const override;
    QVector<QUuid> DartsScoresByPlayerId(const QUuid &tournamentId, const QUuid &playerId, const int &hint) const override;
    int dartsScoresCount(const int &hint) const override;
    const IDartsScoreInput* setDartsScoreHint(const QUuid &scoreId, const int &hint) override;
    int dartsScoreRoundIndex(const QUuid &scoreId) const override;
    int dartsScoreSetIndex(const QUuid &scoreId) const override;
    int ScoreValueFromScoreId(const QUuid &scoreId) const override;
    QUuid tournamentIdFromScoreId(const QUuid &scoreId) const override;
    QUuid playerIdFromScoreId(const QUuid &scoreId) const override;
    int dartsScoreHint(const QUuid &scoreId) const override;
    void removeScoreById(const QUuid &scoreId) override;
    void removeHiddenScores(const QUuid &tournamentId) override;
    int dartsScoreId(const QUuid &tournamentId, const QUuid &playerId) const override;
    QVector<QUuid> scoreModelsByPlayerId(const QUuid &playerId) const override;
    void removeScoresByTournamentId(const QUuid &tournamentId) override;
    void removeScoreModel(const QUuid &scoreId) override;
    const IDartsScoreIndexes *dartsScoreIndexes(const QUuid &tournamentId) const override;
    int dartsScoreCount(const QUuid &tournamentId, const int &hint) const override;
    // Set services method
    DartsModelsService *setTournamentsDbContext(
            IDartsTournamentDb *tournamentsDbContext);
    DartsModelsService* setGetOrderedDartsPointsModels(GetOrderedDartsPointService* getOrderedDartsPointsModels);
    DartsModelsService* setAssembleDartsPointIndexes(GetPointIndexesFromDartsTournamentService *getDartsPointIndexes);
    DartsModelsService* setGetOrderedDartsScoreModels(GetOrderedDartsScoreService *getOrderedDartsScoreModels);
    DartsModelsService* setGetScoreIndexesByTournamentId(GetScoreIndexesByDartsTournamentService *getScoreIndexesByTournamentId);
    DartsModelsService* setCountScoresByTournamentAndHint(CountScoresByTournamentAndHint *countScoresByTournamentAndHint);
    DartsModelsService* setGetScoreModelsByTournamentId(GetScoreModelsByTournamentId *getScoreModelsByTournamentId);
    DartsModelsService* setGetScoreModelsByPlayerId(GetScoreModelsByPlayerId *getScoreModelsByPlayerId);
    DartsModelsService* setGetScoreModelsByRoundIndex(GetScoreModelsByRoundIndex *getScoreModelsByRoundIndex);
    DartsModelsService* setDartsScoreModelHintService(SetDartsModelHint *setScoreModelHintService);
    DartsModelsService* setGetScoreModelsByHint(GetScoreModelsByHintService *getScoreModelsByHint);
    // set db service methods
    DartsModelsService *setDartsPointsDb(IDartsPointDb *dartsPointsDb);
    DartsModelsService* setDartsScoreDb(IDartsScoreDb *dartsScoreDb);
    DartsModelsService* setDartsScoresDb(IDartsScoreDb *dartsScoresDb);
    DartsModelsService* setGetTournamentByIndexService(GetTournamentByIndexService *newGetTournamentByIndexService);

private:
    /*
     * Services
     */

    GetOrderedDartsPointService* _getOrderedDartsPointsModels;
    GetOrderedDartsScoreService* _getOrderedDartsScoreModels;
    const IDartsTournament *getTournamentModelFromId(const QUuid &id) const;
    GetPointIndexesFromDartsTournamentService* _assembleDartsPointIndexes;
    GetScoreIndexesByDartsTournamentService* _getScoreIndexesByTournamentId;
    const IDartsPointInput* getPointModelById(const QUuid &id) const;
    const IDartsScoreInput *getScoreModelById(const QUuid &id) const;
    CountScoresByTournamentAndHint* _countScoresByTournamentAndHint;
    GetScoreModelsByTournamentId* _getScoreModelsByTournamentId;
    GetScoreModelsByPlayerId* _getScoreModelsByPlayerId;
    GetScoreModelsByRoundIndex* _getScoreModelsByRoundIndex;
    GetScoreModelsByHintService* _getScoreModelsByHint;
    SetDartsModelHint* _setScoreModelHintService;
    GetTournamentByIndexService* _getTournamentByIndexService;
    // Db services
    IDartsTournamentDb* _tournamentsDbContext;
    IDartsPointDb* _dartsPointsDb;
    IDartsScoreDb* _dartsScoresDb;
};
#endif // TOURNAMENTMODELCONTEXT_H
