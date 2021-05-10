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
    typedef IBinaryService<const QUuid &,
                           const IdartsPointDb*,
                           QVector<const IDartsPointInput*>> GetOrderedDartsPointService;
    typedef ITernaryService<const QVector<const IDartsPointInput *> &,
                            const IDartsTournament *,
                            const int &,
                            const IDartsPointIndexes *> GetPointIndexesFromDartsTournamentService;
    /*
     * Create and setup instance
     */
    static DartsModelsService *createInstance();
    DartsModelsService* setup();

    /*
     * Darts tournament related section
     */
    const IDartsTournament *getDartsTournamentModelById(const QUuid &tournamentId) const override;
    QVector<const IDartsTournament *> getDartsTournamentModels() const override;
    bool removeTournamentsByIndexes(const QVector<int>& indexes) const override;
    QUuid tournamentIdFromIndex(const int &index) const override;
    QVector<QUuid> tournaments() const override;
    int tournamentsCount() const override;
    QString tournamentTitle(const QUuid &tournament) const override;
    int tournamentStatus(const QUuid &tournament) const override;
    QUuid tournamentWinnerId(const QUuid &tournament) const override;
    void tournamentSetWinnerId(const QUuid &tournament,
                               const QUuid &winner) override;
    QVector<QUuid> tournamentAssignedPlayers(const QUuid &tournament) const override;
    void tournamentAssignPlayer(const QUuid &tournament,
                                  const QUuid &player) override;
    void tournamentAssignPlayers(const QUuid &tournament,
                                  const QVector<QUuid> &players) override;
    void tournamentUnAssignPlayer(const QUuid &tournament,
                                const QUuid &player) override;
    QUuid addDartsTournamentToDb(const IDartsTournament *tournament) override;
    int tournamentAttempts(const QUuid &tournament) const override;
    int tournamentGameMode(const QUuid &tournament) const override;
    int tournamentTerminalKeyCode(const QUuid &tournament) const override;
    int tournamentKeyPoint(const QUuid &tournament) const override;
    int tournamentTableViewHint(const QUuid &tournament) const override;
    int tournamentInputMode(const QUuid &tournament) const override;
    const IDartsPointIndexes *dartsIndexes(const QUuid &tournament) const override;
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
    void addDartsScore(const IDartsScoreInput *pointModel) override;
    QUuid getDartsScoreId(const QUuid &tournament, const QUuid &player,
                          const int &round,
                          const int &hint) const override;
    QUuid getDartsScoreId(const QUuid &tournament,
                          const QUuid &player,
                          const int &round) const override;
    QVector<QUuid> dartsScoreIds() const override;
    QVector<QUuid> dartsScoreIds(const QUuid &tournament) const override;
    QVector<QUuid> dartsScoreIds(const QUuid &tournamentId, const int &roundIndex) const override;
    QVector<QUuid> dartsScoreIds(const QUuid &tournamentId, const int &roundIndex, const int &setIndex) const override;
    QVector<QUuid> dartsScoreIds(const int &hint, const QUuid &tournamentId) const override;
    QVector<QUuid> DartsScoresByPlayerId(const QUuid &tournamentId, const QUuid &playerId, const int &hint) const override;
    int dartsScoresCount(const int &hint) const override;
    const IDartsScoreInput* setDartsScoreHint(const QUuid &point, const int &hint) override;
    int dartsScoreRoundIndex(const QUuid &scoreId) const override;
    int dartsScoreSetIndex(const QUuid &scoreId) const override;
    int ScoreValueFromScoreId(const QUuid &scoreId) const override;
    QUuid tournamentIdFromScoreId(const QUuid &scoreId) const override;
    QUuid playerIdFromScoreId(const QUuid &scoreId) const override;
    int ScoreHint(const QUuid &scoreId) const override;
    void removeScoreById(const QUuid &scoreId) override;
    void removeHiddenScores(const QUuid &tournamentId) override;
    int Score(const QUuid &tournamentId, const QUuid &playerId) const override;
    QVector<QUuid> ScoreModels(const QUuid &playerId) const override;
    void removeScoresByTournamentId(const QUuid &tournamentId) override;
    void removeScoreModel(const QUuid &scoreId) override;
    // Set services method
    DartsModelsService *setTournamentsDbContext(
            IDartsTournamentDb *tournamentsDbContext);
    DartsModelsService *setDartsPointsDb(IdartsPointDb *dartsPointsDb);
    DartsModelsService* setGetOrderedDartsPointsModels(GetOrderedDartsPointService* getOrderedDartsPointsModels);
    DartsModelsService* setAssembleDartsPointIndexes(GetPointIndexesFromDartsTournamentService *getDartsPointIndexes);
    DartsModelsService* setDartsScoreDb(IDartsScoreDb *dartsScoreDb);
private:
    /*
     * Services
     */
    GetOrderedDartsPointService* _getOrderedDartsPointsModels;
    const IDartsTournament *getTournamentModelFromId(const QUuid &id) const;
    GetPointIndexesFromDartsTournamentService* _assembleDartsPointIndexes;
    const IDartsPointInput* getPointModelById(const QUuid &id) const;
    const IDartsScoreInput *getScoreModelById(const QUuid &id) const;

    // Db services
    IDartsTournamentDb* _tournamentsDbContext;
    IdartsPointDb* _dartsPointsDb;
    IDartsScoreDb* _dartsScoreDb;

};



#endif // TOURNAMENTMODELCONTEXT_H
