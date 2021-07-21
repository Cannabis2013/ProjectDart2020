#ifndef ICREATEJSONFROMPLAYERMODELS_H
#define ICREATEJSONFROMPLAYERMODELS_H

#include "icreatejsonfrom.h"
#include "iplayermodel.h"
#include <qvector.h>

class ICreateJsonFromPlayerModels : public ICreateJsonFrom<QVector<const IModel<QUuid>*>>
{
public:
    virtual QByteArray createJson(QVector<const IModel<QUuid>*> models) const override = 0;
};



#endif // ICREATEJSONFROMPLAYERMODELS_H
