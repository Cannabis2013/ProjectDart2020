#ifndef IDARTSINPUTMODELSTOJSON_H
#define IDARTSINPUTMODELSTOJSON_H

#include "DartsModelsContext/DMCInputSLAs/iplayerinput.h"

class IDartsInputModelsToJson
{
public:
    virtual QByteArray toJson(const QVector<const IModel<QUuid>*> &models) const = 0;
};

#endif // IDARTSPOINTJSONBUILDER_H
