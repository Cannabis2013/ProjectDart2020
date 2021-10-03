#ifndef DCTURNVALUESTOJSON_H
#define DCTURNVALUESTOJSON_H

#include "DartsController/DCTurnValuesSLAs/idcturnvaluestojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class DCTurnValuesToJson : public IDCTurnValuesToJson
{
public:
    virtual void setJsonValues(QJsonObject &obj, const DCContext::DCTurnValues *turnValues,
                               const IDCTurnValJsonKeys *keys) const override
    {
        obj[keys->roundIndex()] = turnValues->getRoundIndex();
        obj[keys->setIndex()] = turnValues->getSetIndex();
        obj[keys->attemptIndex()] = turnValues->getAttemptIndex();
        obj[keys->canUndo()] = turnValues->getCanUndo();
        obj[keys->canRedo()] = turnValues->getCanRedo();
        obj[keys->suggestedFinish()] = turnValues->getTargetRow();
        obj[keys->currentPlayerName()] = turnValues->getCurrentPlayerName();
    }
};
#endif // DCTURNVALUESTOJSON_H
