#ifndef DARTSMODELSJSONSERVICE_H
#define DARTSMODELSJSONSERVICE_H

#include "idartsjsonservice.h"
#include "iunaryservice.h"
#include "ibinaryservice.h"
#include "dartsscoreinput.h"

namespace DartsModelsContext {
    class DartsJsonService :
            public IDartsJsonService
    {
    public:
        typedef IDartsScoreModelsService<IDartsScoreDb> ScoreModelsService;
        static DartsJsonService* createInstance();
        const IDartsTournament *assembleDartsTournamentFromJson(const QByteArray &json) const override;
        QByteArray addPlayerNamesToDartsTournamentJson(const QByteArray& json, const QVector<QString>& names) const override;
        QByteArray addWinnerNameToDartsTournamentJson(const QByteArray&json, const QString& name) const override;
        QByteArray assembleJsonDartsTournamentModels(const IDartsModelsService *dartsModelsService, const IPlayerModelsService *iplayerModelsService) const override;
        QByteArray assembleJsonFromDartsTournamentModel(const IDartsTournament *model) const override;
        QVector<int> getDeleteTournamentIndexesFromJson(const QByteArray &json) const override;
        QUuid getTournamentIdByJson(const QByteArray &json) const override;
        // Get/set service methods
        DartsJsonService* setAssembleDartsTournamentFromJson(IUnaryService<const QByteArray &, const IDartsTournament *> *assembleDartsTournamentFromJson);
        DartsJsonService* setGetPlayerIndexesFromJson(IUnaryService<const QByteArray &, QVector<int> > *getPlayerIndexesFromJson);
        DartsJsonService* setAddPlayerNamesToTournamentJson(IBinaryService<const QByteArray &, const QVector<QString> &, QByteArray> *assembleJsonDartsTournamentModel);
        DartsJsonService* setAssembleJsonDartsTournamentModels(IBinaryService<const IDartsModelsService *, const IPlayerModelsService *, const QByteArray> *assembleJsonDartsTournamentModels);
        DartsJsonService* setAssembleJSonFromDartsTournamentModel(IUnaryService<const IDartsTournament *, QByteArray> *assembleJSonFromDartsTournamentModel);
        DartsJsonService* setGetDeleteTournamentIndexesFromJson(IUnaryService<const QByteArray &, QVector<int> > *getDeleteTournamentIndexesFromJson);
        DartsJsonService* setAssignPlayerIdsToDartsTournament(IBinaryService<const IDartsTournament *, const QVector<QUuid> &, const IDartsTournament *> *assignPlayerIdsToDartsTournament);
        DartsJsonService* setGetTournamentIdByJson(IUnaryService<const QByteArray &, QUuid> *getTournamentIdByJson);
        DartsJsonService* setAddWinnerNameToDartsTournamentJson(IBinaryService<const QByteArray &, const QString &, QByteArray> *newAddWinnerNameToDartsTournamentJson);

    private:
        IUnaryService<const QByteArray&,
                      const IDartsTournament*>* _assembleDartsTournamentFromJson;
        IBinaryService<const QByteArray&,
                       const QVector<QString>&,
                       QByteArray>* _addPlayerNamesToTournamentJson;
        IBinaryService<const QByteArray&,const QString&, QByteArray>* _addWinnerNameToDartsTournamentJson;
        IBinaryService<const IDartsModelsService*,
                       const IPlayerModelsService*,
                       const QByteArray>* _assembleJsonDartsTournamentModels;
        IUnaryService<const IDartsTournament*,QByteArray>* _assembleJsonFromDartsTournamentModel;
        IUnaryService<const QByteArray&,QVector<int>>* _getDeleteTournamentIndexesFromJson;
        IBinaryService<const IDartsTournament*,
                               const QVector<QUuid>&,
                               const IDartsTournament*>* _assignPlayerIdsToDartsTournament;
        IUnaryService<const QByteArray&, QUuid>* _getTournamentIdByJson;
    };
}


#endif // DARTSMODELSJSONSERVICE_H
