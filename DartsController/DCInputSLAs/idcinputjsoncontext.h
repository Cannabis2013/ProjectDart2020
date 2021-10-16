#ifndef IDCINPUTJSONCONTEXT_H
#define IDCINPUTJSONCONTEXT_H

#include "DartsController/DCInputSLAs/idcinputmodel.h"
#include <qbytearray.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qvector.h>
#include "DartsController/DCPlayerSLAs/idcplayer.h"

class IDCInputJsonContext {
public:
    virtual void setValues(QJsonObject &obj, DCContext::IDCInputModel* inputModel) const = 0;
    virtual void setValues(QJsonArray &arr, const QVector<DCContext::IDCInputModel*>& inputModels) const = 0;
};

#endif // IDARTSMULTIATTEMPTJSONSERVICE_H
