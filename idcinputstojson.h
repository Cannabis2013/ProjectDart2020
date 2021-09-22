#ifndef IDCINPUTSTOJSON_H
#define IDCINPUTSTOJSON_H


#include "DCInputsSLA/idcinputmodel.h"
#include <qbytearray.h>
#include <qvector.h>
#include "idcplayer.h"

class IDCInputsToJson {
public:
    virtual QByteArray createJson(const QVector<DCContext::IDCInputModel*>& inputModels) const = 0;
    virtual QByteArray createJson(DCContext::IDCInputModel* dartsModel) const = 0;
};

#endif // IDARTSMULTIATTEMPTJSONSERVICE_H
