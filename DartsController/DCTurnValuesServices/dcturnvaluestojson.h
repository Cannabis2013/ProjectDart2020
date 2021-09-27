#ifndef DCTURNVALUESTOJSON_H
#define DCTURNVALUESTOJSON_H

#include "DartsController/DCTurnValuesSLAs/idcturnvaluestojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class DCTurnValuesToJson : public IDCTurnValuesToJson
{
public:
    virtual QJsonObject create(const DCContext::DCTurnValues *turnValues) const override
    {
        return toObject(turnValues);
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
};
#endif // DCTURNVALUESTOJSON_H
