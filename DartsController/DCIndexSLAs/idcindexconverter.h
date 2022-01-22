#ifndef IDCINDEXCONVERTER_H
#define IDCINDEXCONVERTER_H
class QByteArray;
struct DCMeta;
struct DCIndex;
class IDartsIndex;
class IDCIndexConverter
{
public:
    typedef QByteArray ByteArray;
    virtual ByteArray convert(const DCIndex &idx) const = 0;
};
#endif // IDCIDXBUILDER_H
