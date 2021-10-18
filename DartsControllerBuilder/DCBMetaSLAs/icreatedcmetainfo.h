#ifndef ICREATEDCMETAINFO_H
#define ICREATEDCMETAINFO_H

#include "DartsControllerBuilder/DCBMetaServices/dcmeta.h"

class ICreateDCMetaInfo
{
public:
    virtual DCBuilding::DCMeta service(const QByteArray &json) const = 0;
};
#endif // ICREATEDCMETAINFO_H
