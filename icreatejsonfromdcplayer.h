#ifndef ICREATEJSONFROMDCPLAYER_H
#define ICREATEJSONFROMDCPLAYER_H

#include "qbytearray.h"
#include <idcplayer.h>

class ICreateJsonFromDCPlayer
{
public:
    virtual QByteArray createJson(const DCContext::IDCPlayer *playerModel) const = 0;
};

#endif // IDCJSONBUILDER_H
