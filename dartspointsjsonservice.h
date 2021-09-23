#ifndef DARTSMODELSJSONTOINPUTMODELS_H
#define DARTSMODELSJSONTOINPUTMODELS_H

#include "DartsController/DCInputSLAs/idartsinputmodelstojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "idartsinput.h"

class DartsInputModelsToJson : public IDartsInputModelsToJson
{
public:
    virtual QByteArray toJson(const QVector<const IModel<QUuid>*> &models) const override;
};

#endif // DARTSPOINTSJSONSERVICE_H
