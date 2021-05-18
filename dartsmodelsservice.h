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
#include "igetdartspointbyparameters.h"
#include "igetdartsscorebyparameters.h"

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
    typedef IBinaryService<const QUuid&,const IDartsTournamentDb*,const IDartsTournament*> GetDartsTournamentByIdService;
    typedef IBinaryService<const QUuid&,const IDartsPointDb*, const DartsModelsContext::IDartsPointInput*> GetDartsPointByIdService;
    typedef QVector<const DartsModelsContext::IDartsPointInput*> PointModels;
    typedef QVector<const IDartsScoreInput*> ScoreModels;
    typedef IBinaryService<const QUuid &,
                           const IDartsPointDb*,
                           QVector<const DartsModelsContext::IDartsPointInput*>> GetOrderedDartsPointService;
    typedef IBinaryService<const QUuid &,
                           const IDartsScoreDb*,
                           QVector<const IDartsScoreInput*>> GetOrderedDartsScoreService;
    typedef ITernaryService<const QVector<const DartsModelsContext::IDartsPointInput *> &,
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
    typedef IBinaryService<const DartsModelsContext::IDartsPointInput*,const int&, const DartsModelsContext::IDartsPointInput*> SetDartsPointHint;
    typedef IBinaryService<const QUuid&,const IDartsPointDb*,QVector<const DartsModelsContext::IDartsPointInput*>> GetDartsPointModelsByTournamentIdService;
    typedef IBinaryService<const QUuid&,const IDartsScoreDb*,const IDartsScoreInput*> GetDartsScoreById;
    typedef IBinaryService<const QVector<int>&,IDartsTournamentDb*,bool> DeleteTournamentByIndexes;
    /*
     * Create and setup instance
     */
    static DartsModelsService *createInstance();
    /*
     * Darts tournament related section
     */
    const IDartsTournament *dartsTournamentModelById(const QUuid &tournamentId) const override;
    const IDartsTournament *dartsTournamentByIndex(const int &index) const override;
    QVector<const IDartsTournament *> dartsTournamentModels() const override;
    bool removeTournamentsByIndexes(const QVector<int>& indexes) const override;
    void tournamentSetWinnerId(const QUuid &tournamentId,
                               const QUuid &winnerId) override;
    void tournamentAssignPlayer(const QUuid &tournamentId,
                                  const QUuid &player) override;
    void tournamentAssignPlayers(const QUuid &tournamentId,
                                  const QVector<QUuid> &players) override;
    void tournamentUnAssignPlayer(const QUuid &tournamentId,
                                const QUuid &player) override;
    QUuid addDartsTournamentToDb(const IDartsTournament *tournament) override;
    const IDartsPointIndexes *dartsPointIndexes(const QUuid &tournamentId) const override;
    /*
     * Points related section
     */
    QVector<const DartsModelsContext::IDartsPointInput *> dartsPointModelsByTournamentId(const QUuid &tournamentId) const override;
    const DartsModelsContext::IDartsPointInput* getDartsPointModelById(const QUuid& pointId) const override;
    void addDartsPoint(const DartsModelsContext::IDartsPointInput *model) override;
    QVector<const DartsModelsContext::IDartsPointInput*> getDartsPointModelsOrdedByIndexes(const QUuid& tournamentId) const override;
    int dartsPointsCount(const QUuid& tournamentId,const int &hint) const override;
    const DartsModelsContext::IDartsPointInput* setDartsPointHint(const QUuid &tournamentId,
                                              const QUuid &playerId ,
                                              const int &round,
                                              const int &attempt,
                                              const int &hint) override;
    void removePointById(const QUuid &pointId) override;
    void removeHiddenPoints(const QUuid &tournament) override;
    void removePointsByTournamentId(const QUuid &tournament) override;
    void removePointModel(const QUuid &playerScore) override;
    /*
     * Scores methods
     */
    QVector<const IDartsScoreInput *> dartsScoreModelsByTournamentIdAndHint(const QUuid &tournamentId, const int &hint) const override;
    void addDartsScore(const IDartsScoreInput *pointModel) override;
    int dartsScoresCount(const int &hint) const override;
    const IDartsScoreInput* setDartsScoreHint(const QUuid &tournamentId,
                                              const QUuid &playerId,
                                              const int &roundIndex,
                                              const int &hint) override;
    void removeScoreById(const QUuid &scoreId) override;
    void removeHiddenScores(const QUuid &tournamentId) override;
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
    DartsModelsService* setGetDartsPointByParametersService(IGetDartsPointByParameters *pointModelsFilterByParameters);
    DartsModelsService* setGetTournamentByIndexService(GetTournamentByIndexService *newGetTournamentByIndexService);
    DartsModelsService* setGetDartsTournamentByIdService(GetDartsTournamentByIdService *getDartsTournamentByService);
    DartsModelsService* setDartsPointModelHintService(SetDartsPointHint *dartsPointModelHintService);
    DartsModelsService* setGetDartsPointByIdService(GetDartsPointByIdService *getDartsPointByIdService);
    DartsModelsService* setGetDartsPointModelsByTournamentId(GetDartsPointModelsByTournamentIdService *getDartsPointModelsByTournamentId);
    DartsModelsService* setGetDartsScoreByParametersService(IGetDartsScoreByParameters *getDartsScoreByParameters);
    DartsModelsService* setGetDartsScoreByIdService(GetDartsScoreById *getDartsScoreById);
    DartsModelsService* setDeleteTournamentsByIndexes(DeleteTournamentByIndexes *deleteTournamentsByIndexes);
    // set db service methods
    DartsModelsService *setDartsPointsDb(IDartsPointDb *dartsPointsDb);
    DartsModelsService* setDartsScoreDb(IDartsScoreDb *dartsScoreDb);
    DartsModelsService* setDartsScoresDb(IDartsScoreDb *dartsScoresDb);

private:
    /*
     * Services
     */
    // Point services
    GetDartsPointByIdService* _getDartsPointByIdService;
    GetDartsPointModelsByTournamentIdService* _getDartsPointModelsByTournamentId;
    GetOrderedDartsPointService* _getOrderedDartsPointsModels;
    GetPointIndexesFromDartsTournamentService* _assembleDartsPointIndexes;
    SetDartsPointHint* _dartsPointModelHintService;
    IGetDartsPointByParameters* _getPointModelByParameters;
    // Score services
    GetOrderedDartsScoreService* _getOrderedDartsScoreModels;
    GetScoreIndexesByDartsTournamentService* _getScoreIndexesByTournamentId;
    CountScoresByTournamentAndHint* _countScoresByTournamentAndHint;
    GetScoreModelsByTournamentId* _getScoreModelsByTournamentId;
    GetScoreModelsByPlayerId* _getScoreModelsByPlayerId;
    GetScoreModelsByRoundIndex* _getScoreModelsByRoundIndex;
    GetScoreModelsByHintService* _getScoreModelsByHint;
    SetDartsModelHint* _setScoreModelHintService;
    IGetDartsScoreByParameters* _getDartsScoreByParameters;
    GetDartsScoreById* _getDartsScoreById;
    // Tournament services
    GetTournamentByIndexService* _getDartsTournamentByIndexService;
    GetDartsTournamentByIdService* _getDartsTournamentByIdService;
    DeleteTournamentByIndexes* _deleteTournamentsByIndexes;
    // Db services
    IDartsTournamentDb* _tournamentsDbContext;
    IDartsPointDb* _dartsPointsDb;
    IDartsScoreDb* _dartsScoresDb;
};
#endif // TOURNAMENTMODELCONTEXT_H
