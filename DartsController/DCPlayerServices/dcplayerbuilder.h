#ifndef DCPLAYERBUILDER_H
#define DCPLAYERBUILDER_H

#include "DartsController/DCPlayerSLAs/idcplayermodelbuilder.h"
#include "DartsController/DCPlayerServices/dcplayer.h"

class DCPlayerBuilder : public IDCPlayerModelBuilder
{
public:
    DCContext::IDCPlayer *createModel(const QUuid &id, const QString &name) const override
    {
        return new DCContext::DCPlayer(id,name);
    }
};
#endif // DARTSPLAYERBUILDERSERVICE_H
