#ifndef DARTSMODELSJSONSERVICE_H
#define DARTSMODELSJSONSERVICE_H

#include "idartsjsonservice.h"
#include "iunaryservice.h"
#include "ibinaryservice.h"

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
    QByteArray assembleJsonOrderedDartsPointModels(const QVector<const IDartsPointInput *> &pointModels, const IPlayerModelsService *playerModelsService) const override;
    QByteArray assembleJsonDartsTournamentModel(const IDartsTournament *model, const IPlayerModelsService *playerModelsService) const override;
    QByteArray assembleJsonDartsTournamentModels(const IDartsModelsService *dartsModelsService, const IPlayerModelsService *iplayerModelsService) const override;
    QByteArray assembleJsonFromPlayerIdAndName(const QUuid &playerId, const QString &playerName) const override;
    QByteArray assembleJsonFromDartsTournamentModel(const IDartsTournament *model) const override;
    QVector<int> getDeleteTournamentIndexesFromJson(const QByteArray &json) const override;
    int getDeletePlayerIndexFromJson(const QByteArray &json) const override;
    const IDartsPointInput *assembleDartsPointModelFromJson(const QByteArray &json) const override;
    const IPlayerModel *assemblePlayerModelFromJson(const QByteArray &json) const override;
    const IDartsTournament *assignPlayerIdsToDartsTournament(const IDartsTournament *model, const QVector<QUuid> &playerIds) const override;
    QByteArray addPlayerNameToJsonInputModel(const QByteArray &json, const IPlayerModelsService *playerModelsService) const override;
    QByteArray assembleJsonFromDartsPointModel(const IDartsPointInput *model) const override;
    const IDartsScoreInput *assembleDartsScoreModelFromJson(const QByteArray &json) const override;
    QByteArray assembleJsonFromDartsScoreModel(const IDartsScoreInput *model) const override;
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
    DartsJsonService* setAssembleJsonOrderedDartsPointModels(IBinaryService<const QVector<const IDartsPointInput *> &, const IPlayerModelsService *, const QByteArray> *assembleJsonOrderedDartsPointModels);
    DartsJsonService* setAssembleJsonDartsTournamentModel(IBinaryService<const IDartsTournament *, const IPlayerModelsService *, QByteArray> *assembleJsonDartsTournamentModel);
    DartsJsonService* setAssembleJsonDartsTournamentModels(IBinaryService<const IDartsModelsService *, const IPlayerModelsService *, const QByteArray> *assembleJsonDartsTournamentModels);
    DartsJsonService* setAssembleJsonFromPlayerIdAndName(IBinaryService<const QUuid &, const QString &, QByteArray> *assembleJsonFromPlayerIdAndName);
    DartsJsonService* setAssembleJSonFromDartsTournamentModel(IUnaryService<const IDartsTournament *, QByteArray> *assembleJSonFromDartsTournamentModel);
    DartsJsonService* setGetDeleteTournamentIndexesFromJson(IUnaryService<const QByteArray &, QVector<int> > *getDeleteTournamentIndexesFromJson);
    DartsJsonService* setGetDeletePlayerIndexFromJson(IUnaryService<const QByteArray &, int> *getDeletePlayerIndexFromJson);
    DartsJsonService* setAssembleDartsPointModelFromJson(IUnaryService<const QByteArray &, const IDartsPointInput *> *assembleDartsPointModelFromJson);
    DartsJsonService* setAssemblePlayerModelFromJson(IUnaryService<const QByteArray &, const IPlayerModel *> *assemblePlayerModelFromJson);
    DartsJsonService* setAssignPlayerIdsToDartsTournament(IBinaryService<const IDartsTournament *, const QVector<QUuid> &, const IDartsTournament *> *assignPlayerIdsToDartsTournament);
    DartsJsonService* setAddPlayerNameToJsonPointModel(IBinaryService<const IDartsScoreInput *, const QString &, QByteArray> *addPlayerNameToJsonPointModel);
    DartsJsonService* setAssembleJsonFromDartsPointModel(IUnaryService<const IDartsPointInput *, QByteArray> *assembleJsonFromDartsPointModel);
    DartsJsonService* setAssembleDartsScoreFromJson(IUnaryService<const QByteArray &, const IDartsScoreInput *> *assembleDartsScoreFromJson);
    DartsJsonService* setAssembleJsonFromDartsScoreModel(IUnaryService<const IDartsScoreInput *, QByteArray> *assembleJsonFromDartsScoreModel);
    DartsJsonService* setAssembleJsonFromDartsMultiAttemptScores(IUnaryService<const QVector<const IDartsScoreInput *> &, QByteArray> *assembleJsonFromDartsMultiAttemptScores);

    DartsJsonService* setAssembleJsonByDartsScoreIndexes(IUnaryService<const IDartsScoreIndexes *, QByteArray> *assembleJsonByDartsScoreIndexes);
    DartsJsonService* setGetPlayerNameById(IBinaryService<const QUuid &, const IPlayerModelsService *, QString> *getPlayerNameById);
    DartsJsonService* setGetWinnerIdByJson(IUnaryService<const QByteArray &, QUuid> *getWinnerIdByJson);
    DartsJsonService* setGetTournamentIdByJson(IUnaryService<const QByteArray &, QUuid> *getTournamentIdByJson);

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
    IBinaryService<const QVector<const IDartsPointInput*>&,
                   const IPlayerModelsService*,const QByteArray>* _assembleJsonOrderedDartsPointModels;
    IBinaryService<const IDartsTournament*,
                   const IPlayerModelsService*,
                   QByteArray>* _assembleJsonDartsTournamentModel;
    IBinaryService<const IDartsModelsService*,
                   const IPlayerModelsService*,
                   const QByteArray>* _assembleJsonDartsTournamentModels;
    IBinaryService<const QUuid&,const QString&,QByteArray>* _assembleJsonFromPlayerIdAndName;
    IUnaryService<const IDartsTournament*,QByteArray>* _assembleJSonFromDartsTournamentModel;
    IUnaryService<const QByteArray&,QVector<int>>* _getDeleteTournamentIndexesFromJson;
    IUnaryService<const QByteArray&,int>* _getDeletePlayerIndexFromJson;
    IUnaryService<const QByteArray&,const IDartsPointInput*>* _assembleDartsPointModelFromJson;
    IUnaryService<const QByteArray&,const IPlayerModel*>* _assemblePlayerModelFromJson;
    IBinaryService<const IDartsTournament*,
                           const QVector<QUuid>&,
                           const IDartsTournament*>* _assignPlayerIdsToDartsTournament;
    IBinaryService<const IDartsScoreInput*,
                   const QString&,
                   QByteArray>* _assembleJsonByDartsScoreAndPlayerName;
    IUnaryService<const IDartsPointInput*,QByteArray>* _assembleJsonByDartsPointModel;
    IUnaryService<const QByteArray&,const IDartsScoreInput*>* _assembleDartsScoreByJson;
    IUnaryService<const IDartsScoreInput*,QByteArray>* _assembleJsonFromDartsScoreModel;
    IUnaryService<const IDartsScoreIndexes*,QByteArray>* _assembleJsonByDartsScoreIndexes;
    IBinaryService<const QUuid&, const IPlayerModelsService*,QString>* _getPlayerNameById;
    IUnaryService<const QByteArray&, QUuid>* _getWinnerIdByJson;
    IUnaryService<const QByteArray&, QUuid>* _getTournamentIdByJson;
};

#endif // DARTSMODELSJSONSERVICE_H
