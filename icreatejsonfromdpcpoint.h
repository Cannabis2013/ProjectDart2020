#ifndef ICREATEJSONFROMDPCPOINT_H
#define ICREATEJSONFROMDPCPOINT_H

#include "idpcmodel.h"
#include <qbytearray.h>

class ICreateJsonFromDPCPoint
{
public:
    virtual QByteArray createJson(const DPCContext::IDPCModel *model) const = 0;
};
#endif // ICREATEJSONFROMDPCMODEL_H
