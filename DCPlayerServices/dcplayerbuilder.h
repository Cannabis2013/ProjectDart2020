#ifndef DCPLAYERBUILDER_H
#define DCPLAYERBUILDER_H

#include "DCPlayerSLAs/idcplayermodelbuilder.h"
#include <dcplayer.h>

class DCPlayerBuilder : public IDCPlayerModelBuilder
{
public:
    const DCContext::IDCPlayer *createModel(const QUuid &id, const QString &name) const override
    {
        return new DCContext::DCPlayer(id,name);
    }
};
#endif // DARTSPLAYERBUILDERSERVICE_H
