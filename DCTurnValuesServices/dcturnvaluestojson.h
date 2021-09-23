#ifndef DCTURNVALUESTOJSON_H
#define DCTURNVALUESTOJSON_H

#include "DCTurnValuesSLAs/idcturnvaluestojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class DCTurnValuesToJson : public IDCTurnValuesToJson
{
public:
    virtual QByteArray create(const DCContext::DCTurnValues *turnValues) const override
    {
        return toByteArray(toObject(turnValues));
    }
private:
    QJsonObject toObject(const DCContext::DCTurnValues *turnValues) const
    {
        QJsonObject obj;
        obj["roundIndex"] = turnValues->getRoundIndex();;
        obj["setIndex"] = turnValues->getSetIndex();
        obj["attemptIndex"] = turnValues->getAttemptIndex();
        obj["canUndo"] = turnValues->getCanUndo();
        obj["canRedo"] = turnValues->getCanRedo();
        obj["targetRow"] = turnValues->getTargetRow();
        obj["currentPlayerName"] = turnValues->getCurrentPlayerName();
        return obj;
    }
    QByteArray toByteArray(const QJsonObject &obj) const
    {
        auto document = QJsonDocument(obj);
        return document.toJson();
    }
};
#endif // DCTURNVALUESTOJSON_H
