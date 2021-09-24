#ifndef ICREATEJSONFROMPLAYERMODELS_H
#define ICREATEJSONFROMPLAYERMODELS_H

#include "itojson.h"
#include "PlayerModelsContext/SLAs/iplayermodel.h"
#include <qvector.h>

class ICreateJsonFromPlayerModels : public IToJson<QVector<const IModel<QUuid>*>>
{
public:
    virtual QByteArray toJson(QVector<const IModel<QUuid>*> models) const override = 0;
};



#endif // ICREATEJSONFROMPLAYERMODELS_H
