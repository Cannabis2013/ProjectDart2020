#ifndef IDCSETINPUTJSONVALUES_H
#define IDCSETINPUTJSONVALUES_H

#include "DartsController/DCInputSLAs/idcinput.h"
#include <qbytearray.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qvector.h>
#include "DartsController/DCPlayerSLAs/idcplayer.h"

class IDCSetInputJsonValues {
public:
    virtual void setValues(QJsonObject &obj, IDCInput* inputModel) const = 0;
    virtual void setValues(QJsonArray &arr, const QVector<IDCInput*>& inputModels) const = 0;
};

#endif // IDARTSMULTIATTEMPTJSONSERVICE_H
