#ifndef CREATEJSONFROMDPCPOINT_H
#define CREATEJSONFROMDPCPOINT_H

#include "icreatejsonfromdpcpoint.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class CreateJsonFromDPCPoint : public ICreateJsonFromDPCPoint
{
public:
    QByteArray createJson(const DPCContext::IDPCModel *model) const override
    {
        return toByteArray(toObject(model));
    }
private:
    QJsonObject toObject(const DPCContext::IDPCModel *model) const
    {
        QJsonObject obj;
        obj["point"] = model->point();
        obj["score"] = model->score();
        obj["totalScore"] = model->totalScore();
        obj["playerName"] = model->playerName();
        obj["playerId"] = toString(model->playerId());
        obj["modKeyCode"] = model->modKeyCode();
        return obj;
    }
    QByteArray toByteArray(const QJsonObject &obj) const
    {
        auto document = QJsonDocument(obj);
        return document.toJson();
    }
    QString toString(const QUuid &id) const
    {
        return id.toString(QUuid::WithoutBraces);
    }
};
#endif // CREATEJSONFROMDPCPOINT_H
