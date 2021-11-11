#ifndef IPLAYERJSONBUILDER_H
#define IPLAYERJSONBUILDER_H
#include <quuid.h>
#include "ModelsContext/ModelsSLAs/imodel.h"
class IPlayerJsonBuilder
{
public:
    virtual QByteArray toJson(const QVector<IModel<QUuid>*>& models) const = 0;
};
#endif // ICREATEJSONFROMPLAYERMODELS_H
