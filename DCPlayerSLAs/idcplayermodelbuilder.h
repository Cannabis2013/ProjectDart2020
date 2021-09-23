#ifndef IDSCMODELBUILDER_H
#define IDSCMODELBUILDER_H

#include "DCPlayerSLAs/idcplayer.h"

class IDCPlayerModelBuilder
{
public:
    virtual const DCContext::IDCPlayer* createModel(const QUuid &id, const QString &stringValue) const = 0;
};

#endif // IDARTSPLAYERBUILDERSERVICE_H
