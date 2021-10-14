#ifndef IPLAYERCONTEXTJSONBUILDER_H
#define IPLAYERCONTEXTJSONBUILDER_H

#include <quuid.h>
#include "ModelsContext/MCModelsSLAs/imodel.h"

class IPlayerContextJsonBuilder
{
public:
    virtual QByteArray toJson(const QVector<IModel<QUuid>*>& models) const = 0;
};
#endif // ICREATEJSONFROMPLAYERMODELS_H
