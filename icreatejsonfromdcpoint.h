#ifndef ICREATEJSONFROMDCPOINT_H
#define ICREATEJSONFROMDCPOINT_H

#include "idcmodel.h"
#include <qbytearray.h>

class ICreateJsonFromDCPoint
{
public:
    virtual QByteArray createJson(const DCContext::IDCModel *model) const = 0;
};
#endif // ICREATEJSONFROMDPCMODEL_H
