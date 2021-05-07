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
                           const IdartsPointDb<IDartsPointInput<QUuid> > *,
                           QVector<const IDartsPointInput<QUuid>*>> GetOrderedDartsPointService;
    typedef ITernaryService<const QVector<const IDartsPointInput<QUuid> *> &,
                            const IDartsTournament *,
                            const int &,
                            const IDartsPointIndexes *> GetPointIndexesFromDartsTournamentService;
    /*
     * Destructor
     */
    ~DartsModelsService();
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
    void addDartsPoint(const IDartsPointInput<QUuid> *model) override;
    QVector<const IDartsPointInput<QUuid>*> getDartsPointModelsOrdedByIndexes(const QUuid& tournamentId) const override;
    QUuid getDartsPointId(const QUuid &tournament,
                   const QUuid &player ,
                   const int &round,
                   const int &throwIndex,
                   const int &hint) const override;
    virtual QUuid getDartsPointId(const QUuid &tournament,
                           const QUuid &player ,
                           const int &round,
                           const int &attemptIndex) const override;
    QList<QUuid> dartsPointIds() const override;
    QList<QUuid> dartsPointIds(const QUuid &tournament) const override;
    QList<QUuid> dartsPointIds(const QUuid &tournament,
                        const int &roundID) const override;
    QList<QUuid> dartsPointIds(const QUuid &tournament,
                        const int &roundID,
                        const int &setID) override;
    QList<QUuid> dartsPointIds(const int &hint,
                        const QUuid &tournament) override;
    QList<QUuid> pointsByPlayerId(const QUuid &tournament,
                              const QUuid &player,
                              const int &hint) const override;
    int dartsPointsCount(const QUuid& tournamentId,const int &hint) const override;
    QUuid setDartsPointHint(const QUuid &point,
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
              const QUuid &player) const override;
    QList<QUuid> pointModels(const QUuid &player) override;
    void removePointsByTournamentId(const QUuid &tournament) override;
    void removePointModel(const QUuid &playerScore) override;
    QVector<int> dartsPointValuesByTournamentId(const QUuid &tournament) const override;
    /*
     * Scores methods
     */
    const IDartsScoreInput<QUuid> *assembleDartsScoresFromJson(const QByteArray &json) override;
    void addDartsScore(const IDartsScoreInput<QUuid> *) override;
    QUuid getDartsScoreId(const QUuid &tournament, const QUuid &player,
                          const int &round,
                          const int &hint) const override;
    QUuid getDartsScoreId(const QUuid &tournament,
                          const QUuid &player,
                          const int &round) const override;
    QList<QUuid> dartsScoreIds() const override;
    QList<QUuid> dartsScoreIds(const QUuid &tournament) const override;
    QList<QUuid> dartsScoreIds(const QUuid &tournament, const int &roundID) const override;
    QList<QUuid> dartsScoreIds(const QUuid &tournament, const int &roundID, const int &setID) const override;
    QList<QUuid> dartsScoreIds(const int &hint, const QUuid &tournament) const override;
    QList<QUuid> ScoresByPlayerId(const QUuid &tournament, const QUuid &player, const int &hint) const override;
    int dartsScoresCount(const int &hint) const override;
    QUuid setDartsScoreHint(const QUuid &point, const int &hint) override;
    int dartsScoreRoundIndex(const QUuid &) const override;
    int dartsScoreSetIndex(const QUuid &) const override;
    int ScoreValueFromScoreId(const QUuid &) const override;
    QUuid tournamentIdFromScoreId(const QUuid &playerScore) const override;
    QUuid playerIdFromScoreId(const QUuid &playerScore) const override;
    int ScoreHint(const QUuid &scoreID) const override;
    int ScoreKeyCode(const QUuid &) const override;
    void removeScoreById(const QUuid &) override;
    void removeHiddenScores(const QUuid &) override;
    int Score(const QUuid &, const QUuid &) const override;
    int Score(const QUuid &player) const override;
    QList<QUuid> ScoreModels(const QUuid &player) const override;
    void removeScoresByTournamentId(const QUuid &tournament) override;
    void removeScoreModel(const QUuid &playerScore) override;
    // Set services method
    DartsModelsService *setTournamentsDbContext(
            IDartsTournamentDb<IDartsTournament> *tournamentsDbContext);
    DartsModelsService *setDartsPointsDb(IdartsPointDb<IDartsPointInput<QUuid> > *dartsPointsDb);
    DartsModelsService* setGetOrderedDartsPointsModels(GetOrderedDartsPointService* getOrderedDartsPointsModels);
    DartsModelsService* setAssembleDartsPointIndexes(GetPointIndexesFromDartsTournamentService *getDartsPointIndexes);

private:
    /*
     * Services
     */
    IUnaryService<const QByteArray&,
    const IDartsTournament*>* _assembleDartsTournamentFromJson;
    GetOrderedDartsPointService* _getOrderedDartsPointsModels;
    template<typename TModelInterface>
    const TModelInterface *getTournamentModelFromId(const QUuid &id) const;
    GetPointIndexesFromDartsTournamentService* _assembleDartsPointIndexes;
    template<typename T = IModel<QUuid>>
    const T* getPointModelFromId(const QUuid &id) const;

    // Db services
    IDartsTournamentDb<IDartsTournament>* _tournamentsDbContext;
    IdartsPointDb<IDartsPointInput<QUuid>>* _dartsPointsDb;
};



#endif // TOURNAMENTMODELCONTEXT_H
