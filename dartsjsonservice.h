#ifndef DARTSMODELSJSONSERVICE_H
#define DARTSMODELSJSONSERVICE_H

#include "idartsjsonservice.h"
#include "iunaryservice.h"
#include "ibinaryservice.h"
#include "dartsscoreinput.h"

class DartsJsonService :
        public IDartsJsonService
{

    // IDartsModelsJsonService interface
public:
    static DartsJsonService* createInstance();
    const IDartsTournament *assembleDartsTournamentFromJson(const QByteArray &json) const override;
    QVector<int> getPlayerIndexesFromJson(const QByteArray &json) const override;
    QByteArray assembleJsonDartsPointIndexes(const IDartsPointIndexes *indexes) const override;
    QByteArray assembleJsonDartsScoreIndexes(const IDartsScoreIndexes *indexes) const override;
    QByteArray assembleJsonFromPlayerNamesAndIds(const QVector<QUuid> &playerIds, const QVector<QString> &playerNames) const override;
    QByteArray assembleJsonFromTournamentDartsPoints(const QUuid &tournamentId, const IDartsModelsService *dartsModelsService) const override;
    QJsonArray jsonArrayFromDartsScores(const QUuid &tournamentId, const IDartsModelsService *dartsModelsService) const override;
    QByteArray assembleJsonOrderedDartsPointModels(const QVector<const DartsModelsContext::IDartsPointInput *> &pointModels, const IPlayerModelsService *playerModelsService) const override;
    QByteArray addPlayerNamesToDartsTournamentJson(const QByteArray& json, const QVector<QString>& names) const override;
    QByteArray addWinnerNameToDartsTournamentJson(const QByteArray&json, const QString& name) const override;
    QByteArray assembleJsonDartsTournamentModels(const IDartsModelsService *dartsModelsService, const IPlayerModelsService *iplayerModelsService) const override;
    QByteArray assembleJsonByPlayerIdAndName(const QUuid &playerId, const QString &playerName) const override;
    QByteArray assembleJsonFromDartsTournamentModel(const IDartsTournament *model) const override;
    QVector<int> getDeleteTournamentIndexesFromJson(const QByteArray &json) const override;
    int getDeletePlayerIndexFromJson(const QByteArray &json) const override;
    const DartsModelsContext::IDartsPointInput *assembleDartsPointModelFromJson(const QByteArray &json) const override;
    const IPlayerModel *assemblePlayerModelFromJson(const QByteArray &json) const override;
    const IDartsTournament *assignPlayerIdsToDartsTournament(const IDartsTournament *model, const QVector<QUuid> &playerIds) const override;
    QByteArray assembleJsonFromDartsMultiAttemptScores(const QVector<const IDartsScoreInput *> &models) const override;
    QUuid getWinnerIdByJson(const QByteArray &json) const override;
    QUuid getTournamentIdByJson(const QByteArray &json) const override;
    // Get/set service methods
    DartsJsonService* setAssembleDartsTournamentFromJson(IUnaryService<const QByteArray &, const IDartsTournament *> *assembleDartsTournamentFromJson);
    DartsJsonService* setGetPlayerIndexesFromJson(IUnaryService<const QByteArray &, QVector<int> > *getPlayerIndexesFromJson);
    DartsJsonService* setAssembleJsonDartsPointIndexes(IUnaryService<const IDartsPointIndexes *, QByteArray> *assembleJsonDartsIndexes);
    DartsJsonService* setAssembleJsonFromPlayerNamesAndIds(IBinaryService<const QVector<QUuid> &, const QVector<QString> &, QByteArray> *assembleJsonFromPlayerNamesAndIds);
    DartsJsonService* setAssembleJsonFromTournamentDartsPoints(IBinaryService<const QUuid &, const IDartsModelsService *, QByteArray> *assembleJsonFromTournamentDartsPoints);
    DartsJsonService* setJsonArrayFromDartsScores(IBinaryService<const QUuid &, const IDartsModelsService *, QJsonArray> *jsonArrayFromDartsScores);
    DartsJsonService* setAssembleJsonOrderedDartsPointModels(IBinaryService<const QVector<const DartsModelsContext::IDartsPointInput *> &, const IPlayerModelsService *, const QByteArray> *assembleJsonOrderedDartsPointModels);
    DartsJsonService* setAddPlayerNamesToTournamentJson(IBinaryService<const QByteArray &, const QVector<QString> &, QByteArray> *assembleJsonDartsTournamentModel);
    DartsJsonService* setAssembleJsonDartsTournamentModels(IBinaryService<const IDartsModelsService *, const IPlayerModelsService *, const QByteArray> *assembleJsonDartsTournamentModels);
    DartsJsonService* setAssembleJsonFromPlayerIdAndName(IBinaryService<const QUuid &, const QString &, QByteArray> *assembleJsonFromPlayerIdAndName);
    DartsJsonService* setAssembleJSonFromDartsTournamentModel(IUnaryService<const IDartsTournament *, QByteArray> *assembleJSonFromDartsTournamentModel);
    DartsJsonService* setGetDeleteTournamentIndexesFromJson(IUnaryService<const QByteArray &, QVector<int> > *getDeleteTournamentIndexesFromJson);
    DartsJsonService* setGetDeletePlayerIndexFromJson(IUnaryService<const QByteArray &, int> *getDeletePlayerIndexFromJson);
    DartsJsonService* setAssembleDartsPointModelFromJson(IUnaryService<const QByteArray &, const DartsModelsContext::IDartsPointInput *> *assembleDartsPointModelFromJson);
    DartsJsonService* setAssemblePlayerModelFromJson(IUnaryService<const QByteArray &, const IPlayerModel *> *assemblePlayerModelFromJson);
    DartsJsonService* setAssignPlayerIdsToDartsTournament(IBinaryService<const IDartsTournament *, const QVector<QUuid> &, const IDartsTournament *> *assignPlayerIdsToDartsTournament);
    DartsJsonService* setAssembleJsonFromDartsMultiAttemptScores(IUnaryService<const QVector<const IDartsScoreInput *> &, QByteArray> *assembleJsonFromDartsMultiAttemptScores);
    DartsJsonService* setAssembleJsonByDartsScoreIndexes(IUnaryService<const IDartsScoreIndexes *, QByteArray> *assembleJsonByDartsScoreIndexes);
    DartsJsonService* setGetPlayerNameById(IBinaryService<const QUuid &, const IPlayerModelsService *, QString> *getPlayerNameById);
    DartsJsonService* setGetWinnerIdByJson(IUnaryService<const QByteArray &, QUuid> *getWinnerIdByJson);
    DartsJsonService* setGetTournamentIdByJson(IUnaryService<const QByteArray &, QUuid> *getTournamentIdByJson);
    DartsJsonService* setAddWinnerNameToDartsTournamentJson(IBinaryService<const QByteArray &, const QString &, QByteArray> *newAddWinnerNameToDartsTournamentJson);

private:
    IUnaryService<const QByteArray&,
    const IDartsTournament*>* _assembleDartsTournamentFromJson;
    IUnaryService<const QByteArray&,QVector<int>>* _getPlayerIndexesFromJson;
    IUnaryService<const IDartsPointIndexes*,QByteArray>* _assembleJsonDartsPointIndexes;
    IBinaryService<const QVector<QUuid>&,
                   const QVector<QString>&,
                   QByteArray>* _assembleJsonFromPlayerNamesAndIds;
    IBinaryService<const QUuid&,
                   const IDartsModelsService*,
                   QByteArray>* _assembleJsonFromTournamentDartsPoints;
    IUnaryService<const QVector<const IDartsScoreInput*>&,
                                QByteArray>* _assembleJsonFromDartsMultiAttemptScores;
    IBinaryService<const QUuid&,
                   const IDartsModelsService*,
                   QJsonArray>* _jsonArrayFromDartsScores;
    IBinaryService<const QVector<const DartsModelsContext::IDartsPointInput*>&,
                   const IPlayerModelsService*,const QByteArray>* _assembleJsonOrderedDartsPointModels;
    IBinaryService<const QByteArray&,
                   const QVector<QString>&,
                   QByteArray>* _addPlayerNamesToTournamentJson;
    IBinaryService<const QByteArray&,const QString&, QByteArray>* _addWinnerNameToDartsTournamentJson;
    IBinaryService<const IDartsModelsService*,
                   const IPlayerModelsService*,
                   const QByteArray>* _assembleJsonDartsTournamentModels;
    IBinaryService<const QUuid&,const QString&,QByteArray>* _assembleJsonFromPlayerIdAndName;
    IUnaryService<const IDartsTournament*,QByteArray>* _assembleJSonFromDartsTournamentModel;
    IUnaryService<const QByteArray&,QVector<int>>* _getDeleteTournamentIndexesFromJson;
    IUnaryService<const QByteArray&,int>* _getDeletePlayerIndexFromJson;
    IUnaryService<const QByteArray&,const DartsModelsContext::IDartsPointInput*>* _assembleDartsPointModelFromJson;
    IUnaryService<const QByteArray&,const IPlayerModel*>* _assemblePlayerModelFromJson;
    IBinaryService<const IDartsTournament*,
                           const QVector<QUuid>&,
                           const IDartsTournament*>* _assignPlayerIdsToDartsTournament;
    IUnaryService<const IDartsScoreIndexes*,QByteArray>* _assembleJsonByDartsScoreIndexes;
    IBinaryService<const QUuid&, const IPlayerModelsService*,QString>* _getPlayerNameById;
    IUnaryService<const QByteArray&, QUuid>* _getWinnerIdByJson;
    IUnaryService<const QByteArray&, QUuid>* _getTournamentIdByJson;
};

#endif // DARTSMODELSJSONSERVICE_H
