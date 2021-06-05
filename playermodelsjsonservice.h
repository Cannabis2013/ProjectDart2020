#ifndef PLAYERMODELSJSONSERVICE_H
#define PLAYERMODELSJSONSERVICE_H

#include "iplayermodelsjsonservice.h"
#include "iplayermodel.h"
#include <qbytearray.h>
#include "iunaryservice.h"
#include "ibinaryservice.h"

namespace DartsModelsContext {
    class PlayerModelsJsonService : public
            IPlayerModelsJsonService<IPlayerModel,QUuid,QString,QByteArray>
    {
    public:

        static PlayerModelsJsonService* createInstance();
        virtual QVector<int> getPlayerIndexesByJson(const JsonFormat &json) const override;
        virtual JsonFormat assembleJsonFromPlayerNamesAndIds(const QVector<IdFormat> &, const QVector<StringFormat> &) const override;
        virtual JsonFormat assembleJsonByPlayerIdAndName(const IdFormat &, const QString &) const override;
        virtual int getDeletePlayerIndexFromJson(const JsonFormat &json) const override;
        virtual const PlayerInterface *assemblePlayerModelFromJson(const JsonFormat &) const override;
        virtual IdFormat getWinnerIdByJson(const JsonFormat &) const override;
        PlayerModelsJsonService* setGetPlayerIndexesFromJson(IUnaryService<const QByteArray &, QVector<int> > *newGetPlayerIndexesFromJson);
        PlayerModelsJsonService* setAssembleJsonFromPlayerNamesAndIds(IBinaryService<const QVector<QUuid> &, const QVector<QString> &, QByteArray> *newAssembleJsonFromPlayerNamesAndIds);
        PlayerModelsJsonService* setAssembleJsonFromPlayerIdAndName(IBinaryService<const QUuid &, const QString &, QByteArray> *newAssembleJsonFromPlayerIdAndName);
        PlayerModelsJsonService* setGetDeletePlayerIndexFromJson(IUnaryService<const QByteArray &, int> *newGetDeletePlayerIndexFromJson);

        PlayerModelsJsonService* setAssemblePlayerModelFromJson(IUnaryService<const QByteArray &, const IPlayerModel *> *newAssemblePlayerModelFromJson);

        PlayerModelsJsonService* setGetWinnerIdByJson(IUnaryService<const QByteArray &, QUuid> *newGetWinnerIdByJson);

    private:
        IUnaryService<const QByteArray&,QVector<int>>* _getPlayerIndexesFromJson;
        IBinaryService<const QVector<QUuid>&,
                       const QVector<QString>&,
                       QByteArray>* _assembleJsonFromPlayerNamesAndIds;
        IBinaryService<const QUuid&,const QString&,QByteArray>* _assembleJsonFromPlayerIdAndName;
        IUnaryService<const QByteArray&,int>* _getDeletePlayerIndexFromJson;
        IUnaryService<const QByteArray&,const IPlayerModel*>* _assemblePlayerModelFromJson;
        IUnaryService<const QByteArray&, QUuid>* _getWinnerIdByJson;
    };
}


#endif // PLAYERMODELSJSONSERVICE_H
