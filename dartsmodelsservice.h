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
    const IDartsTournament<QUuid, QString> *getDartsTournamentById(const QUuid &tournamentId) const override;
    bool removeTournamentsByIndexes(const QVector<int>& indexes) override;
    QUuid tournamentIdFromIndex(const int &index) override;
    QVector<QUuid> tournaments() override;
    int tournamentsCount() override;
    QString tournamentTitle(const QUuid &tournament) override;
    int tournamentStatus(const QUuid &tournament) override;
    QUuid tournamentWinner(const QUuid &tournament) override;
    void tournamentSetWinnerId(const QUuid &tournament,
                               const QUuid &winner) override;
    QVector<QUuid> tournamentAssignedPlayers(const QUuid &tournament) override;
    void tournamentAssignPlayer(const QUuid &tournament,
                                  const QUuid &player) override;
    void tournamentAssignPlayers(const QUuid &tournament,
                                  const QVector<QUuid> &players) override;
    void tournamentUnAssignPlayer(const QUuid &tournament,
                                const QUuid &player) override;
    const IDartsTournament<QUuid,QString>* assembleDartsTournamentFromJson(const QByteArray& json) override;
    QUuid addDartsTournamentToDb(const IDartsTournament<QUuid, QString> *tournament) override;
    int tournamentAttempts(const QUuid &tournament) override;
    int tournamentGameMode(const QUuid &tournament) override;
    int tournamentTerminalKeyCode(const QUuid &tournament) override;
    int tournamentKeyPoint(const QUuid &tournament) override;
    int tournamentTableViewHint(const QUuid &tournament) override;
    int tournamentInputMode(const QUuid &tournament) override;
    const QVector<int> dartsIndexes(const QUuid &tournament) override;
    /*
     * Points related section
     */
    const IDartsPointInput<QUuid>* assembleDartsInputPointFromJson(const QByteArray& json) override;
    void addDartsPoint(const IDartsPointInput<QUuid> *model) override;
    QVector<const IDartsPointInput<QUuid>*> getDartsPointModelsOrdedByIndexes(const QUuid& tournamentId) const override;
    QUuid getDartsPointId(const QUuid &tournament,
                   const QUuid &player ,
                   const int &round,
                   const int &throwIndex,
                   const int &hint) override;
    virtual QUuid getDartsPointId(const QUuid &tournament,
                           const QUuid &player ,
                           const int &round,
                           const int &attemptIndex) override;
    QList<QUuid> dartsPointIds() const override;
    QList<QUuid> dartsPointIds(const QUuid &tournament) const override;
    QList<QUuid> dartsPointIds(const QUuid &tournament,
                        const int &roundID) override;
    QList<QUuid> dartsPointIds(const QUuid &tournament,
                        const int &roundID,
                        const int &setID) override;
    QList<QUuid> dartsPointIds(const int &hint,
                        const QUuid &tournament) override;
    QList<QUuid> pointsByPlayerId(const QUuid &tournament,
                              const QUuid &player,
                              const int &hint) override;
    int dartsPointsCount(const int &hint) override;
    QUuid setDartsPointHint(const QUuid &point,
                       const int &hint) override;
    int dartsPointRoundIndex(const QUuid &playerScore) override;
    int dartsPointSetIndex(const QUuid &playerScore) override;
    int dartsPointAttemptIndex(const QUuid &playerScore) override;
    int pointValueFromPointId(const QUuid &playerScore) const override;
    QUuid tournamentIdFromPointId(const QUuid &playerScore) override;
    QUuid playerIdFromPointId(const QUuid &playerScore) const override;
    int pointHint(const QUuid &scoreID) override;
    int pointKeyCode(const QUuid &scoreID) const  override;
    void removePointById(const QUuid &point) override;

    void removeHiddenPoints(const QUuid &tournament) override;

    int point(const QUuid &tournament,
              const QUuid &player) override;
    int point(const QUuid &player) override;
    QList<QUuid> pointModels(const QUuid &player) override;
    void removePointsByTournamentId(const QUuid &tournament) override;
    void removePointModel(const QUuid &playerScore) override;
    QVector<int> dartsPointValuesByTournamentId(const QUuid &tournament) override;
    /*
     * Scores methods
     */
    const IDartsScoreInput<QUuid> *assembleDartsScoresFromJson(const QByteArray &json) override;
    void addDartsScore(const IDartsScoreInput<QUuid> *) override;
    QUuid getDartsScoreId(const QUuid &tournament, const QUuid &player,
                          const int &round,
                          const int &hint) override;
    QUuid getDartsScoreId(const QUuid &tournament,
                          const QUuid &player,
                          const int &round) override;
    QList<QUuid> dartsScoreIds() const override;
    QList<QUuid> dartsScoreIds(const QUuid &tournament) const override;
    QList<QUuid> dartsScoreIds(const QUuid &tournament, const int &roundID) override;
    QList<QUuid> dartsScoreIds(const QUuid &tournament, const int &roundID, const int &setID) override;
    QList<QUuid> dartsScoreIds(const int &hint, const QUuid &tournament) override;
    QList<QUuid> ScoresByPlayerId(const QUuid &tournament, const QUuid &player, const int &hint) override;
    int dartsScoresCount(const int &hint) override;
    QUuid setDartsScoreHint(const QUuid &point, const int &hint) override;
    int dartsScoreRoundIndex(const QUuid &) override;
    int dartsScoreSetIndex(const QUuid &) override;
    int ScoreValueFromScoreId(const QUuid &) const override;
    QUuid tournamentIdFromScoreId(const QUuid &playerScore) override;
    QUuid playerIdFromScoreId(const QUuid &playerScore) const override;
    int ScoreHint(const QUuid &scoreID) override;
    int ScoreKeyCode(const QUuid &) const override;
    void removeScoreById(const QUuid &) override;
    void removeHiddenScores(const QUuid &) override;
    int Score(const QUuid &, const QUuid &) override;
    int Score(const QUuid &player) override;
    QList<QUuid> ScoreModels(const QUuid &player) override;
    void removeScoresByTournamentId(const QUuid &tournament) override;
    void removeScoreModel(const QUuid &playerScore) override;
    // Set services method
    void setTournamentsDbContext(IDartsTournamentDb<IDartsTournament<QUuid, QString> > *tournamentsDbContext);

    void setAssembleDartsInputPointFromJson(IUnaryService<const QByteArray &, const IDartsPointInput<QUuid> *> *assembleDartsInputPointFromJson);
    DartsModelsService *setAssembleDartsTournamentFromJson(IUnaryService<const QByteArray &, const IDartsTournament<QUuid, QString> *> *assembleDartsTournamentFromJson);

    DartsModelsService *setGetOrderedDartsPointsModels(IBinaryService<const QUuid &, const IdartsPointDb<IDartsPointInput<QUuid> > *, QVector<const IDartsPointInput<QUuid> *> > *getOrderedDartsPointsModels);

private:
    /*
     * Services
     */
    IUnaryService<const QByteArray&,
    const IDartsTournament<QUuid,QString>*>* _assembleDartsTournamentFromJson;
    IUnaryService<const QByteArray&,const IDartsPointInput<QUuid>*>* _assembleDartsInputPointFromJson;
    IBinaryService<const QUuid&,const IdartsPointDb<IDartsPointInput<QUuid>>*,
                  QVector<const IDartsPointInput<QUuid>*>>* _getOrderedDartsPointsModels;
    /*
     * Get tournament model
     */
    template<typename TModelInterface>
    const TModelInterface *getTournamentModelFromId(const QUuid &id);
    template<typename T = IModel<QUuid>>
    const T* getPointModelFromId(const QUuid &id) const;

    IModelsDbContext* _dbContext;
    IDartsTournamentDb<IDartsTournament<QUuid,QString>>* _tournamentsDbContext;
    IdartsPointDb<IDartsPointInput<QUuid>>* _dartsPointsDb;
};

#endif // TOURNAMENTMODELCONTEXT_H
