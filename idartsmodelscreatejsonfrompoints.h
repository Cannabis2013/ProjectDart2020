#ifndef IDARTSMODELSCREATEJSONFROMPOINTS_H
#define IDARTSMODELSCREATEJSONFROMPOINTS_H

#include "itojson.h"
#include "iplayerinput.h"

class IDartsModelsCreateJsonFromPoints :
        public IToJson<const QVector<const IModel<QUuid>*>&>
{
public:
    virtual QByteArray toJson(const QVector<const IModel<QUuid>*> &models) const override = 0;
};

#endif // IDARTSPOINTJSONBUILDER_H
