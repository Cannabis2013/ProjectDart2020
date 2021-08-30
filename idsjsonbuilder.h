#ifndef IDSJSONBUILDER_H
#define IDSJSONBUILDER_H

#include "iunaryservice.h"
#include <idscmodel.h>
#include <qbytearray.h>
#include <qvector.h>
#include "idcplayer.h"
#include "idscindexes.h"

class IDSJsonBuilder {
public:
    virtual QByteArray createJson(const QVector<DSCContext::IDSCModel*>& inputModels) const = 0;
    virtual QByteArray createJson(DSCContext::IDSCModel* dartsModel) const = 0;
};

#endif // IDARTSMULTIATTEMPTJSONSERVICE_H
