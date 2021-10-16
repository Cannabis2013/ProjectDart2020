#ifndef IDCPLAYERJSONBUILDER_H
#define IDCPLAYERJSONBUILDER_H

#include "qbytearray.h"
#include "DartsController/DCPlayerSLAs/idcplayer.h"

class IDCPlayerJsonBuilder
{
public:
    virtual QByteArray createJson(const DCContext::IDCPlayer *playerModel) const = 0;
};

#endif // IDCJSONBUILDER_H
