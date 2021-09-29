#ifndef DCTURNVALUESTOJSON_H
#define DCTURNVALUESTOJSON_H

#include "DartsController/DCTurnValuesSLAs/idcturnvaluestojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class DCTurnValuesToJson : public IDCTurnValuesToJson
{
public:
    virtual void setJsonValues(QJsonObject &obj, const DCContext::DCTurnValues *turnValues) const override
    {
        obj["roundIndex"] = turnValues->getRoundIndex();;
        obj["setIndex"] = turnValues->getSetIndex();
        obj["attemptIndex"] = turnValues->getAttemptIndex();
        obj["canUndo"] = turnValues->getCanUndo();
        obj["canRedo"] = turnValues->getCanRedo();
        obj["targetRow"] = turnValues->getTargetRow();
        obj["currentPlayerName"] = turnValues->getCurrentPlayerName();
    }
};
#endif // DCTURNVALUESTOJSON_H
