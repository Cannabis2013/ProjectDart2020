#ifndef IDCINPUTSTOJSON_H
#define IDCINPUTSTOJSON_H


#include "DartsController/DCInputSLAs/idcinputmodel.h"
#include <qbytearray.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qvector.h>
#include "DartsController/DCPlayerSLAs/idcplayer.h"
#include "DartsController/DCInputSLAs/idcinputjsonkeys.h"

class IDCInputsToJson {
public:
    virtual QJsonArray createJson(const QVector<DCContext::IDCInputModel*>& inputModels, const IDCInputJsonKeys *inputKeys) const = 0;
    virtual QJsonObject createJson(DCContext::IDCInputModel* inputModel, const IDCInputJsonKeys *inputKeys) const = 0;
};

#endif // IDARTSMULTIATTEMPTJSONSERVICE_H
