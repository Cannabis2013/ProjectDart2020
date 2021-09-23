#ifndef IDARTSINPUTMODELSTOJSON_H
#define IDARTSINPUTMODELSTOJSON_H

#include "itojson.h"
#include "iplayerinput.h"

class IDartsInputModelsToJson :
        public IToJson<const QVector<const IModel<QUuid>*>&>
{
public:
    virtual QByteArray toJson(const QVector<const IModel<QUuid>*> &models) const override = 0;
};

#endif // IDARTSPOINTJSONBUILDER_H
