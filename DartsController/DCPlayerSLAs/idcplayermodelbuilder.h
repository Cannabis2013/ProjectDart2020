#ifndef IDSCMODELBUILDER_H
#define IDSCMODELBUILDER_H

#include "DartsController/DCPlayerSLAs/idcplayer.h"

class IDCPlayerModelBuilder
{
public:
    virtual DCContext::IDCPlayer* createModel(const QUuid &id, const QString &stringValue) const = 0;
};

#endif // IDARTSPLAYERBUILDERSERVICE_H
