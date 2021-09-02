#ifndef IDCMODELTOJSON_H
#define IDCMODELTOJSON_H

#include "iunaryservice.h"
#include "idcmodel.h"
#include <qbytearray.h>
#include <qvector.h>
#include "idcplayer.h"

class IDCModelToJson {
public:
    virtual QByteArray createJson(const QVector<DCContext::IDCModel*>& inputModels) const = 0;
    virtual QByteArray createJson(DCContext::IDCModel* dartsModel) const = 0;
};

#endif // IDARTSMULTIATTEMPTJSONSERVICE_H
