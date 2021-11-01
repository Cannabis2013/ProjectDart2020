#ifndef ICREATEDCMETAINFO_H
#define ICREATEDCMETAINFO_H
#include "DartsControllerBuilder/DCBMetaServices/dcbmeta.h"
class ICreateDCMetaInfo
{
public:
    virtual DCBMeta service(const QByteArray &json) const = 0;
};
#endif // ICREATEDCMETAINFO_H
