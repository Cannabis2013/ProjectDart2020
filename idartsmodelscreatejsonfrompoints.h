#ifndef IDARTSMODELSCREATEJSONFROMPOINTS_H
#define IDARTSMODELSCREATEJSONFROMPOINTS_H

#include "icreatejsonfrom.h"
#include "iplayerinput.h"

class IDartsModelsCreateJsonFromPoints :
        public ICreateJsonFrom<const QVector<const IModel<QUuid>*>&>
{
public:
    virtual QByteArray createJson(const QVector<const IModel<QUuid>*> &models) const override = 0;
};

#endif // IDARTSPOINTJSONBUILDER_H
