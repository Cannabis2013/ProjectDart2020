#ifndef PLAYERMODELBUILDERSERVICE_H
#define PLAYERMODELBUILDERSERVICE_H

#include "idartsplayermodelbuilderservice.h"
#include <QJsonDocument>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <dcplayer.h>

namespace DPCContext {
    class DartsPlayerModelBuilderService : public
            IDartsPlayerModelBuilderService<DCContext::IDCPlayer,QString,QUuid,QByteArray>
    {
    public:
        QVector<const ModelsInterface *> createPlayerModelsByJson(const JsonFormat &json) const override
        {
            using namespace DCContext;
            auto arr = toJsonArray(json);
            QVector<const IDCPlayer*> list;
            for (const auto &playerDataJsonValue : arr) {
                auto obj = playerDataJsonValue.toObject();
                auto playerStringId = obj["playerId"].toString();
                auto playerId = QUuid::fromString(playerStringId);
                auto playerName = obj["playerName"].toString();
                list << new DCPlayer(playerId,playerName);
            }
            return list;
        }
        const ModelsInterface *createPlayerModelByValues(const IdFormat &id, const StringFormat &name) const override
        {
            return new DCContext::DCPlayer(id,name);
        }
    private:
        QJsonArray toJsonArray(const QByteArray &json) const
        {
            auto document = QJsonDocument::fromJson(json);
            return document.array();
        }
        QVector<const DCContext::IDCPlayer*> createModels(const QJsonArray &arr) const
        {
            using namespace DCContext;
            QVector<const IDCPlayer*> list;
            for (const auto &jsonValue : arr)
                list << createModel(jsonValue);
            return list;
        }
        const DCContext::DCPlayer *createModel(const QJsonValue &jsonValue) const
        {
            using namespace DCContext;
            auto obj = jsonValue.toObject();
            auto playerStringId = obj["playerId"].toString();
            auto playerId = QUuid::fromString(playerStringId);
            auto playerName = obj["playerName"].toString();
            return new DCPlayer(playerId,playerName);
        }
    };
}
#endif // PLAYERMODELBUILDERSERVICE_H
