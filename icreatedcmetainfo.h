#ifndef ICREATEDCMETAINFO_H
#define ICREATEDCMETAINFO_H

#include <idcmetainfo.h>

class ICreateDCMetaInfo
{
public:
    virtual const DCBuilding::IDCMetaInfo* service(const QByteArray &json) const = 0;
};


#endif // ICREATEDCMETAINFO_H
