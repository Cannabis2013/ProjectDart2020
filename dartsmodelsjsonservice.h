#ifndef DARTSMODELSJSONSERVICE_H
#define DARTSMODELSJSONSERVICE_H

#include "idartsjsonservice.h"
#include "iunaryservice.h"
#include "ibinaryservice.h"

class DartsModelsJsonService :
        public IDartsJsonService
{

    // IDartsModelsJsonService interface
public:
    static DartsModelsJsonService* createInstance();
    const IDartsTournament *assembleDartsTournamentFromJson(const QByteArray &json) const override;
    QVector<int> getPlayerIndexesFromJson(const QByteArray &json) const override;
    QByteArray assembleJsonDartsIndexes(const IDartsPointIndexes *indexes) const override;
    QByteArray assembleJsonFromPlayerNamesAndIds(const QVector<QUuid> &playerIds, const QVector<QString> &playerNames) const override;
    QByteArray assembleJsonFromTournamentDartsPoints(const QUuid &tournamentId, const IDartsModelsService *dartsModelsService) const override;
    QJsonArray jsonArrayFromDartsScores(const QUuid &tournamentId, const IDartsModelsService *dartsModelsService) const override;
    QByteArray assembleJsonOrderedDartsPointModels(const QVector<const IDartsPointInput *> &pointModels, const IPlayerModelsService *playerModelsService) const override;
    QByteArray assembleJsonDartsTournamentModel(const IDartsTournament *model, const IPlayerModelsService *playerModelsService) const override;
    QByteArray assembleJsonDartsTournamentModels(const IDartsModelsService *dartsModelsService, const IPlayerModelsService *iplayerModelsService) const override;
    QByteArray assembleJsonFromDartsIndexesAndPoints(const IDartsModelsService *dartsModelsService, const IPlayerModelsService *playerModelsService) const override;
    QByteArray assembleJsonFromPlayerIdAndName(const QUuid &playerId, const QString &playerName) const override;
    QByteArray assembleJsonFromDartsTournamentModel(const IDartsTournament *model) const override;
    QVector<int> getDeleteTournamentIndexesFromJson(const QByteArray &json) const override;
    int getDeletePlayerIndexFromJson(const QByteArray &json) const override;
    const IDartsPointInput *assembleDartsPointModelFromJson(const QByteArray &json) const override;
    const IPlayerModel *assemblePlayerModelFromJson(const QByteArray &json) const override;
    const IDartsTournament *assignPlayerIdsToDartsTournament(const IDartsTournament *model, const QVector<QUuid> &playerIds) const override;
    QByteArray addPlayerNameToJsonPointModel(const QByteArray &json, const IPlayerModelsService *playerModelsService) const override;
    QByteArray assembleJsonFromDartsPointModel(const IDartsPointInput *model) const override;
    // Get/set service methods
    DartsModelsJsonService* setAssembleDartsTournamentFromJson(IUnaryService<const QByteArray &, const IDartsTournament *> *assembleDartsTournamentFromJson);
    DartsModelsJsonService* setGetPlayerIndexesFromJson(IUnaryService<const QByteArray &, QVector<int> > *getPlayerIndexesFromJson);
    DartsModelsJsonService* setAssembleJsonDartsIndexes(IUnaryService<const IDartsPointIndexes *, QByteArray> *assembleJsonDartsIndexes);
    DartsModelsJsonService* setAssembleJsonFromPlayerNamesAndIds(IBinaryService<const QVector<QUuid> &, const QVector<QString> &, QByteArray> *assembleJsonFromPlayerNamesAndIds);
    DartsModelsJsonService* setAssembleJsonFromTournamentDartsPoints(IBinaryService<const QUuid &, const IDartsModelsService *, QByteArray> *assembleJsonFromTournamentDartsPoints);
    DartsModelsJsonService* setJsonArrayFromDartsScores(IBinaryService<const QUuid &, const IDartsModelsService *, QJsonArray> *jsonArrayFromDartsScores);
    DartsModelsJsonService* setAssembleJsonOrderedDartsPointModels(IBinaryService<const QVector<const IDartsPointInput *> &, const IPlayerModelsService *, const QByteArray> *assembleJsonOrderedDartsPointModels);
    DartsModelsJsonService* setAssembleJsonDartsTournamentModel(IBinaryService<const IDartsTournament *, const IPlayerModelsService *, QByteArray> *assembleJsonDartsTournamentModel);
    DartsModelsJsonService* setAssembleJsonDartsTournamentModels(IBinaryService<const IDartsModelsService *, const IPlayerModelsService *, const QByteArray> *assembleJsonDartsTournamentModels);
    DartsModelsJsonService* setAssembleJsonFromDartsIndexesAndPoints(IBinaryService<const IDartsModelsService *, const IPlayerModelsService *, const QByteArray> *assembleJsonFromDartsIndexesAndPoints);
    DartsModelsJsonService* setAssembleJsonFromPlayerIdAndName(IBinaryService<const QUuid &, const QString &, QByteArray> *assembleJsonFromPlayerIdAndName);
    DartsModelsJsonService* setAssembleJSonFromDartsTournamentModel(IUnaryService<const IDartsTournament *, QByteArray> *assembleJSonFromDartsTournamentModel);
    DartsModelsJsonService* setGetDeleteTournamentIndexesFromJson(IUnaryService<const QByteArray &, QVector<int> > *getDeleteTournamentIndexesFromJson);
    DartsModelsJsonService* setGetDeletePlayerIndexFromJson(IUnaryService<const QByteArray &, int> *getDeletePlayerIndexFromJson);
    DartsModelsJsonService* setAssembleDartsPointModelFromJson(IUnaryService<const QByteArray &, const IDartsPointInput *> *assembleDartsPointModelFromJson);
    DartsModelsJsonService* setAssemblePlayerModelFromJson(IUnaryService<const QByteArray &, const IPlayerModel *> *assemblePlayerModelFromJson);
    DartsModelsJsonService* setAssignPlayerIdsToDartsTournament(IBinaryService<const IDartsTournament *, const QVector<QUuid> &, const IDartsTournament *> *assignPlayerIdsToDartsTournament);
    DartsModelsJsonService* setAddPlayerNameToJsonPointModel(IBinaryService<const QByteArray &, const IPlayerModelsService *, QByteArray> *addPlayerNameToJsonPointModel);
    DartsModelsJsonService* setAssembleJsonFromDartsPointModel(IUnaryService<const IDartsPointInput *, QByteArray> *assembleJsonFromDartsPointModel);

private:
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
                   QJsonArray>* _jsonArrayFromDartsScores;
    IBinaryService<const QVector<const IDartsPointInput*>&,
                   const IPlayerModelsService*,const QByteArray>* _assembleJsonOrderedDartsPointModels;
    IBinaryService<const IDartsTournament*,
                   const IPlayerModelsService*,
                   QByteArray>* _assembleJsonDartsTournamentModel;
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
    IUnaryService<const QByteArray&,const IDartsPointInput*>* _assembleDartsPointModelFromJson;
    IUnaryService<const QByteArray&,const IPlayerModel*>* _assemblePlayerModelFromJson;
    IBinaryService<const IDartsTournament*,
                           const QVector<QUuid>&,
                           const IDartsTournament*>* _assignPlayerIdsToDartsTournament;
    IBinaryService<const QByteArray&,
                   const IPlayerModelsService*,
                   QByteArray>* _addPlayerNameToJsonPointModel;
    IUnaryService<const IDartsPointInput*,QByteArray>* _assembleJsonFromDartsPointModel;

};

#endif // DARTSMODELSJSONSERVICE_H
